CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(userbatteryplugin)
TEMPLATE    = lib

HEADERS     = UserBatteryPlugin.h
SOURCES     = UserBatteryPlugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

QT += designer

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(userbattery.pri)
