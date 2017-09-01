#include "publish.h"

Publish::Publish(const QHostAddress host, quint16 port, QObject* parent): Client(host,port,parent)
{
    connect(this, &Publish::connected, this, &Publish::onConnected);
    connect(&m_timer, &QTimer::timeout, this, &Publish::eventloop);
    connect(this, &Publish::disconnected, this, &Publish::onDisconnected);
}
void Publish::getSharedMemory()
{
    //récupération de la valeur de la shared memory
    SharedMemory.setKey("PSDpower");
    SharedMemory.attach(QSharedMemory::ReadWrite);

    QByteArray data;
    SharedMemory.lock();
    data.setRawData((char*)SharedMemory.constData(),SharedMemory.size());
    SharedMemory.unlock();
    QDataStream stream(&data,QIODevice::ReadWrite);
    qDebug()<<"data"<<data;
    stream >> m_X;
    stream >> m_Y;
    stream >> m_psdpower;
    qDebug()<<"psd"<<m_psdpower;
    qDebug()<<"x"<<m_X;
    qDebug()<<"y"<<m_Y;
    SharedMemory.detach();

    SharedMemory.setKey("PowerPhotodiode");
    SharedMemory.attach(QSharedMemory::ReadWrite);
    QByteArray data2;
    SharedMemory.lock();
    data2.setRawData((char*)SharedMemory.constData(),SharedMemory.size());
    SharedMemory.unlock();
    QDataStream stream2(&data2,QIODevice::ReadWrite);
    stream2 >> m_powerFSD;
    stream2 >> m_powertrans1;
    stream2 >> m_powertrans2;
    qDebug()<<"FSD"<< m_powerFSD;
    qDebug()<<"tr1"<< m_powertrans1;
    qDebug()<<"tr2"<< m_powertrans2;
    SharedMemory.detach();
}

void Publish::getvalue()
{
    m_timer.start(1000);
}

void Publish::stopConnect()
{
    m_timer.stop();
    disconnectFromHost();

}

void Publish::onConnected()
{
   qDebug()<<"connected";
}

void Publish::eventloop()
{
    getSharedMemory();

    QMQTT::Message message1(m_X, POS_X, QByteArray::number(m_X));
    publish(message1);
    QMQTT::Message message2(m_Y, POS_Y, QByteArray::number(m_Y));
    publish(message2);
    QMQTT::Message message3(m_psdpower, PSD_POWER, QByteArray::number(m_psdpower));
    publish(message3);
    QMQTT::Message message4(m_powerFSD, FDS_POWER, QByteArray::number(m_powerFSD));
    publish(message4);
    QMQTT::Message message5(m_powertrans1, TRANS1_POWER, QByteArray::number(m_powertrans1));
    publish(message5);
    QMQTT::Message message6(m_powertrans2, TRANS2_POWER, QByteArray::number(m_powertrans2));
    publish(message6);

    /*m_timer.stop();
    disconnectFromHost();*/
}

void Publish::onDisconnected()
{
    QTimer::singleShot(0, qApp, &QCoreApplication::quit);
}


