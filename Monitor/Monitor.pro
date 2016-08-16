QT += qml quick quickcontrols2 svg

CONFIG += c++11

SOURCES += main.cpp \
    datahandler.cpp \
    logheardbeatwatcher.cpp \
    logmobile.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES += \
    android/AndroidManifest.xml \
    android/res/values/libs.xml \
    android/build.gradle

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

HEADERS += \
    datahandler.h \
    logheardbeatwatcher.h \
    logmobile.h

