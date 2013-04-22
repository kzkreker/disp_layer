#ifndef GPSDATA_H
#define GPSDATA_H

#include <QObject>
#include <QList>

class GPSdata : public QObject
{
    Q_OBJECT
public:
    explicit GPSdata(QObject *parent = 0);


        QString lon;
        QString lat;
        QString dataCV;
        QString speed;
        QString course;
        QString idbuf;


};

#endif // GPSDATA_H
