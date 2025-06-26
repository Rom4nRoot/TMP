QT += widgets network sql
CONFIG += c++11 debug
TEMPLATE = app

# Включаем отладочные сообщения
DEFINES += QT_DEBUG

SOURCES += \
    main.cpp \
    authWindow.cpp \
    mainWindow.cpp \
    task1Window.cpp \
    task2Window.cpp \
    task3Window.cpp \
    task4Window.cpp \
    statWindow.cpp \
    registerDialog.cpp \
    client.cpp

HEADERS += \
    logger.h \
    main.h \
    authWindow.h \
    mainWindow.h \
    task1Window.h \
    task2Window.h \
    task3Window.h \
    task4Window.h \
    statWindow.h \
    registerDialog.h \
    client.h

FORMS += \
    authWindow.ui \
    mainWindow.ui \
    task1Window.ui \
    task2Window.ui \
    task3Window.ui \
    task4Window.ui \
    registerDialog.ui \
    statWindow.ui
