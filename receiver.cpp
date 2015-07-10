#include "receiver.h"
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QThread>

receiver::receiver(QObject *parent) : QObject(parent)
{

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));


//    QNetworkRequest request;
//    request.setUrl(QUrl("http://qt-project.org"));
//    request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");

    thread()->sleep(1);

    QNetworkReply *reply = manager->get((QNetworkRequest(QUrl("localhost:9998"))));
    connect(reply, SIGNAL(readyRead()), this, SLOT(readyRead()));

    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(slotError(QNetworkReply::NetworkError)));
//    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
//            this, SLOT(slotSslErrors(QList<QSslError>)));
}


void receiver::readyRead(){

    qDebug() << "Reply";
}

void receiver::slotError(QNetworkReply::NetworkError e){
    qDebug() << "Slot Error" << e;
}

void receiver::replyFinished(QNetworkReply* re){
    qDebug() << "Reply finished";
}
