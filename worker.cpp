#include "worker.h"

Worker::Worker()
{
}

void Worker::doWork(const QString &parameter) {

    QByteArray arr("\r\n",2);

    for(;;){
        s->write(arr);
        thread()->msleep(1);
    }

    QString result;
    /* ... here is the expensive or blocking operation ... */
    emit resultReady(result);
}
