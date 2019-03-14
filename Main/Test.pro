#-------------------------------------------------
#
# Project created by QtCreator 2019-01-31T20:01:12
#
#-------------------------------------------------

QT       += core gui
RC_ICONS = icon.ico
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    itworkspop.cpp \
    qublock.cpp \
    quellblock.cpp \
    aboutgame.cpp \
    infoeditor.cpp \
    importaction.cpp \
    exportaction.cpp \
    aboutauthor.cpp

HEADERS  += mainwindow.h \
    itworkspop.h \
    qublock.h \
    quellblock.h \
    aboutgame.h \
    osspecificvars.h \
    infoeditor.h \
    importaction.h \
    exportaction.h \
    aboutauthor.h
unix {
        QMAKE_CXXFLAGS_WARN_ON += -Wno-unknown-pragmas
        LIBS += -lxml2
    }
win32 {
        QMAKE_CXXFLAGS += /utf-8
        LIBS += -llibxml2
    }

FORMS    += mainwindow.ui \
    itworkspop.ui \
    qublock.ui \
    aboutgame.ui \
    infoeditor.ui \
    aboutauthor.ui
