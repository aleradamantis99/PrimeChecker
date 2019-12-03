TEMPLATE = app
CONFIG += console c++2a
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += --std=c++2a

LIBS += -pthread

SOURCES += \
        main.cpp \
        primechecker.cpp

HEADERS += \
    primechecker.h
