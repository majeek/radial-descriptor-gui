/****************************************************************************
** Meta object code from reading C++ file 'CalculateSignalsWorker.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CalculateSignalsWorker.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CalculateSignalsWorker.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CalculateSignalsWorker_t {
    QByteArrayData data[10];
    char stringdata0[180];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CalculateSignalsWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CalculateSignalsWorker_t qt_meta_stringdata_CalculateSignalsWorker = {
    {
QT_MOC_LITERAL(0, 0, 22), // "CalculateSignalsWorker"
QT_MOC_LITERAL(1, 23, 16), // "sendDebugMessage"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 5), // "error"
QT_MOC_LITERAL(4, 47, 17), // "updateProgressBar"
QT_MOC_LITERAL(5, 65, 29), // "returnCalculateSignalsResults"
QT_MOC_LITERAL(6, 95, 30), // "cv::vector<SignalDescriptor*>*"
QT_MOC_LITERAL(7, 126, 7), // "cv::Mat"
QT_MOC_LITERAL(8, 134, 22), // "acquireProgressBarSlot"
QT_MOC_LITERAL(9, 157, 22) // "releaseProgressBarSlot"

    },
    "CalculateSignalsWorker\0sendDebugMessage\0"
    "\0error\0updateProgressBar\0"
    "returnCalculateSignalsResults\0"
    "cv::vector<SignalDescriptor*>*\0cv::Mat\0"
    "acquireProgressBarSlot\0releaseProgressBarSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CalculateSignalsWorker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       3,    1,   52,    2, 0x06 /* Public */,
       4,    2,   55,    2, 0x06 /* Public */,
       5,    2,   60,    2, 0x06 /* Public */,
       5,    3,   65,    2, 0x06 /* Public */,
       8,    1,   72,    2, 0x06 /* Public */,
       9,    1,   75,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 6, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void CalculateSignalsWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CalculateSignalsWorker *_t = static_cast<CalculateSignalsWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendDebugMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->error((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->updateProgressBar((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->returnCalculateSignalsResults((*reinterpret_cast< cv::vector<SignalDescriptor*>*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->returnCalculateSignalsResults((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< cv::vector<SignalDescriptor*>*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 5: _t->acquireProgressBarSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->releaseProgressBarSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CalculateSignalsWorker::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CalculateSignalsWorker::sendDebugMessage)) {
                *result = 0;
            }
        }
        {
            typedef void (CalculateSignalsWorker::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CalculateSignalsWorker::error)) {
                *result = 1;
            }
        }
        {
            typedef void (CalculateSignalsWorker::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CalculateSignalsWorker::updateProgressBar)) {
                *result = 2;
            }
        }
        {
            typedef void (CalculateSignalsWorker::*_t)(cv::vector<SignalDescriptor*> * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CalculateSignalsWorker::returnCalculateSignalsResults)) {
                *result = 3;
            }
        }
        {
            typedef void (CalculateSignalsWorker::*_t)(cv::Mat , cv::vector<SignalDescriptor*> * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CalculateSignalsWorker::returnCalculateSignalsResults)) {
                *result = 4;
            }
        }
        {
            typedef void (CalculateSignalsWorker::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CalculateSignalsWorker::acquireProgressBarSlot)) {
                *result = 5;
            }
        }
        {
            typedef void (CalculateSignalsWorker::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CalculateSignalsWorker::releaseProgressBarSlot)) {
                *result = 6;
            }
        }
    }
}

const QMetaObject CalculateSignalsWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CalculateSignalsWorker.data,
      qt_meta_data_CalculateSignalsWorker,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CalculateSignalsWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CalculateSignalsWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CalculateSignalsWorker.stringdata0))
        return static_cast<void*>(const_cast< CalculateSignalsWorker*>(this));
    if (!strcmp(_clname, "QRunnable"))
        return static_cast< QRunnable*>(const_cast< CalculateSignalsWorker*>(this));
    return QObject::qt_metacast(_clname);
}

int CalculateSignalsWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void CalculateSignalsWorker::sendDebugMessage(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CalculateSignalsWorker::error(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CalculateSignalsWorker::updateProgressBar(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CalculateSignalsWorker::returnCalculateSignalsResults(cv::vector<SignalDescriptor*> * _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CalculateSignalsWorker::returnCalculateSignalsResults(cv::Mat _t1, cv::vector<SignalDescriptor*> * _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void CalculateSignalsWorker::acquireProgressBarSlot(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void CalculateSignalsWorker::releaseProgressBarSlot(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
