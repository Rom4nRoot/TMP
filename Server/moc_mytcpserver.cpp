/****************************************************************************
** Meta object code from reading C++ file 'mytcpserver.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mytcpserver.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mytcpserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN11MyTcpServerE_t {};
} // unnamed namespace

template <> constexpr inline auto MyTcpServer::qt_create_metaobjectdata<qt_meta_tag_ZN11MyTcpServerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MyTcpServer",
        "onNewConnection",
        "",
        "onClientDisconnected",
        "quintptr",
        "socketId",
        "onClientError",
        "error"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onNewConnection'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onClientDisconnected'
        QtMocHelpers::SlotData<void(quintptr)>(3, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 4, 5 },
        }}),
        // Slot 'onClientError'
        QtMocHelpers::SlotData<void(quintptr, const QString &)>(6, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 4, 5 }, { QMetaType::QString, 7 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MyTcpServer, qt_meta_tag_ZN11MyTcpServerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MyTcpServer::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11MyTcpServerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11MyTcpServerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11MyTcpServerE_t>.metaTypes,
    nullptr
} };

void MyTcpServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MyTcpServer *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onNewConnection(); break;
        case 1: _t->onClientDisconnected((*reinterpret_cast< std::add_pointer_t<quintptr>>(_a[1]))); break;
        case 2: _t->onClientError((*reinterpret_cast< std::add_pointer_t<quintptr>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject *MyTcpServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyTcpServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11MyTcpServerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MyTcpServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
