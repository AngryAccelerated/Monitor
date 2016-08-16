#-------------------------------------------------
#
# Project created by QtCreator 2016-08-14T10:18:58
#
#-------------------------------------------------

QT       += core gui network sql charts concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    datahandler.cpp \
    log.cpp \
    logclient.cpp \
    logclientlifewatcher.cpp \
    logserver.cpp \
    logset.cpp

HEADERS  += mainwindow.h \
    datahandler.h \
    log.h \
    logclient.h \
    logclientlifewatcher.h \
    logserver.h \
    logset.h

FORMS    += mainwindow.ui

TRANSLATIONS += server_zh_CH.ts
