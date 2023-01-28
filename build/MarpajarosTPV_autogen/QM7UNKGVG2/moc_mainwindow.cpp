/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../forms/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[20];
    char stringdata0[246];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 9), // "ShowLogin"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 7), // "SetUser"
QT_MOC_LITERAL(4, 30, 4), // "user"
QT_MOC_LITERAL(5, 35, 16), // "UpdateWindowList"
QT_MOC_LITERAL(6, 52, 10), // "OpenWindow"
QT_MOC_LITERAL(7, 63, 14), // "QMdiSubWindow*"
QT_MOC_LITERAL(8, 78, 6), // "window"
QT_MOC_LITERAL(9, 85, 21), // "AbrirListadoProductos"
QT_MOC_LITERAL(10, 107, 20), // "AbrirListadoUsuarios"
QT_MOC_LITERAL(11, 128, 7), // "Cascada"
QT_MOC_LITERAL(12, 136, 22), // "DividirHorizontalmente"
QT_MOC_LITERAL(13, 159, 10), // "CerrarTodo"
QT_MOC_LITERAL(14, 170, 12), // "AbrirUsuario"
QT_MOC_LITERAL(15, 183, 9), // "UsuarioId"
QT_MOC_LITERAL(16, 193, 16), // "AbrirUsuarioJson"
QT_MOC_LITERAL(17, 210, 7), // "usuario"
QT_MOC_LITERAL(18, 218, 5), // "roles"
QT_MOC_LITERAL(19, 224, 21) // "UpdateListadoUsuarios"

    },
    "MainWindow\0ShowLogin\0\0SetUser\0user\0"
    "UpdateWindowList\0OpenWindow\0QMdiSubWindow*\0"
    "window\0AbrirListadoProductos\0"
    "AbrirListadoUsuarios\0Cascada\0"
    "DividirHorizontalmente\0CerrarTodo\0"
    "AbrirUsuario\0UsuarioId\0AbrirUsuarioJson\0"
    "usuario\0roles\0UpdateListadoUsuarios"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x0a /* Public */,
       3,    1,   75,    2, 0x0a /* Public */,
       5,    0,   78,    2, 0x0a /* Public */,
       6,    1,   79,    2, 0x0a /* Public */,
       9,    0,   82,    2, 0x0a /* Public */,
      10,    0,   83,    2, 0x0a /* Public */,
      11,    0,   84,    2, 0x0a /* Public */,
      12,    0,   85,    2, 0x0a /* Public */,
      13,    0,   86,    2, 0x0a /* Public */,
      14,    1,   87,    2, 0x0a /* Public */,
      16,    2,   90,    2, 0x0a /* Public */,
      19,    0,   95,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::QJsonObject, QMetaType::QJsonArray,   17,   18,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->ShowLogin(); break;
        case 1: _t->SetUser((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 2: _t->UpdateWindowList(); break;
        case 3: _t->OpenWindow((*reinterpret_cast< QMdiSubWindow*(*)>(_a[1]))); break;
        case 4: _t->AbrirListadoProductos(); break;
        case 5: _t->AbrirListadoUsuarios(); break;
        case 6: _t->Cascada(); break;
        case 7: _t->DividirHorizontalmente(); break;
        case 8: _t->CerrarTodo(); break;
        case 9: _t->AbrirUsuario((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->AbrirUsuarioJson((*reinterpret_cast< QJsonObject(*)>(_a[1])),(*reinterpret_cast< QJsonArray(*)>(_a[2]))); break;
        case 11: _t->UpdateListadoUsuarios(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMdiSubWindow* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
