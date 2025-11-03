/*---------------------------------------------------------*\
||| debugutil.cpp                                           |
|||                                                         |
|||   Debug utility implementation                         |
|||                                                         |
|||   This file is part of the LL-Connect 3 project        |
|||   SPDX-License-Identifier: GPL-2.0-or-later            |
\*---------------------------------------------------------*/

#include "debugutil.h"
#include <QSettings>

namespace DebugUtil {

bool isDebugEnabled() {
    QSettings settings("LianLi", "LConnect3");
    return settings.value("Debug/Enabled", false).toBool();
}

} // namespace DebugUtil

