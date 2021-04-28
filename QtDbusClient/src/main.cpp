#include "MainWindow.h"

#include <QApplication>
#include <QDebug>
#include <QLoggingCategory>
#include <QtDBus/QDBusConnection>

Q_LOGGING_CATEGORY( logMain, "main" )

int main( int argc, char * argv[] )
{
    QApplication a( argc, argv );

    if ( !QDBusConnection::sessionBus().isConnected() ) {
        qCCritical( logMain )
          << "Cannot connect to the D-Bus session bus. To start it, run: eval `dbus-launch --auto-syntax";
        return 1;
    }

    MainWindow w;
    w.show();

    return a.exec();
}
