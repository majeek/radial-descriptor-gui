/****************************************************************************
** Meta object code from reading C++ file 'CalculateSuccessRateForAllWorker.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CalculateSuccessRateForAllWorker.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CalculateSuccessRateForAllWorker.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CalculateSuccessRateForAllWorker_t {
    QByteArrayData data[11];
    char stringdata0[316];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CalculateSuccessRateForAllWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CalculateSuccessRateForAllWorker_t qt_meta_stringdata_CalculateSuccessRateForAllWorker = {
    {
QT_MOC_LITERAL(0, 0, 32), // "CalculateSuccessRateForAllWorker"
QT_MOC_LITERAL(1, 33, 37), // "initializeProgressBarWaitDial..."
QT_MOC_LITERAL(2, 71, 0), // ""
QT_MOC_LITERAL(3, 72, 54), // "connectCalculateSuccessRateWo..."
QT_MOC_LITERAL(4, 127, 27), // "CalculateSuccessRateWorker*"
QT_MOC_LITERAL(5, 155, 32), // "updateSuccessRateVariablesSignal"
QT_MOC_LITERAL(6, 188, 19), // "cv::vector<cv::Mat>"
QT_MOC_LITERAL(7, 208, 34), // "imagesToCalculateSuccessRateV..."
QT_MOC_LITERAL(8, 243, 27), // "numberOfImagesToSuccessRate"
QT_MOC_LITERAL(9, 271, 40), // "imagesToCalculateSuccessRateF..."
QT_MOC_LITERAL(10, 312, 3) // "run"

    },
    "CalculateSuccessRateForAllWorker\0"
    "initializeProgressBarWaitDialogSignal\0"
    "\0connectCalculateSuccessRateWorkerSignalsAndRunItSignal\0"
    "CalculateSuccessRateWorker*\0"
    "updateSuccessRateVariablesSignal\0"
    "cv::vector<cv::Mat>\0"
    "imagesToCalculateSuccessRateVector\0"
    "numberOfImagesToSuccessRate\0"
    "imagesToCalculateSuccessRateFileNameList\0"
    "run"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CalculateSuccessRateForAllWorker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,
       3,    1,   39,    2, 0x06 /* Public */,
       5,    3,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int, QMetaType::QStringList,    7,    8,    9,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void CalculateSuccessRateForAllWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CalculateSuccessRateForAllWorker *_t = static_cast<CalculateSuccessRateForAllWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->initializeProgressBarWaitDialogSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->connectCalculateSuccessRateWorkerSignalsAndRunItSignal((*reinterpret_cast< CalculateSuccessRateWorker*(*)>(_a[1]))); break;
        case 2: _t->updateSuccessRateVariablesSignal((*reinterpret_cast< cv::vector<cv::Mat>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QStringList(*)>(_a[3]))); break;
        case 3: _t->run(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< CalculateSuccessRateWorker* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CalculateSuccessRateForAllWorker::*_t)(QString , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CalculateSuccessRateForAllWorker::initializeProgressBarWaitDialogSignal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CalculateSuccessRateForAllWorker::*_t)(CalculateSuccessRateWorker * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CalculateSuccessRateForAllWorker::connectCalculateSuccessRateWorkerSignalsAndRunItSignal)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CalculateSuccessRateForAllWorker::*_t)(cv::vector<cv::Mat> , int , QStringList );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CalculateSuccessRateForAllWorker::updateSuccessRateVariablesSignal)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject CalculateSuccessRateForAllWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CalculateSuccessRateForAllWorker.data,
      qt_meta_data_CalculateSuccessRateForAllWorker,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CalculateSuccessRateForAllWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CalculateSuccessRateForAllWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CalculateSuccessRateForAllWorker.stringdata0))
        return static_cast<void*>(const_cast< CalculateSuccessRateForAllWorker*>(this));
    if (!strcmp(_clname, "QRunnable"))
        return static_cast< QRunnable*>(const_cast< CalculateSuccessRateForAllWorker*>(this));
    return QObject::qt_metacast(_clname);
}

int CalculateSuccessRateForAllWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void CalculateSuccessRateForAllWorker::initializeProgressBarWaitDialogSignal(QString _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CalculateSuccessRateForAllWorker::connectCalculateSuccessRateWorkerSignalsAndRunItSignal(CalculateSuccessRateWorker * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CalculateSuccessRateForAllWorker::updateSuccessRateVariablesSignal(cv::vector<cv::Mat> _t1, int _t2, QStringList _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
