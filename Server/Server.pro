QT += core network sql
QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

TARGET = Server

SOURCES += \
    main.cpp \
    mytcpserver.cpp \
    ClientHandler.cpp \
    DatabaseManager.cpp \
    sha1.cpp \
    newton.cpp \
    vigenere.cpp \
    wavembed.cpp

HEADERS += \
    mytcpserver.h \
    ClientHandler.h \
    DatabaseManager.h \
    sha1.h \
    newton.h \
    vigenere.h \
    wavembed.h


