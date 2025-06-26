QT += testlib
QT -= gui

CONFIG += qt console warn_on c++11
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../Server

SOURCES += tst_newton.cpp \
    ../../Server/newton.cpp

HEADERS += tst_newton.h \
    ../../Server/newton.h 