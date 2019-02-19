/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[12];
    char stringdata0[134];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Widget"
QT_MOC_LITERAL(1, 7, 9), // "ShowShape"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 12), // "ShowPenWidth"
QT_MOC_LITERAL(4, 31, 12), // "ShowPenColor"
QT_MOC_LITERAL(5, 44, 12), // "ShowPenStyle"
QT_MOC_LITERAL(6, 57, 10), // "ShowPenCap"
QT_MOC_LITERAL(7, 68, 11), // "ShowPenJoin"
QT_MOC_LITERAL(8, 80, 15), // "ShowSpreadStyle"
QT_MOC_LITERAL(9, 96, 12), // "ShowFillRule"
QT_MOC_LITERAL(10, 109, 14), // "ShowBrushColor"
QT_MOC_LITERAL(11, 124, 9) // "ShowBrush"

    },
    "Widget\0ShowShape\0\0ShowPenWidth\0"
    "ShowPenColor\0ShowPenStyle\0ShowPenCap\0"
    "ShowPenJoin\0ShowSpreadStyle\0ShowFillRule\0"
    "ShowBrushColor\0ShowBrush"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

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
       1,    1,   64,    2, 0x09 /* Protected */,
       3,    1,   67,    2, 0x09 /* Protected */,
       4,    0,   70,    2, 0x09 /* Protected */,
       5,    1,   71,    2, 0x09 /* Protected */,
       6,    1,   74,    2, 0x09 /* Protected */,
       7,    1,   77,    2, 0x09 /* Protected */,
       8,    0,   80,    2, 0x09 /* Protected */,
       9,    0,   81,    2, 0x09 /* Protected */,
      10,    0,   82,    2, 0x09 /* Protected */,
      11,    1,   83,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Widget *_t = static_cast<Widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ShowShape((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->ShowPenWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->ShowPenColor(); break;
        case 3: _t->ShowPenStyle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->ShowPenCap((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->ShowPenJoin((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->ShowSpreadStyle(); break;
        case 7: _t->ShowFillRule(); break;
        case 8: _t->ShowBrushColor(); break;
        case 9: _t->ShowBrush((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Widget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Widget.data,
      qt_meta_data_Widget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
