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
    QByteArrayData data[14];
    char stringdata0[242];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QTCyberSerpent_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QTCyberSerpent_t qt_meta_stringdata_QTCyberSerpent = {
    {
QT_MOC_LITERAL(0, 0, 14), // "QTCyberSerpent"
QT_MOC_LITERAL(1, 15, 22), // "UI_CB_AddMessageInList"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 17), // "UI_CB_UpdateImage"
QT_MOC_LITERAL(4, 57, 5), // "image"
QT_MOC_LITERAL(5, 63, 17), // "UI_CB_CreateError"
QT_MOC_LITERAL(6, 81, 7), // "message"
QT_MOC_LITERAL(7, 89, 27), // "UI_CB_UpdateAfficherOptions"
QT_MOC_LITERAL(8, 117, 28), // "UI_CB_UpdateAfficherGameplay"
QT_MOC_LITERAL(9, 146, 23), // "UI_CB_UpdateAfficherWin"
QT_MOC_LITERAL(10, 170, 24), // "UI_CB_UpdateAfficherLose"
QT_MOC_LITERAL(11, 195, 20), // "bttn_CommencerPartie"
QT_MOC_LITERAL(12, 216, 12), // "bttn_Quitter"
QT_MOC_LITERAL(13, 229, 12) // "bttn_Valider"

    },
    "QTCyberSerpent\0UI_CB_AddMessageInList\0"
    "\0UI_CB_UpdateImage\0image\0UI_CB_CreateError\0"
    "message\0UI_CB_UpdateAfficherOptions\0"
    "UI_CB_UpdateAfficherGameplay\0"
    "UI_CB_UpdateAfficherWin\0"
    "UI_CB_UpdateAfficherLose\0bttn_CommencerPartie\0"
    "bttn_Quitter\0bttn_Valider"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QTCyberSerpent[] = {

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
       1,    0,   64,    2, 0x08 /* Private */,
       3,    1,   65,    2, 0x08 /* Private */,
       5,    1,   68,    2, 0x08 /* Private */,
       7,    0,   71,    2, 0x08 /* Private */,
       8,    0,   72,    2, 0x08 /* Private */,
       9,    0,   73,    2, 0x08 /* Private */,
      10,    0,   74,    2, 0x08 /* Private */,
      11,    0,   75,    2, 0x08 /* Private */,
      12,    0,   76,    2, 0x08 /* Private */,
      13,    0,   77,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QTCyberSerpent::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QTCyberSerpent *_t = static_cast<QTCyberSerpent *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->UI_CB_AddMessageInList(); break;
        case 1: _t->UI_CB_UpdateImage((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 2: _t->UI_CB_CreateError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->UI_CB_UpdateAfficherOptions(); break;
        case 4: _t->UI_CB_UpdateAfficherGameplay(); break;
        case 5: _t->UI_CB_UpdateAfficherWin(); break;
        case 6: _t->UI_CB_UpdateAfficherLose(); break;
        case 7: _t->bttn_CommencerPartie(); break;
        case 8: _t->bttn_Quitter(); break;
        case 9: _t->bttn_Valider(); break;
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
