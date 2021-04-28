QT += core dbus

CONFIG += c++11

DBUS_ADAPTORS += ../dbus-1/interfaces/aero.ians.ControlIndicator.RouteVisibility1.xml

SOURCES += \
    src/Service.cpp \
    src/main.cpp \

HEADERS += \
    src/Service.h \
    ../include/DbusServices.h \
