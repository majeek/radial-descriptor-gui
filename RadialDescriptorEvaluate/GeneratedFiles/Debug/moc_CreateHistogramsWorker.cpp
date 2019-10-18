/****************************************************************************
** Meta object code from reading C++ file 'CreateHistogramsWorker.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CreateHistogramsWorker.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CreateHistogramsWorker.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CreateHistogramsWorker_t {
    QByteArrayData data[10];
    char stringdata0[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CreateHistogramsWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CreateHistogramsWorker_t qt_meta_stringdata_CreateHistogramsWorker = {
    {
QT_MOC_LITERAL(0, 0, 22), // "CreateHistogramsWorker"
QT_MOC_LITERAL(1, 23, 5), // "error"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 24), // "updateComparisonProgress"
QT_MOC_LITERAL(4, 55, 22), // "returnHistogramsSignal"
QT_MOC_LITERAL(5, 78, 32), // "cv::vector<cv::vector<double> >*"
QT_MOC_LITERAL(6, 111, 7), // "cv::EM*"
QT_MOC_LITERAL(7, 119, 21), // "showMessageWaitWindow"
QT_MOC_LITERAL(8, 141, 21), // "hideMessageWaitWindow"
QT_MOC_LITERAL(9, 163, 3) // "run"

    },
    "CreateHistogramsWorker\0error\0\0"
    "updateComparisonProgress\0"
    "returnHistogramsSignal\0"
    "cv::vector<cv::vector<double> >*\0"
    "cv::EM*\0showMessageWaitWindow\0"
    "hideMessageWaitWindow\0run"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CreateHistogramsWorker[] = {

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
       3,    1,   47,    2, 0x06 /* Public */,
       4,    3,   50,    2, 0x06 /* Public */,
       7,    0,   57,    2, 0x06 /* Public */,
       8,    0,   58,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   59,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    1,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 5, 0x80000000 | 6,    2,    2,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void CreateHistogramsWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CreateHistogramsWorker *_t = static_cast<CreateHistogramsWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->error((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->updateComparisonProgress((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->returnHistogramsSignal((*reinterpret_cast< cv::vector<cv::vector<double> >*(*)>(_a[1])),(*reinterpret_cast< cv::vector<cv::vector<double> >*(*)>(_a[2])),(*reinterpret_cast< cv::EM*(*)>(_a[3]))); break;
        case 3: _t->showMessageWaitWindow(); break;
        case 4: _t->hideMessageWaitWindow(); break;
        case 5: _t->run(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CreateHistogramsWorker::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CreateHistogramsWorker::error)) {
                *result = 0;
            }
        }
        {
            typedef void (CreateHistogramsWorker::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CreateHistogramsWorker::updateComparisonProgress)) {
                *result = 1;
            }
        }
        {
            typedef void (CreateHistogramsWorker::*_t)(cv::vector<cv::vector<double>> * , cv::vector<cv::vector<double>> * , cv::EM * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CreateHistogramsWorker::returnHistogramsSignal)) {
                *result = 2;
            }
        }
        {
            typedef void (CreateHistogramsWorker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CreateHistogramsWorker::showMessageWaitWindow)) {
                *result = 3;
            }
        }
        {
            typedef void (CreateHistogramsWorker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CreateHistogramsWorker::hideMessageWaitWindow)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject CreateHistogramsWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CreateHistogramsWorker.data,
      qt_meta_data_CreateHistogramsWorker,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CreateHistogramsWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CreateHistogramsWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CreateHistogramsWorker.stringdata0))
        return static_cast<void*>(const_cast< CreateHistogramsWorker*>(this));
    if (!strcmp(_clname, "QRunnable"))
        return static_cast< QRunnable*>(const_cast< CreateHistogramsWorker*>(this));
    return QObject::qt_metacast(_clname);
}

int CreateHistogramsWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void CreateHistogramsWorker::error(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CreateHistogramsWorker::updateComparisonProgress(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CreateHistogramsWorker::returnHistogramsSignal(cv::vector<cv::vector<double>> * _t1, cv::vector<cv::vector<double>> * _t2, cv::EM * _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CreateHistogramsWorker::showMessageWaitWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void CreateHistogramsWorker::hideMessageWaitWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
