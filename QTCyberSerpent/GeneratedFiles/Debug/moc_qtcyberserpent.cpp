/****************************************************************************
** Meta object code from reading C++ file 'qtcyberserpent.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qtcyberserpent.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtcyberserpent.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QTCyberSerpent_t {
    QByteArrayData data[8];
    char stringdata0[83];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QTCyberSerpent_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QTCyberSerpent_t qt_meta_stringdata_QTCyberSerpent = {
    {
QT_MOC_LITERAL(0, 0, 14), // "QTCyberSerpent"
QT_MOC_LITERAL(1, 15, 16), // "AddMessageInList"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 11), // "std::string"
QT_MOC_LITERAL(4, 45, 7), // "message"
QT_MOC_LITERAL(5, 53, 11), // "UpdateImage"
QT_MOC_LITERAL(6, 65, 5), // "image"
QT_MOC_LITERAL(7, 71, 11) // "CreateError"

    },
    "QTCyberSerpent\0AddMessageInList\0\0"
    "std::string\0message\0UpdateImage\0image\0"
    "CreateError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QTCyberSerpent[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x08 /* Private */,
       5,    1,   32,    2, 0x08 /* Private */,
       7,    1,   35,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QImage,    6,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void QTCyberSerpent::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QTCyberSerpent *_t = static_cast<QTCyberSerpent *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->AddMessageInList((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 1: _t->UpdateImage((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 2: _t->CreateError((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject QTCyberSerpent::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_QTCyberSerpent.data,
      qt_meta_data_QTCyberSerpent,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QTCyberSerpent::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QTCyberSerpent::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QTCyberSerpent.stringdata0))
        return static_cast<void*>(const_cast< QTCyberSerpent*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int QTCyberSerpent::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
