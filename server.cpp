#include "server.h"
////////////////////////////////////////////////////////
///конструктор сервера
////////////////////////////////////////////////////////
Server::Server(QObject* parent) : QObject(parent) {
    server = new MaiaXmlRpcServer(8083, this);

    server->addMethod("transport.sendActiveGPS", this, "sendActiveGPS");
    server->addMethod("transport.getGPSTrack", this, "getGPSTrack");
    server->addMethod("transport.getPICSensors", this, "getPICSensors");

    connector.activateConnection();
    connector.createTables();
}

////////////////////////////////////////////////////////
///отправляем текущее положение транспорта
////////////////////////////////////////////////////////
QVariant Server::sendActiveGPS(QString SeatchData){
    qDebug()<<"sendActiveGPS";
    return connector.getActiveGps(SeatchData);
}

QVariant Server::getGPSTrack(QString dataStart, QString dataEnd, QString carID)
{
  qDebug()<<"getGPSTrack";
  qDebug()<<carID;

  return connector.getGpsTrack(dataStart, dataEnd, carID);
}

////////////////////////////////////////////////////////
///отправляем  показания датчиков из архива
////////////////////////////////////////////////////////
QVariant Server::getPICSensors(QString dataStart, QString dataEnd, QString carID)
{
    qDebug()<<"getPicSensors";

    qDebug()<<carID;
    qDebug()<<  dataStart;
    qDebug()<<  dataEnd;

    return connector.getPicSensors(dataStart, dataEnd, carID);
}
