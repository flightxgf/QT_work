#-------------------------------------------------
#
# Project created by QtCreator 2018-04-19T11:10:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
DEFINES += QT_DEPRECATED_WARNINGS

TARGET = xgftest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    testthread.cpp

HEADERS  += mainwindow.h \
    testthread.h

FORMS    += mainwindow.ui
