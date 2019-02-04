#-------------------------------------------------
#
# Project created by QtCreator 2019-01-31T20:01:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    itworkspop.cpp \
    quellblock.cpp

HEADERS  += mainwindow.h \
    itworkspop.h \
    quellblock.h

FORMS    += mainwindow.ui \
    itworkspop.ui

unix:!macx: LIBS += -L$$PWD/../build-QuBlock-Desktop-Debug/ -lqublock

INCLUDEPATH += $$PWD/../build-QuBlock-Desktop-Debug
DEPENDPATH += $$PWD/../build-QuBlock-Desktop-Debug
