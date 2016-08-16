QT += core sql network
QT -= gui

TARGET = LogDesktop
CONFIG += console
CONFIG -= app_bundle

CONFIG += c++11

TEMPLATE = app


SOURCES += main.cpp \
    datahandler.cpp \
    log.cpp \
    logdesktop.cpp \
    logset.cpp \
    logheardbeatwatcher.cpp \
    logreader.cpp

HEADERS += \
    datahandler.h \
    log.h \
    logdesktop.h \
    logset.h \
    logheardbeatwatcher.h \
    logreader.h


TRANSLATIONS += desktop_zh_CH.ts
