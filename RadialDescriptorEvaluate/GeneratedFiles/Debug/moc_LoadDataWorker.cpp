/****************************************************************************
** Meta object code from reading C++ file 'LoadDataWorker.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../LoadDataWorker.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LoadDataWorker.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LoadDataWorker_t {
    QByteArrayData data[4];
    char stringdata0[86];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LoadDataWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LoadDataWorker_t qt_meta_stringdata_LoadDataWorker = {
    {
QT_MOC_LITERAL(0, 0, 14), // "LoadDataWorker"
QT_MOC_LITERAL(1, 15, 35), // "initializeTotalProgressDialog..."
QT_MOC_LITERAL(2, 51, 0), // ""
QT_MOC_LITERAL(3, 52, 33) // "increaseTotalProgressDialogSi..."

    },
    "LoadDataWorker\0initializeTotalProgressDialogSignal\0"
    "\0increaseTotalProgressDialogSignal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LoadDataWorker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,
       3,    0,   29,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    2,    2,
    QMetaType::Void,

       0        // eod
};

void LoadDataWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LoadDataWorker *_t = static_cast<LoadDataWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->initializeTotalProgressDialogSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->increaseTotalProgressDialogSignal(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (LoadDataWorker::*_t)(QString , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LoadDataWorker::initializeTotalProgressDialogSignal)) {
                *result = 0;
            }
        }
        {
            typedef void (LoadDataWorker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LoadDataWorker::increaseTotalProgressDialogSignal)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject LoadDataWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_LoadDataWorker.data,
      qt_meta_data_LoadDataWorker,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LoadDataWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LoadDataWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LoadDataWorker.stringdata0))
        return static_cast<void*>(const_cast< LoadDataWorker*>(this));
    if (!strcmp(_clname, "QRunnable"))
        return static_cast< QRunnable*>(const_cast< LoadDataWorker*>(this));
    return QObject::qt_metacast(_clname);
}

int LoadDataWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void LoadDataWorker::initializeTotalProgressDialogSignal(QString _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LoadDataWorker::increaseTotalProgressDialogSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
