TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    measurement.cpp \
    mswitch.cpp \
    logger.cpp \
    powermanager.cpp \
    composite.cpp

HEADERS += \
    measurement.h \
    mswitch.h \
    logger.h \
    powermanager.h \
    composite.h
