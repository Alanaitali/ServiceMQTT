#ifndef PUBLISH_H
#define PUBLISH_H

#include <qmqtt.h>
#include <QCoreApplication>
#include <QTimer>
#include <QObject>
#include <QSharedMemory>
#include <QDataStream>
#include <QDebug>
#include <QIODevice>
#include "dbus.h"



const QHostAddress EXAMPLE_HOST = (QHostAddress)"10.0.0.1";
const quint16 SEND_PORT = 1883;
const QString POS_X = "Position/X";
const QString POS_Y = "Position/Y";
const QString PSD_POWER = "Power/PSD";
const QString FDS_POWER = "Power/FDS";
const QString TRANS1_POWER = "Power/Trans1";
const QString TRANS2_POWER = "Power/Trans2";

class Publish : public QMQTT::Client
{

public:
    Publish(const QHostAddress host=EXAMPLE_HOST, quint16 port=SEND_PORT, QObject *parent=NULL);

public slots:
    void onConnected();
    void getvalue();
    void stopConnect();

protected slots:
    void eventloop();
    void onDisconnected();

private:
    void getSharedMemory();


    QTimer                      m_timer;
    QSharedMemory               SharedMemory;
    Dbus                        m_Dbus;
    double                      m_X;
    double                      m_Y;
    double                      m_powerFSD;
    double                      m_powertrans1;
    double                      m_powertrans2;
    double                      m_psdpower;

};

#endif // PUBLISH_H
