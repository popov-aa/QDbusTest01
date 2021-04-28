#pragma once

class QDBusServiceWatcher;
class AeroIansControlIndicatorRouteVisibility1Interface;

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget * parent = nullptr );
    ~MainWindow();

private slots:
    void serviceRegistered( const QString & service );
    void serviceUnregistered( const QString & service );
    void serviceOwnerChanged( const QString & service, const QString & oldOwner, const QString & newOwner );

    void on_pushButtonGet_clicked();
    void on_pushButtonSet_clicked();

private:
    void removeInterface();
    void log( const QString & text );

private:
    Ui::MainWindow * ui;
    QDBusServiceWatcher * m_serviceWatcher;
    AeroIansControlIndicatorRouteVisibility1Interface * m_routeVisibilityInterface;
};
