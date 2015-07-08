#include "sockettx.h"
#include "worker.h"

MyTcpServer::MyTcpServer(QObject *parent) :
    QObject(parent)
{
    server = new QTcpServer(this);

    // whenever a user connects, it will emit signal
    connect(server, SIGNAL(newConnection()),
            this, SLOT(newConnection()));

    if(!server->listen(QHostAddress::Any, 9998))
    {
        qDebug() << "Server could not start";
    }
    else
    {
        qDebug() << "Server started!";
    }
}

void MyTcpServer::newConnection()
{
    // need to grab the socket
    QTcpSocket *socket = server->nextPendingConnection();

    if (socket == 0)
            return;

    socket->write("Hello client\r\n");
    socket->flush();

    socket->waitForBytesWritten(3000);

    startWorker(socket);
    //socket->close();
}

void MyTcpServer::startWorker(QTcpSocket* sck){

  Worker* worker = new Worker();
  worker->s = sck;
  worker->moveToThread(&workerThread);

  connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
  connect(this, &MyTcpServer::operate, worker, &Worker::doWork);
  connect(worker, &Worker::resultReady, this, &MyTcpServer::handleResults);
  workerThread.start();
  emit operate("");
}

void MyTcpServer::handleResults(const QString &) {

}

MyTcpServer::~MyTcpServer(){
    workerThread.quit();
    workerThread.wait();
}
