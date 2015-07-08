#include <QCoreApplication>
#include "sockettx.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MyTcpServer s;
    s.newConnection();

    return a.exec();
}
