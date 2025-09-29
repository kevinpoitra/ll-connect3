/****************************************************************************
** Meta object code from reading C++ file 'settingspage.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/pages/settingspage.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settingspage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_SettingsPage_t {
    uint offsetsAndSizes[22];
    char stringdata0[13];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[20];
    char stringdata4[24];
    char stringdata5[24];
    char stringdata6[18];
    char stringdata7[25];
    char stringdata8[22];
    char stringdata9[20];
    char stringdata10[11];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_SettingsPage_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_SettingsPage_t qt_meta_stringdata_SettingsPage = {
    {
        QT_MOC_LITERAL(0, 12),  // "SettingsPage"
        QT_MOC_LITERAL(13, 16),  // "onAutoRunToggled"
        QT_MOC_LITERAL(30, 0),  // ""
        QT_MOC_LITERAL(31, 19),  // "onHideOnTrayToggled"
        QT_MOC_LITERAL(51, 23),  // "onMinimizeToTrayToggled"
        QT_MOC_LITERAL(75, 23),  // "onFloatingWindowToggled"
        QT_MOC_LITERAL(99, 17),  // "onLanguageChanged"
        QT_MOC_LITERAL(117, 24),  // "onTemperatureUnitChanged"
        QT_MOC_LITERAL(142, 21),  // "onServiceDelayChanged"
        QT_MOC_LITERAL(164, 19),  // "onApplyServiceDelay"
        QT_MOC_LITERAL(184, 10)   // "onResetAll"
    },
    "SettingsPage",
    "onAutoRunToggled",
    "",
    "onHideOnTrayToggled",
    "onMinimizeToTrayToggled",
    "onFloatingWindowToggled",
    "onLanguageChanged",
    "onTemperatureUnitChanged",
    "onServiceDelayChanged",
    "onApplyServiceDelay",
    "onResetAll"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_SettingsPage[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   68,    2, 0x08,    1 /* Private */,
       3,    0,   69,    2, 0x08,    2 /* Private */,
       4,    0,   70,    2, 0x08,    3 /* Private */,
       5,    0,   71,    2, 0x08,    4 /* Private */,
       6,    0,   72,    2, 0x08,    5 /* Private */,
       7,    0,   73,    2, 0x08,    6 /* Private */,
       8,    0,   74,    2, 0x08,    7 /* Private */,
       9,    0,   75,    2, 0x08,    8 /* Private */,
      10,    0,   76,    2, 0x08,    9 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject SettingsPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_SettingsPage.offsetsAndSizes,
    qt_meta_data_SettingsPage,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_SettingsPage_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SettingsPage, std::true_type>,
        // method 'onAutoRunToggled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onHideOnTrayToggled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onMinimizeToTrayToggled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onFloatingWindowToggled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onLanguageChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onTemperatureUnitChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onServiceDelayChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onApplyServiceDelay'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onResetAll'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void SettingsPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SettingsPage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onAutoRunToggled(); break;
        case 1: _t->onHideOnTrayToggled(); break;
        case 2: _t->onMinimizeToTrayToggled(); break;
        case 3: _t->onFloatingWindowToggled(); break;
        case 4: _t->onLanguageChanged(); break;
        case 5: _t->onTemperatureUnitChanged(); break;
        case 6: _t->onServiceDelayChanged(); break;
        case 7: _t->onApplyServiceDelay(); break;
        case 8: _t->onResetAll(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *SettingsPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SettingsPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SettingsPage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SettingsPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
