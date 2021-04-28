#pragma once

#include <QHash>
#include <QObject>

class Service : public QObject
{
    Q_OBJECT

public:
    explicit Service( QObject * parent = nullptr );

public slots:
    bool get( qulonglong routeId );
    void set( qulonglong routeId, bool visibility );

signals:
    void changed( qulonglong routeId, bool visibility );

private:
    QHash<int, bool> m_routeVisibility;
};
