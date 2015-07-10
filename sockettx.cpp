#include "sockettx.h"
#include "worker.h"

MyTcpServer::MyTcpServer(QObject *parent) :
    QObject(parent)
{
    server = new QTcpServer(this);

    // whenever a user connects, it will emit signal
    connect(server, SIGNAL(newConnection()),
            this, SLOT(newConnection()));

    connect(server, SIGNAL(acceptError(QAbstractSocket::SocketError)),
            this, SLOT(e(QAbstractSocket::SocketError)));

    if(!server->listen(QHostAddress::Any, 9998))
    {
        qDebug() << "Server could not start";
    }
    else
    {
        qDebug() << "Server started!";
    }
}

void MyTcpServer::e(QAbstractSocket::SocketError e) {

    qDebug() << "Error"  << e;
}

void MyTcpServer::newConnection()
{
    // need to grab the socket
    QTcpSocket *socket = server->nextPendingConnection();

    if (socket == 0)
            return;

    QString boundary = "myboundary";

    QString headerStr =
                "HTTP/1.0 200 OK\r\n" \
                        "Server: iRecon\r\n" \
                        "Connection: close\r\n" \
                        "Max-Age: 0\r\n" \
                        "Expires: 0\r\n" \
                        "Cache-Control: no-store, no-cache, must-revalidate, pre-check=0, post-check=0, max-age=0\r\n" \
                        "Pragma: no-cache\r\n" \
                        "Content-Type: multipart/x-mixed-replace; " \
                        "boundary=" + boundary + "\r\n" \
                        "\r\n" \
                        "--" + boundary + "\r\n";

    socket->write(headerStr.toUtf8());
    socket->flush();

    socket->waitForBytesWritten(3000);

    //startWorker(socket);
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
