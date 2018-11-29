/****************************************************************************
** Meta object code from reading C++ file 'main_ui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../main_ui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_ui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_main_ui_t {
    QByteArrayData data[12];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_main_ui_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_main_ui_t qt_meta_stringdata_main_ui = {
    {
QT_MOC_LITERAL(0, 0, 7), // "main_ui"
QT_MOC_LITERAL(1, 8, 6), // "Slot_1"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 6), // "Slot_2"
QT_MOC_LITERAL(4, 23, 6), // "Slot_3"
QT_MOC_LITERAL(5, 30, 6), // "Slot_4"
QT_MOC_LITERAL(6, 37, 6), // "Slot_5"
QT_MOC_LITERAL(7, 44, 6), // "Slot_6"
QT_MOC_LITERAL(8, 51, 6), // "Slot_7"
QT_MOC_LITERAL(9, 58, 6), // "Slot_8"
QT_MOC_LITERAL(10, 65, 6), // "Slot_9"
QT_MOC_LITERAL(11, 72, 9) // "Open_File"

    },
    "main_ui\0Slot_1\0\0Slot_2\0Slot_3\0Slot_4\0"
    "Slot_5\0Slot_6\0Slot_7\0Slot_8\0Slot_9\0"
    "Open_File"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_main_ui[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x09 /* Protected */,
       3,    0,   65,    2, 0x09 /* Protected */,
       4,    0,   66,    2, 0x09 /* Protected */,
       5,    0,   67,    2, 0x09 /* Protected */,
       6,    0,   68,    2, 0x09 /* Protected */,
       7,    0,   69,    2, 0x09 /* Protected */,
       8,    0,   70,    2, 0x09 /* Protected */,
       9,    0,   71,    2, 0x09 /* Protected */,
      10,    0,   72,    2, 0x09 /* Protected */,
      11,    0,   73,    2, 0x09 /* Protected */,

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
    QMetaType::Void,

       0        // eod
};

void main_ui::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        main_ui *_t = static_cast<main_ui *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Slot_1(); break;
        case 1: _t->Slot_2(); break;
        case 2: _t->Slot_3(); break;
        case 3: _t->Slot_4(); break;
        case 4: _t->Slot_5(); break;
        case 5: _t->Slot_6(); break;
        case 6: _t->Slot_7(); break;
        case 7: _t->Slot_8(); break;
        case 8: _t->Slot_9(); break;
        case 9: _t->Open_File(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject main_ui::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_main_ui.data,
      qt_meta_data_main_ui,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *main_ui::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *main_ui::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_main_ui.stringdata0))
        return static_cast<void*>(const_cast< main_ui*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int main_ui::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
