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

////////////////////////////////////////////////////////////
///Вытаскиваем Активные машины
////////////////////////////////////////////////////////////
QVariant DataBase::getActiveGps(QString SeatchData)
{
    QSqlQuery query;

    //запрос активных машин и смежных таблиц
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
    return gpssend;
}


////////////////////////////////////////////////////////////
///трек по запросу
////////////////////////////////////////////////////////////
QVariant DataBase::getGpsTrack(QString dataStart, QString dataEnd, QString carID)
{
     QSqlQuery query;
     QString vehicletable;
     QString liststrings;

     query.exec( "SELECT car.id_car, car.gps_table_id FROM  public.car Where car.id_car = "+carID+";");

     while (query.next())
     {
        qDebug()<<query.record().value(0).toString();
        qDebug()<<query.record().value(1).toString();
        vehicletable=query.record().value(1).toString();
     }

      query.exec("SELECT data, speed, course, lat, lon FROM vehicle_"+vehicletable+
                 " where data>='"+dataStart+"' AND data<='"+dataEnd+"' ORDER BY data LIMIT 1000000000");

       QString resoult;
       int range=query.size();

       qint64 seeker;

       bool viser = false;

       if (range<=360)                               {seeker=1;}
       else if(range>360 && range<=3600)             {seeker = 5;}
       else if(range>3600 && range<=7200)            {seeker = 30;}
       else if(range>3600 && range<=36000)           {seeker = 80;}
       else if(range>36000 && range<=360000)         {seeker = 1000; viser=true;}
       else if(range>360000 && range<=3600000)       {seeker = 10000; viser=true;}
       else if(range>3600000 && range<=36000000)     {seeker = 100000; viser=true;}
       else if(range>36000000 && range<=360000000)   {seeker = 1000000; viser=true;}
       else if(range>360000000 && range<=3600000000) {seeker = 10000000; viser=true;}
       else if(range>3600000000)                     {seeker = 100000000; viser=true;}



       for(int i=0; i<=query.size(); i=i+seeker)
       {
         query.seek(i);
         if (query.record().value(4).toString()!=""){
         resoult= query.record().value(0).toString(); liststrings=liststrings+resoult+"|";
         resoult= query.record().value(1).toString(); liststrings=liststrings+resoult+"|";
         resoult= query.record().value(2).toString(); liststrings=liststrings+resoult+"|";
         resoult= query.record().value(3).toString(); liststrings=liststrings+resoult+"|";
         resoult= query.record().value(4).toString(); liststrings=liststrings+resoult;
         liststrings = liststrings+"~";}
       }

      liststrings= liststrings+QString::number(viser);
      qDebug()<<"end";
      qDebug()<<liststrings;
      return liststrings;
}

////////////////////////////////////////////////////////////
///Датчики по запросу
////////////////////////////////////////////////////////////
QVariant DataBase::getPicSensors(QString dataStart, QString dataEnd, QString carID)
{
     QSqlQuery query;
     QString vehicletable;
     QString liststrings;
     QString resoult;
     qint64 seeker;

     qDebug()<<dataStart;
     qDebug()<<dataEnd;
     qDebug()<<carID;

     query.exec( "SELECT car.id_car, car.pic_table_id FROM  public.car Where car.id_car = "+carID+";");

     while (query.next())
     {
        qDebug()<<query.record().value(0).toString();
        qDebug()<<query.record().value(1).toString();
        vehicletable=query.record().value(1).toString();
     }

     query.exec( "SELECT an, led, pot, temp, data FROM vehicle_pic_"+vehicletable+
     " where data>='"+dataStart+"' AND data<='"+dataEnd+"' ORDER BY data LIMIT 1000000000");

     int range = query.size();
     qDebug()<<range;
     if (range<=360)                               { seeker=1; }
     else if(range>360 && range<=3600)             { seeker = 5; }
     else if(range>3600 && range<=7200)            { seeker = 30; }
     else if(range>3600 && range<=36000)           { seeker = 80; }
     else if(range>36000 && range<=360000)         { seeker = 1000; }
     else if(range>360000 && range<=3600000)       { seeker = 10000; }
     else if(range>3600000 && range<=36000000)     { seeker = 100000; }
     else if(range>36000000 && range<=360000000)   { seeker = 1000000; }
     else if(range>360000000 && range<=3600000000) { seeker = 10000000; }
     else if(range>3600000000)                     { seeker = 100000000; }


     for(int i=0; i<=query.size(); i=i+seeker)
     {
       query.seek(i);
       if (query.record().value(0).toString()!=""){
       resoult= query.record().value(0).toString(); liststrings=liststrings+resoult+"|";
       resoult= query.record().value(1).toString(); liststrings=liststrings+resoult+"|";
       resoult= query.record().value(2).toString(); liststrings=liststrings+resoult+"|";
       resoult= query.record().value(3).toString(); liststrings=liststrings+resoult+"|";
       resoult= query.record().value(4).toString(); liststrings=liststrings+resoult;
       liststrings = liststrings+"~";}
     }

      qDebug()<<liststrings;

      return liststrings;
}
////////////////////////////////////////////////////////////
///Обслуживание
////////////////////////////////////////////////////////////
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
