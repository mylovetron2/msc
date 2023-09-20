/****************************************************************************
** Meta object code from reading C++ file 'emitter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../myProject_sumome_29-09/emitter.h"
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
    QByteArrayData data[11];
    char stringdata0[115];
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
QT_MOC_LITERAL(5, 44, 13), // "updateAllData"
QT_MOC_LITERAL(6, 58, 14), // "readSerial_sig"
QT_MOC_LITERAL(7, 73, 10), // "readSerial"
QT_MOC_LITERAL(8, 84, 11), // "writeSerial"
QT_MOC_LITERAL(9, 96, 16), // "handleReadSerial"
QT_MOC_LITERAL(10, 113, 1) // "r"

    },
    "Emitter\0signal1\0\0getBufferSerial\0"
    "updateData\0updateAllData\0readSerial_sig\0"
    "readSerial\0writeSerial\0handleReadSerial\0"
    "r"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Emitter[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    1,   55,    2, 0x06 /* Public */,
       4,    0,   58,    2, 0x06 /* Public */,
       5,    0,   59,    2, 0x06 /* Public */,
       6,    1,   60,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   63,    2, 0x0a /* Public */,
       8,    0,   64,    2, 0x0a /* Public */,
       9,    1,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   10,

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
        case 3: _t->updateAllData(); break;
        case 4: _t->readSerial_sig((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 5: _t->readSerial(); break;
        case 6: _t->writeSerial(); break;
        case 7: _t->handleReadSerial((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
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
        {
            using _t = void (Emitter::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Emitter::updateAllData)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Emitter::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Emitter::readSerial_sig)) {
                *result = 4;
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
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
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

// SIGNAL 3
void Emitter::updateAllData()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Emitter::readSerial_sig(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
