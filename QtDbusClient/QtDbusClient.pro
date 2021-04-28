QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets dbus

CONFIG += c++11

DBUS_INTERFACES += ../dbus-1/interfaces/aero.ians.ControlIndicator.RouteVisibility1.xml

SOURCES += \
    src/main.cpp \
    src/MainWindow.cpp \

HEADERS += \
    src/MainWindow.h \
    ../include/DbusServices.h \

FORMS += \
    src/MainWindow.ui \
