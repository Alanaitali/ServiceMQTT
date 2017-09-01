#ifndef DBUS_H
#define DBUS_H

#include <QMutexLocker>
#include <QMutex>
#include <QVariant>
#include <QThread>
#include <QDebug>



class Dbus : public QObject
{
public:
    Dbus();
    ~Dbus();

protected slots:
    void start();

public:
    Q_INVOKABLE void writeValue(QString serviceName, QString servicePath, const QString functionName, const QVariant arg1);
    Q_INVOKABLE void writeValue(QString serviceName, QString servicePath, const QString functionName, const QVariant arg1,const QVariant arg2);
    Q_INVOKABLE bool readBoolValue(QString serviceName, QString servicePath, const QString functionName);

private:
    QMutex              mutex;

};

#endif // DBUS_H
