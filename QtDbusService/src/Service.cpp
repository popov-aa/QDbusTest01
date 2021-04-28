#include "Service.h"

#include <QDebug>
#include <QLoggingCategory>

Q_LOGGING_CATEGORY( logService, "Service" );

Service::Service( QObject * parent )
  : QObject( parent )
{}

bool Service::get( qulonglong routeId )
{
    qCInfo( logService ) << "Get route visibility for route" << routeId;
    return m_routeVisibility.value( routeId, false );
}

void Service::set( qulonglong routeId, bool visibility )
{

    qCInfo( logService ) << "Set route visibility for route" << routeId << "to" << visibility;
    m_routeVisibility[routeId] = visibility;
    emit changed( routeId, visibility );
}
