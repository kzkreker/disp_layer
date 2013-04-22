#include "server.h"


Server::Server(QObject* parent) : QObject(parent) {

    server = new MaiaXmlRpcServer(8083, this);
    server->addMethod("transport.nix", this, "nix");
    server->addMethod("transport.sendActiveGPS", this, "sendActiveGPS");
    connector.activateConnection();
    connector.createTables();

}

///////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////
void Server::nix() {
    qDebug() << "i got called";
}

////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////
QVariant Server::sendActiveGPS(QString SeatchData)
{
    qDebug()<<SeatchData;
    return connector.getActiveGps(SeatchData);
}
