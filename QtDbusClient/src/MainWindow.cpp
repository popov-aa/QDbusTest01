#include "MainWindow.h"
#include "QBigEndianStorageType"
#include "routevisibility1_interface.h"
#include "ui_MainWindow.h"
#include <../include/DbusServices.h>
#include <QDBusConnection>
#include <QDBusConnectionInterface>
#include <QDBusInterface>
#include <QDBusServiceWatcher>
#include <QDebug>
#include <QLoggingCategory>
#include <QtDBus/QDBusServiceWatcher>

Q_LOGGING_CATEGORY( logMainWindow, "MainWindow" )

MainWindow::MainWindow( QWidget * parent )
  : QMainWindow( parent )
  , ui( new Ui::MainWindow )
{
    ui->setupUi( this );
    m_serviceWatcher =
      new QDBusServiceWatcher( SERVICE_NAME,
                               QDBusConnection::sessionBus(),
                               QDBusServiceWatcher::WatchForRegistration | QDBusServiceWatcher::WatchForUnregistration,
                               this );

    QObject::connect( m_serviceWatcher, &QDBusServiceWatcher::serviceRegistered, this, &MainWindow::serviceRegistered );
    QObject::connect(
      m_serviceWatcher, &QDBusServiceWatcher::serviceUnregistered, this, &MainWindow::serviceUnregistered );
    serviceRegistered( SERVICE_NAME );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::serviceRegistered( const QString & service )
{
    if ( service == SERVICE_NAME ) {
        removeInterface();
        m_routeVisibilityInterface = new AeroIansControlIndicatorRouteVisibility1Interface(
          SERVICE_NAME, "/", QDBusConnection::sessionBus(), this );
        if ( m_routeVisibilityInterface->isValid() ) {
            connect(
              m_routeVisibilityInterface,
              &AeroIansControlIndicatorRouteVisibility1Interface::changed,
              this,
              [this]( qulonglong routeId, bool visibility ) {
                  log(
                    tr( "Visibility of route #%1 was set to %2" ).arg( routeId ).arg( visibility ? "true" : "false" ) );
              } );
            log( tr( "Service %1 was registered" ).arg( SERVICE_NAME ) );
            setEnabled( true );
        } else {
            removeInterface();
        }
    } else {
        qCWarning( logMainWindow ) << "Registered service" << service << "is not our service" << SERVICE_NAME;
        return;
    }
}

void MainWindow::serviceUnregistered( const QString & service )
{
    if ( service == SERVICE_NAME ) {
        removeInterface();
        log( tr( "Service %1 was unregistered" ).arg( SERVICE_NAME ) );
        setEnabled( false );
    } else {
        qCWarning( logMainWindow ) << "Registered service" << service << "is not our service" << SERVICE_NAME;
    }
}

void MainWindow::serviceOwnerChanged( const QString & service, const QString & oldOwner, const QString & newOwner )
{
    qDebug( logMainWindow ) << service << oldOwner << newOwner;
}

void MainWindow::on_pushButtonGet_clicked()
{
    ui->checkBoxRouteVisibility->setChecked( m_routeVisibilityInterface->get( ui->spinBoxRouteId->value() ).value() );
}

void MainWindow::on_pushButtonSet_clicked()
{
    m_routeVisibilityInterface->set( ui->spinBoxRouteId->value(), ui->checkBoxRouteVisibility->isChecked() );
}

void MainWindow::removeInterface()
{
    if ( m_routeVisibilityInterface != nullptr ) {
        m_routeVisibilityInterface->deleteLater();
        m_routeVisibilityInterface = nullptr;
    }
}

void MainWindow::log( const QString & text )
{
    ui->textBrowserLog->setPlainText( ui->textBrowserLog->toPlainText() + "\n" + text );
}
