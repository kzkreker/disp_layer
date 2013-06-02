#ifndef SERVER_H
#define SERVER_H

#include "maiaXmlRpcServer.h"
#include "database.h"
#include "cstatistic.h"
#include "gpsdata.h"

class Server : public QObject {
    Q_OBJECT

    public:
        Server(QObject* parent = 0);

    signals:

    private slots:
        QVariant sendActiveGPS(QString id);
        QVariant getGPSTrack(QString dataStart, QString dataEnd, QString carID);
        QVariant getPICSensors(QString dataStart, QString dataEnd, QString carID);

    private:
        MaiaXmlRpcServer *server;
        DataBase connector;
        cStatistic status;
};

#endif
