#include "database.h"
#include "gpsdata.h"

DataBase::DataBase(QObject *parent) :
    QObject(parent)
{
}

 QSqlDatabase db;


bool DataBase::activateConnection()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("GPStrack");
    db.setHostName("localhost");
    db.setPort(1254);
    db.setUserName("postgres");

    if (!db.open()) {
        qDebug() << QObject::trUtf8("Error") << db.lastError().text();
        return -1;
    }

    return true;
}

void DataBase::closeConnection(){
    db.close();
}

QVariant DataBase::getActiveGps(QString SeatchData)
{
    QSqlQuery query;
    query.exec("SELECT activiti.data, activiti.speed, activiti.course, activiti.lat,"
               "activiti.lon, car.car_name, car.car_number, car.id_crew, car.id_car,"
               "activiti.id, car.gps_table_id, car.pic_table_id "
               "FROM  public.activiti, public.car WHERE "
               "activiti.id = car.gps_table_id AND "
               "activiti.data >= '"+SeatchData+"';");


    QVariant gpssend;
    QVariantList gpssendlist;
    QString resoult;
    QString liststrings;

    while (query.next())
    {
        resoult= query.record().value(0).toString(); liststrings.append(resoult); liststrings.append(",");
        resoult= query.record().value(1).toString(); liststrings.append(resoult); liststrings.append(",");
        resoult= query.record().value(2).toString(); liststrings.append(resoult); liststrings.append(",");
        resoult= query.record().value(3).toString(); liststrings.append(resoult); liststrings.append(",");
        resoult= query.record().value(4).toString(); liststrings.append(resoult); liststrings.append(",");
        resoult= query.record().value(5).toString(); liststrings.append(resoult); liststrings.append(",");
        resoult= query.record().value(6).toString(); liststrings.append(resoult); liststrings.append(",");
        resoult= query.record().value(7).toString(); liststrings.append(resoult); liststrings.append(",");
        resoult= query.record().value(8).toString(); liststrings.append(resoult); liststrings.append(",");
        resoult= query.record().value(9).toString(); liststrings.append(resoult); liststrings.append(",");
        resoult= query.record().value(10).toString(); liststrings.append(resoult); liststrings.append(",");
        resoult= query.record().value(11).toString(); liststrings.append(resoult);
        gpssendlist.append(liststrings);
        liststrings.clear();
    }

    gpssend=gpssendlist;
    qDebug()<<gpssend;
    return gpssend;
}

void DataBase::createTables()
{
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS people (name character varying(60)[], tel character varying,"
               "id_crew integer, id_driver integer NOT NULL, CONSTRAINT id_people_key PRIMARY KEY (id_driver ))"
               "WITH (OIDS=FALSE); ALTER TABLE people OWNER TO postgres;");

    query.exec("CREATE TABLE IF NOT EXISTS car( id_crew integer, id_car integer NOT NULL,"
                "car_name character varying, car_body_number integer,"
                "car_number character varying, car_engine_number integer,"
                "gps_table_id integer, pic_table_id integer,"
                "CONSTRAINT id_car_key PRIMARY KEY (id_car ))"
                "WITH (OIDS=FALSE); ALTER TABLE car OWNER TO postgres;");

}
