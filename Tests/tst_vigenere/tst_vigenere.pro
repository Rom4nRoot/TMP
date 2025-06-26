QT += testlib
QT -= gui

CONFIG += qt console warn_on c++11
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../Server

SOURCES += tst_vigenere.cpp \
    ../../Server/vigenere.cpp

HEADERS += tst_vigenere.h \
    ../../Server/vigenere.h 