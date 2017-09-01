QT += core network mqtt
QT -= gui
QT += dbus

TARGET = MQTT
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    publish.cpp \
    subscribe.cpp \
    dbus.cpp

HEADERS += \
    publish.h \
    subscribe.h \
    dbus.h

target.path = /usr/bin
INSTALLS += target

