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

    QVariant getActiveGps(QString SeatchData);
    void closeConnection();
    //void readSettings();
    //void addSettings();
    bool activateConnection();
    void createTables();


private:

};

#endif // DATABASE_H
