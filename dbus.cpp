#include "dbus.h"

#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusReply>



Dbus::Dbus()
{


    qDebug()<<"value";
}

Dbus::~Dbus()
{

}

void Dbus::writeValue(QString serviceName, QString servicePath, const QString functionName, const QVariant arg1)
{
qDebug()<<"writebad";
    QMutexLocker lock(&mutex);
    QDBusInterface send(serviceName, servicePath,"",QDBusConnection::systemBus());
    if(send.isValid())
    {
         qDebug()<<"value send";
        send.call(functionName,arg1);

    }
}

void Dbus::writeValue(QString serviceName, QString servicePath, const QString functionName, const QVariant arg1, const QVariant arg2)
{
    qDebug()<<"writegood";
    QMutexLocker lock(&mutex);
    QDBusInterface send(serviceName, servicePath,"",QDBusConnection::systemBus());
    if(send.isValid())
    {
         qDebug()<<"value send";
        send.call(functionName,arg1,arg2);

    }
}


bool Dbus::readBoolValue(QString serviceName, QString servicePath, const QString functionName)
{
    QMutexLocker lock(&mutex);
    QDBusInterface get(serviceName, servicePath, "", QDBusConnection::systemBus());
    if (get.isValid())
    {
        QDBusReply<bool> reply = get.call(functionName);

        if (reply.isValid())
        {
            return reply.value();
        }
    }
    return 0;
}
