#include <QCoreApplication>
#include "sockettx.h"
#include "receiver.h"

#include <QThread>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MyTcpServer s;

    receiver* r = new receiver(&a);

    return a.exec();
}
