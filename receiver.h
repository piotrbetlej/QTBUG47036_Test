#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QNetworkReply>

class receiver : public QObject
{
    Q_OBJECT
public:
    explicit receiver(QObject *parent = 0);

signals:

public slots:
    void readyRead();
    void slotError(QNetworkReply::NetworkError);
    void replyFinished(QNetworkReply*);

};

#endif // RECEIVER_H
