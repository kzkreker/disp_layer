#ifndef CSTATISTIC_H
#define CSTATISTIC_H

#include <QObject>
#include <QDateTime>
#include <QList>
#include <QDebug>
#include "gpsdata.h"

class cStatistic : public QObject
{
    Q_OBJECT
public:
    explicit cStatistic(QObject *parent = 0);

signals:

public slots:
    bool findInSyncList(QString id);
    void remOld();

private:

};

#endif // CSTATISTIC_H
