#include <QCoreApplication>
#include "publish.h"
#include "subscribe.h"
#include "dbus.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Subscribe s;
    s.connectToHost();
   /*Publish p;
    p.connectToHost();*/





    return a.exec();
}


