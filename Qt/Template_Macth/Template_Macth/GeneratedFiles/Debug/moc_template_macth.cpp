/****************************************************************************
** Meta object code from reading C++ file 'template_macth.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../template_macth.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'template_macth.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Template_Macth_t {
    QByteArrayData data[15];
    char stringdata0[208];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Template_Macth_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Template_Macth_t qt_meta_stringdata_Template_Macth = {
    {
QT_MOC_LITERAL(0, 0, 14), // "Template_Macth"
QT_MOC_LITERAL(1, 15, 20), // "ho_Image_show_signal"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 1), // "a"
QT_MOC_LITERAL(4, 39, 19), // "init_windows_signal"
QT_MOC_LITERAL(5, 59, 3), // "str"
QT_MOC_LITERAL(6, 63, 24), // "circle_Image_show_signal"
QT_MOC_LITERAL(7, 88, 1), // "b"
QT_MOC_LITERAL(8, 90, 4), // "bstr"
QT_MOC_LITERAL(9, 95, 21), // "Template_Macth_Method"
QT_MOC_LITERAL(10, 117, 22), // "Template_Macth1_Method"
QT_MOC_LITERAL(11, 140, 13), // "ho_Image_show"
QT_MOC_LITERAL(12, 154, 12), // "init_windows"
QT_MOC_LITERAL(13, 167, 17), // "circle_Image_show"
QT_MOC_LITERAL(14, 185, 22) // "Template_Macth2_Method"

    },
    "Template_Macth\0ho_Image_show_signal\0"
    "\0a\0init_windows_signal\0str\0"
    "circle_Image_show_signal\0b\0bstr\0"
    "Template_Macth_Method\0Template_Macth1_Method\0"
    "ho_Image_show\0init_windows\0circle_Image_show\0"
    "Template_Macth2_Method"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Template_Macth[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    1,   62,    2, 0x06 /* Public */,
       6,    2,   65,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   70,    2, 0x08 /* Private */,
      10,    0,   71,    2, 0x08 /* Private */,
      11,    1,   72,    2, 0x08 /* Private */,
      12,    1,   75,    2, 0x08 /* Private */,
      13,    2,   78,    2, 0x08 /* Private */,
      14,    0,   83,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    7,    8,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    7,    8,
    QMetaType::Void,

       0        // eod
};

void Template_Macth::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Template_Macth *_t = static_cast<Template_Macth *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ho_Image_show_signal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->init_windows_signal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->circle_Image_show_signal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->Template_Macth_Method(); break;
        case 4: _t->Template_Macth1_Method(); break;
        case 5: _t->ho_Image_show((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->init_windows((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->circle_Image_show((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: _t->Template_Macth2_Method(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Template_Macth::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Template_Macth::ho_Image_show_signal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Template_Macth::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Template_Macth::init_windows_signal)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Template_Macth::*_t)(int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Template_Macth::circle_Image_show_signal)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject Template_Macth::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Template_Macth.data,
      qt_meta_data_Template_Macth,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Template_Macth::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Template_Macth::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Template_Macth.stringdata0))
        return static_cast<void*>(const_cast< Template_Macth*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Template_Macth::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Template_Macth::ho_Image_show_signal(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Template_Macth::init_windows_signal(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Template_Macth::circle_Image_show_signal(int _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
