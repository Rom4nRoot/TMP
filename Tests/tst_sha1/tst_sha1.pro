QT += testlib
QT -= gui

CONFIG += qt console warn_on c++11
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../Server

SOURCES += tst_sha1.cpp \
    ../../Server/sha1.cpp

HEADERS += tst_sha1.h \
    ../../Server/sha1.h 