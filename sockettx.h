#ifndef SOCKETTX_H
#define SOCKETTX_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>
#include <QThread>
#include "worker.h"

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = 0);
    ~MyTcpServer();

signals:
    void operate(const QString &);

public slots:
    void newConnection();
    void handleResults(const QString &);

private:
    QTcpServer *server;
    QThread workerThread;

    void startWorker(QTcpSocket* sck);

};

#endif // MYTCPSERVER_H
