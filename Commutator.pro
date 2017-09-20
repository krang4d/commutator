QT += core gui widgets
INCLUDEPATH += .
TEMPLATE = app
CONFIG += console c++11

SOURCES += main.cpp \
    measurement.cpp \
    mswitch.cpp \
    logger.cpp \
    powermanager.cpp \
    composite.cpp \
    centerwidget.cpp \
    mainwindow.cpp \
    observer.cpp \
    tools.cpp \
    startdialog.cpp \
    scenariothread.cpp

HEADERS += \
    measurement.h \
    mswitch.h \
    logger.h \
    powermanager.h \
    composite.h \
    centerwidget.h \
    mainwindow.h \
    observer.h \
    tools.h \
    startdialog.h \
    scenariothread.h

FORMS += \
    tools.ui \
    startdialog.ui
