#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>
#include <QThread>

class Worker : public QObject
{
    Q_OBJECT
public:
    Worker();
    QTcpSocket* s;

public slots:
    void doWork(const QString &parameter);

signals:
    void resultReady(const QString &result);
};
#endif // WORKER_H
