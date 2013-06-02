#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql>
#include <QDebug>
#include <QDate>
#include "database.h"
#include "gpsdata.h"
class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    
signals:

public slots:
    //работа с БД
    QVariant getActiveGps(QString SeatchData);
    QVariant getGpsTrack(QString dataStart, QString dataEnd, QString carID);
    QVariant getPicSensors(QString dataStart, QString dataEnd, QString carID);
    //служебные функции
    //void readSettings();
    //void addSettings();
    void closeConnection();
    bool activateConnection();
    void createTables();


private:

};

#endif // DATABASE_H
