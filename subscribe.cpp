#include "subscribe.h"


Subscribe::Subscribe(QObject *parent) : Client(QHostAddress::LocalHost, RECEIVE_PORT, parent)
{
    connect(this, &Subscribe::connected, this, &Subscribe::onConnected);
    connect(this, &Subscribe::subscribed, this, &Subscribe::onSubscribed);
    connect(this, &Subscribe::received, this, &Subscribe::onReceived);

    m_powerrefPSD=0;
    m_powerrefFSD=0;
    m_powerrefTr1=0;
    m_powerrefTr2=0;
    m_serviceName=  "amplitude.systemes.service.warptool";
    m_path=      "/";
    m_calibrationFDS=     "calibrationFDS";
    m_calibrationPSD=     "calibrationPSD";
    m_calibrationTr1=     "calibrationTrans1";
    m_calibrationTr2=     "calibrationTrans2";
    m_PSDvalue=           "psdValue";
    m_photodiodesvalue=   "photodiodeValue";
    m_InterlockFunctionName = "setGPIO";
    m_connectFunctionName = "clientConnect";


}


void Subscribe::onConnected()
{
    m_qout << "connected" << endl;
    subscribe(CALPSD, 0);
    subscribe(CALFDS, 0);
    subscribe(CALTR1, 0);
    subscribe(CALTR2, 0);
    subscribe(PHOTODIODE, 0);
    subscribe(PSD, 0);
    subscribe(Interlock,0);
    subscribe(Connect,0);
}

void Subscribe::onSubscribed(const QString &topic)
{
    m_qout << "subscribed " << topic << endl;
}

void Subscribe::onReceived(const QMQTT::Message &message)
{
    if (message.topic()=="Power/calibration/FDS")
    {
        m_powerrefFSD= (QString::fromUtf8(message.payload())).toDouble();
        m_Dbus.writeValue(m_serviceName,m_path,m_calibrationFDS,m_powerrefFSD);
        qDebug()<<"FSD"<<m_powerrefFSD;

    }
    else if (message.topic()=="Power/calibration/PSD")
    {
        m_powerrefPSD= (QString::fromUtf8(message.payload())).toDouble();
        m_Dbus.writeValue(m_serviceName,m_path,m_calibrationPSD,m_powerrefPSD);
        qDebug()<<"PSD"<<m_powerrefPSD;
    }
    else if (message.topic()=="Power/calibration/TR1")
    {
        m_powerrefTr1= (QString::fromUtf8(message.payload())).toDouble();
        m_Dbus.writeValue(m_serviceName,m_path,m_calibrationTr1,m_powerrefTr1);
        qDebug()<<"Tr1"<<m_powerrefTr1;
    }
    else if (message.topic()=="Power/calibration/TR2")
    {
        m_powerrefTr2= (QString::fromUtf8(message.payload())).toDouble();
        m_Dbus.writeValue(m_serviceName,m_path,m_calibrationTr2,m_powerrefTr2);
        qDebug()<<"Tr2"<<m_powerrefTr2;
    }
    else if (message.topic()=="Value/Psd")
    {
        m_PSD= (QString::fromUtf8(message.payload()).toInt());
        m_Dbus.writeValue(m_serviceName,m_path,m_PSDvalue,m_PSD);
        qDebug()<<"psd"<<m_PSD;

        if(m_PSD=true)
        {
        m_publish.connectToHost();
        m_publish.getvalue();
        }
        else
        {
            m_publish.stopConnect();
        }
    }
    else if(message.topic()=="Value/Photodiode")
    {
        m_Photodiodes= (QString::fromUtf8(message.payload()).toInt());
        m_Dbus.writeValue(m_serviceName,m_path,m_photodiodesvalue,m_Photodiodes);
        qDebug()<<"photodiode"<<m_Photodiodes;
        if(m_Photodiodes==true)
        {
        m_publish.connectToHost();
        m_publish.getvalue();
        qDebug()<<"getvalue";
        }
        else if(m_Photodiodes==false)
        {
            m_publish.disconnect();
            qDebug()<<"stopqet";

        }
    }
    else if(message.topic()=="Value/Gpio/Interlock")
    {
        qDebug()<<"Gpioset"<<m_Photodiodes;
        m_Interlock= (QString::fromUtf8(message.payload()).toInt());
        m_Dbus.writeValue(m_serviceName,m_path,m_InterlockFunctionName,INTERLOCK,m_Interlock);

    }
    else if(message.topic()=="Connect/Client")
    {
        qDebug()<<"Connect"<<m_connect;
        Publish p;
        p.connectToHost();
        p.getvalue();

    }
}

