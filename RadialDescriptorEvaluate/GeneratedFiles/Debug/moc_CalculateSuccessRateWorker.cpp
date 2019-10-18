/****************************************************************************
** Meta object code from reading C++ file 'CalculateSuccessRateWorker.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CalculateSuccessRateWorker.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CalculateSuccessRateWorker.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CalculateSuccessRateWorker_t {
    QByteArrayData data[9];
    char stringdata0[154];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CalculateSuccessRateWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CalculateSuccessRateWorker_t qt_meta_stringdata_CalculateSuccessRateWorker = {
    {
QT_MOC_LITERAL(0, 0, 26), // "CalculateSuccessRateWorker"
QT_MOC_LITERAL(1, 27, 5), // "error"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 17), // "updateProgressBar"
QT_MOC_LITERAL(4, 52, 22), // "acquireProgressBarSlot"
QT_MOC_LITERAL(5, 75, 22), // "releaseProgressBarSlot"
QT_MOC_LITERAL(6, 98, 32), // "returnCalculateSuccessRateResult"
QT_MOC_LITERAL(7, 131, 18), // "cv::vector<double>"
QT_MOC_LITERAL(8, 150, 3) // "run"

    },
    "CalculateSuccessRateWorker\0error\0\0"
    "updateProgressBar\0acquireProgressBarSlot\0"
    "releaseProgressBarSlot\0"
    "returnCalculateSuccessRateResult\0"
    "cv::vector<double>\0run"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CalculateSuccessRateWorker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       3,    2,   47,    2, 0x06 /* Public */,
       4,    1,   52,    2, 0x06 /* Public */,
       5,    1,   55,    2, 0x06 /* Public */,
       6,    3,   58,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    1,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 7, QMetaType::Int,    2,    2,    2,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void CalculateSuccessRateWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CalculateSuccessRateWorker *_t = static_cast<CalculateSuccessRateWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->error((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->updateProgressBar((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->acquireProgressBarSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->releaseProgressBarSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->returnCalculateSuccessRateResult((*reinterpret_cast< cv::vector<double>(*)>(_a[1])),(*reinterpret_cast< cv::vector<double>(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 5: _t->run(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CalculateSuccessRateWorker::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CalculateSuccessRateWorker::error)) {
                *result = 0;
            }
        }
        {
            typedef void (CalculateSuccessRateWorker::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CalculateSuccessRateWorker::updateProgressBar)) {
                *result = 1;
            }
        }
        {
            typedef void (CalculateSuccessRateWorker::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CalculateSuccessRateWorker::acquireProgressBarSlot)) {
                *result = 2;
            }
        }
        {
            typedef void (CalculateSuccessRateWorker::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CalculateSuccessRateWorker::releaseProgressBarSlot)) {
                *result = 3;
            }
        }
        {
            typedef void (CalculateSuccessRateWorker::*_t)(cv::vector<double> , cv::vector<double> , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CalculateSuccessRateWorker::returnCalculateSuccessRateResult)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject CalculateSuccessRateWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CalculateSuccessRateWorker.data,
      qt_meta_data_CalculateSuccessRateWorker,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CalculateSuccessRateWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CalculateSuccessRateWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CalculateSuccessRateWorker.stringdata0))
        return static_cast<void*>(const_cast< CalculateSuccessRateWorker*>(this));
    if (!strcmp(_clname, "QRunnable"))
        return static_cast< QRunnable*>(const_cast< CalculateSuccessRateWorker*>(this));
    return QObject::qt_metacast(_clname);
}

int CalculateSuccessRateWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void CalculateSuccessRateWorker::error(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CalculateSuccessRateWorker::updateProgressBar(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CalculateSuccessRateWorker::acquireProgressBarSlot(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CalculateSuccessRateWorker::releaseProgressBarSlot(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CalculateSuccessRateWorker::returnCalculateSuccessRateResult(cv::vector<double> _t1, cv::vector<double> _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
