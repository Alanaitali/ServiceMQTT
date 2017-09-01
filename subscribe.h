#ifndef SUBSCRIBE_H
#define SUBSCRIBE_H


#include <qmqtt.h>
#include <QCoreApplication>
#include <QTimer>
#include <QObject>
#include <QString>
#include <QSharedMemory>
#include <QDataStream>
#include "dbus.h"
#include "publish.h"


#define INTERLOCK     "/sys/devices/platform/gpio-exporter/out_PA2/value"

const QHostAddress EXAMPLES_HOST = (QHostAddress)"10.0.0.1";
const quint16 RECEIVE_PORT = 1883;
const QString CALPSD = "Power/calibration/PSD";
const QString CALFDS = "Power/calibration/FDS";
const QString CALTR1 = "Power/calibration/TR1";
const QString CALTR2 = "Power/calibration/TR2";
const QString PHOTODIODE = "Value/Photodiode";
const QString PSD = "Value/Psd";
const QString Interlock =        "Value/Gpio/Interlock";
const QString Connect =         "Connect/Client";

class Subscribe : public QMQTT::Client
{

public:
    Subscribe(QObject *parent=NULL);

public slots:
    void onConnected();


protected slots:
    void onSubscribed(const QString& topic);
    void onReceived(const QMQTT::Message& message);

private:

    Dbus                        m_Dbus;
    Publish                     m_publish;
    QTextStream                 m_qout{stdout};
    double                      m_powerrefPSD;
    double                      m_powerrefFSD;                            //Reference power value for calibration
    double                      m_powerrefTr1;
    double                      m_powerrefTr2;
    bool                        m_Photodiodes;
    bool                        m_PSD;
    bool                        m_Interlock;
    bool                        m_connect;
    QString                     m_serviceName;
    QString                     m_pathFds;
    QString                     m_calibrationPSD;
    QString                     m_calibrationFDS;
    QString                     m_calibrationTr1;
    QString                     m_calibrationTr2;
    QString                     m_path;
    QString                     m_PSDvalue;
    QString                     m_photodiodesvalue;
    QString                     m_InterlockFunctionName;
    QString                     m_connectFunctionName;


};

#endif // SUBSCRIBE_H
