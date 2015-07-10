#include "worker.h"

Worker::Worker()
{
}

void Worker::doWork(const QString &parameter) {

    QByteArray arr("\r\n",2);

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

    for(;;){
        s->write(headerStr.toUtf8());
        thread()->msleep(1);
    }

    QString result;
    /* ... here is the expensive or blocking operation ... */
    emit resultReady(result);
}
