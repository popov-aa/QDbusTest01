#include "../include/DbusServices.h"
#include "Service.h"
#include "routevisibility1_adaptor.h"

#include <QCoreApplication>
#include <QDebug>
#include <QLoggingCategory>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusError>

Q_LOGGING_CATEGORY( logMain, "main" )

int main( int argc, char * argv[] )
{
    QCoreApplication a( argc, argv );

    if ( !QDBusConnection::sessionBus().isConnected() ) {
        qCCritical( logMain )
          << "Cannot connect to the D-Bus session bus. To start it, run: eval `dbus-launch --auto-syntax";
        return 1;
    }

    if ( !QDBusConnection::sessionBus().registerService( SERVICE_NAME ) ) {
        qCCritical( logMain ) << QDBusConnection::sessionBus().lastError().message();
        return 2;
    }

    Service service;
    RouteVisibilityAdaptor routeVisibilityAdaptor( &service );
    if ( !QDBusConnection::sessionBus().registerObject( "/", &service ) ) {
        qCCritical( logMain ) << "Cannot register object.";
        return 3;
    }

    return a.exec();
}
