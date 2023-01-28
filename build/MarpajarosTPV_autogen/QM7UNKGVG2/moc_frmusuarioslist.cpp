/****************************************************************************
** Meta object code from reading C++ file 'frmusuarioslist.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../forms/frmusuarioslist.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmusuarioslist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_frmUsuariosList_t {
    QByteArrayData data[15];
    char stringdata0[192];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_frmUsuariosList_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_frmUsuariosList_t qt_meta_stringdata_frmUsuariosList = {
    {
QT_MOC_LITERAL(0, 0, 15), // "frmUsuariosList"
QT_MOC_LITERAL(1, 16, 12), // "AbrirUsuario"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 9), // "UsuarioId"
QT_MOC_LITERAL(4, 40, 13), // "SearchChanged"
QT_MOC_LITERAL(5, 54, 12), // "NuevoUsuario"
QT_MOC_LITERAL(6, 67, 16), // "ModificarUsuario"
QT_MOC_LITERAL(7, 84, 17), // "ActualizarListado"
QT_MOC_LITERAL(8, 102, 11), // "closeParent"
QT_MOC_LITERAL(9, 114, 8), // "LoadPage"
QT_MOC_LITERAL(10, 123, 19), // "ColumnHeaderClicked"
QT_MOC_LITERAL(11, 143, 11), // "columnIndex"
QT_MOC_LITERAL(12, 155, 12), // "ListScrolled"
QT_MOC_LITERAL(13, 168, 8), // "position"
QT_MOC_LITERAL(14, 177, 14) // "DeleteUsuarios"

    },
    "frmUsuariosList\0AbrirUsuario\0\0UsuarioId\0"
    "SearchChanged\0NuevoUsuario\0ModificarUsuario\0"
    "ActualizarListado\0closeParent\0LoadPage\0"
    "ColumnHeaderClicked\0columnIndex\0"
    "ListScrolled\0position\0DeleteUsuarios"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_frmUsuariosList[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   67,    2, 0x0a /* Public */,
       5,    0,   68,    2, 0x0a /* Public */,
       6,    0,   69,    2, 0x0a /* Public */,
       7,    0,   70,    2, 0x0a /* Public */,
       8,    0,   71,    2, 0x08 /* Private */,
       9,    0,   72,    2, 0x08 /* Private */,
      10,    1,   73,    2, 0x08 /* Private */,
      12,    1,   76,    2, 0x08 /* Private */,
      14,    0,   79,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,

       0        // eod
};

void frmUsuariosList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<frmUsuariosList *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->AbrirUsuario((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->SearchChanged(); break;
        case 2: _t->NuevoUsuario(); break;
        case 3: _t->ModificarUsuario(); break;
        case 4: _t->ActualizarListado(); break;
        case 5: _t->closeParent(); break;
        case 6: _t->LoadPage(); break;
        case 7: _t->ColumnHeaderClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->ListScrolled((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->DeleteUsuarios(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (frmUsuariosList::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&frmUsuariosList::AbrirUsuario)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject frmUsuariosList::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_frmUsuariosList.data,
    qt_meta_data_frmUsuariosList,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *frmUsuariosList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *frmUsuariosList::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_frmUsuariosList.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int frmUsuariosList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void frmUsuariosList::AbrirUsuario(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
