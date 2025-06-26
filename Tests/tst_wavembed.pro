QT += testlib
QT -= gui

CONFIG += qt console warn_on c++11
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../Server

SOURCES += tst_wavembed.cpp \
    ../Server/wavembed.cpp

HEADERS += tst_wavembed.h \
    ../Server/wavembed.h 