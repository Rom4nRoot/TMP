QT += testlib
QT -= gui

CONFIG += qt console warn_on c++11
CONFIG -= app_bundle

TEMPLATE = subdirs

# Пути к исходным файлам
INCLUDEPATH += ../Server
INCLUDEPATH += ../Client

# Исходные файлы тестов
SOURCES += \
    tst_sha1.cpp \
    tst_newton.cpp \
    tst_vigenere.cpp \
    tst_wavembed.cpp

HEADERS += \
    tst_sha1.h \
    tst_newton.h \
    tst_vigenere.h \
    tst_wavembed.h

# Исходные файлы сервера
SOURCES += \
    ../Server/sha1.cpp \
    ../Server/newton.cpp \
    ../Server/vigenere.cpp \
    ../Server/wavembed.cpp

HEADERS += \
    ../Server/sha1.h \
    ../Server/newton.h \
    ../Server/vigenere.h \
    ../Server/wavembed.h

# Настройки для тестов
QMAKE_CXXFLAGS += -Wall -Wextra
QMAKE_CXXFLAGS_DEBUG += -g
QMAKE_CXXFLAGS_RELEASE += -O2

# Отключаем предупреждения для тестов
QMAKE_CXXFLAGS += -Wno-unused-parameter

# Генерация .moc файлов
QMAKE_MOC = $$[QT_INSTALL_BINS]/moc
QMAKE_MOCFLAGS = -DQT_NO_KEYWORDS

# Добавляем .moc файлы в проект
OTHER_FILES += \
    tst_sha1.moc \
    tst_newton.moc \
    tst_vigenere.moc \
    tst_wavembed.moc

LIBS += -L../Server/build -lServer

SUBDIRS += \
    tst_newton \
    tst_sha1 \
    tst_vigenere \
    tst_wavembed 