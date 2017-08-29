QT += core gui widgets
INCLUDEPATH += .
TEMPLATE = app
//CONFIG += console c++11

SOURCES += main.cpp \
    measurement.cpp \
    mswitch.cpp \
    logger.cpp \
    powermanager.cpp \
    composite.cpp \
    centerwidget.cpp \
    mainwindow.cpp

HEADERS += \
    measurement.h \
    mswitch.h \
    logger.h \
    powermanager.h \
    composite.h \
    centerwidget.h \
    mainwindow.h
