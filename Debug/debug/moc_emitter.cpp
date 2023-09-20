/****************************************************************************
** Meta object code from reading C++ file 'emitter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../myProject/emitter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'emitter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Emitter_t {
    QByteArrayData data[7];
    char stringdata0[67];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Emitter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Emitter_t qt_meta_stringdata_Emitter = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Emitter"
QT_MOC_LITERAL(1, 8, 7), // "signal1"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 15), // "getBufferSerial"
QT_MOC_LITERAL(4, 33, 10), // "updateData"
QT_MOC_LITERAL(5, 44, 10), // "readSerial"
QT_MOC_LITERAL(6, 55, 11) // "writeSerial"

    },
    "Emitter\0signal1\0\0getBufferSerial\0"
    "updateData\0readSerial\0writeSerial"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Emitter[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    1,   40,    2, 0x06 /* Public */,
       4,    0,   43,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   44,    2, 0x0a /* Public */,
       6,    0,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Emitter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Emitter *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal1(); break;
        case 1: _t->getBufferSerial((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 2: _t->updateData(); break;
        case 3: _t->readSerial(); break;
        case 4: _t->writeSerial(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Emitter::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Emitter::signal1)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Emitter::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Emitter::getBufferSerial)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Emitter::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Emitter::updateData)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Emitter::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Emitter.data,
    qt_meta_data_Emitter,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Emitter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Emitter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Emitter.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Emitter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Emitter::signal1()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Emitter::getBufferSerial(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Emitter::updateData()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
