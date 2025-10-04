/*
 * Lian Li SL Infinity Fan Control Driver (Fan Only)
 * 
 * This driver provides fan speed control for Lian Li SL Infinity fans.
 * RGB control is handled by OpenRGB to avoid conflicts.
 * 
 * Exposes:
 *   /proc/Lian_li_SL_INFINITY/Port_X/fan_speed      (write 0–100)
 *
 * Author: AI + Joey
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/hid.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/delay.h>

#define VENDOR_ID  0x0CF2
#define PRODUCT_ID 0xA102

struct sli_port {
	int index;  /* 0..3 */
	struct sli_hub *hub;
	u8 fan_speed;  /* Current fan speed (0-100) */
};

struct sli_hub {
	struct hid_device *hdev;
	struct proc_dir_entry *procdir;
	struct sli_port ports[4];  /* 4 ports */
};

static struct sli_hub *g_hub = NULL;

/* Send HID command for fan control */
static int sli_send_segment(struct hid_device *hdev, const u8 *buf, size_t len)
{
	int rc;
	rc = hid_hw_raw_request(hdev, 0xE0, (u8 *)buf, len,
							HID_FEATURE_REPORT, HID_REQ_SET_REPORT);
	if (rc < 0)
		pr_err("SLI: HID command failed: %d\n", rc);
	return rc;
}

/* Set fan speed for a port */
static int sli_set_fan_speed(struct sli_port *p, u8 speed_percent)
{
	struct hid_device *hdev = p->hub->hdev;
	u8 port_num = p->index + 1;  /* Convert 0-based to 1-based port number */
	u8 cmd[7];

	/* Individual port control protocol discovered from PCAP analysis:
	 * Port 1: e0 20 00 <duty> 00 00 00
	 * Port 2: e0 21 00 <duty> 00 00 00
	 * Port 3: e0 22 00 <duty> 00 00 00
	 * Port 4: e0 23 00 <duty> 00 00 00
	 */
	cmd[0] = 0xE0;           /* Report ID */
	cmd[1] = 0x20 + p->index; /* Port selector: 0x20, 0x21, 0x22, 0x23 */
	cmd[2] = 0x00;           /* Reserved */
	cmd[3] = speed_percent;  /* Duty cycle (0-100) */
	cmd[4] = 0x00;           /* Reserved */
	cmd[5] = 0x00;           /* Reserved */
	cmd[6] = 0x00;           /* Reserved */

	pr_info("SLI: Setting port %d to %d%% (duty=0x%02x)\n", 
	        port_num, speed_percent, speed_percent);

	int rc = sli_send_segment(hdev, cmd, sizeof(cmd));
	if (rc < 0) {
		pr_err("SLI: Failed to set port %d to %d%%: %d\n", port_num, speed_percent, rc);
		return rc;
	}

	pr_info("SLI: Successfully set port %d to %d%%\n", port_num, speed_percent);
	p->fan_speed = speed_percent;
	return 0;
}

/* Write handler: percentage -> duty */
static ssize_t sli_write_fan_speed(struct file *file,
								   const char __user *ubuf,
								   size_t count, loff_t *ppos)
{
	struct sli_port *p = pde_data(file_inode(file));
	char buf[16];
	int speed;
	int rc;

	if (count >= sizeof(buf))
		return -EINVAL;
	if (copy_from_user(buf, ubuf, count))
		return -EFAULT;
	buf[count] = '\0';

	if (kstrtoint(buf, 10, &speed) < 0)
		return -EINVAL;

	/* Clamp to valid range */
	if (speed < 0) speed = 0;
	if (speed > 100) speed = 100;

	rc = sli_set_fan_speed(p, (u8)speed);
	if (rc < 0) return rc;

	pr_info("SLI: Port %d set to %d%% (duty=0x%02x)\n", 
	        p->index+1, speed, speed);
	return count;
}

/* Read handler: return current speed */
static ssize_t sli_read_fan_speed(struct file *file, char __user *ubuf,
								  size_t count, loff_t *ppos)
{
	struct sli_port *p = pde_data(file_inode(file));
	char buf[16];
	int len;

	if (*ppos > 0)
		return 0;

	len = snprintf(buf, sizeof(buf), "%d\n", p->fan_speed);
	if (len > count)
		len = count;

	if (copy_to_user(ubuf, buf, len))
		return -EFAULT;

	*ppos += len;
	return len;
}

static const struct proc_ops sli_fan_speed_ops = {
	.proc_read = sli_read_fan_speed,
	.proc_write = sli_write_fan_speed,
};

/* Probe function */
static int sli_probe(struct hid_device *hdev, const struct hid_device_id *id)
{
	struct sli_hub *hub;
	int i;

	hub = devm_kzalloc(&hdev->dev, sizeof(*hub), GFP_KERNEL);
	if (!hub)
		return -ENOMEM;

	hub->hdev = hdev;
	hid_set_drvdata(hdev, hub);

	int rc = hid_parse(hdev);
	if (rc) {
		pr_err("SLI: HID parse failed: %d\n", rc);
		return rc;
	}

	rc = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	if (rc) {
		pr_err("SLI: HID hw start failed: %d\n", rc);
		return rc;
	}

	/* Create proc directory */
	hub->procdir = proc_mkdir("Lian_li_SL_INFINITY", NULL);
	if (!hub->procdir) {
		pr_err("SLI: Failed to create proc directory\n");
		hid_hw_stop(hdev);
		return -ENOMEM;
	}

	/* Initialize ports */
	for (i = 0; i < 4; i++) {
		hub->ports[i].index = i;
		hub->ports[i].hub = hub;
		hub->ports[i].fan_speed = 0;
	}

	/* Create proc files for each port */
	for (i = 0; i < 4; i++) {
		char port_name[16];
		struct proc_dir_entry *port_dir;
		struct sli_port *p = &hub->ports[i];

		snprintf(port_name, sizeof(port_name), "Port_%d", i+1);
		port_dir = proc_mkdir(port_name, hub->procdir);
		if (!port_dir) {
			pr_err("SLI: Failed to create proc dir for port %d\n", i+1);
			continue;
		}

		/* Fan speed control */
		proc_create_data("fan_speed", 0222, port_dir, &sli_fan_speed_ops, p);
	}

	g_hub = hub;
	pr_info("SLI: HID device initialized\n");
	return 0;
}

static void sli_remove(struct hid_device *hdev)
{
	struct sli_hub *hub = hid_get_drvdata(hdev);
	if (hub && hub->procdir) {
		remove_proc_subtree("Lian_li_SL_INFINITY", NULL);
	}
	hid_hw_stop(hdev);
	g_hub = NULL;
	pr_info("SLI: HID device removed\n");
}

static const struct hid_device_id sli_table[] = {
	{ HID_USB_DEVICE(VENDOR_ID, PRODUCT_ID) },
	{ }
};
MODULE_DEVICE_TABLE(hid, sli_table);

static struct hid_driver sli_driver = {
	.name = "Lian_Li_SL_INFINITY",
	.id_table = sli_table,
	.probe = sli_probe,
	.remove = sli_remove,
};

module_hid_driver(sli_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("AI + Joey");
MODULE_DESCRIPTION("Lian Li SL Infinity Fan Control Driver (Fan Only)");
MODULE_VERSION("1.0");
