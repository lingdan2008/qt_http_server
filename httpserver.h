#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QObject>
#include <QtCore>
#include <QDebug>
#include <QtNetwork/QtNetwork>
#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QtNetwork>
#include <QtNetwork>

#define DEF_HTTP_TIMEOUT    1000
#define DEF_HTTP_VERSION    "POST / HTTP/1.1"
#define DEF_HTTP_LENGTH     "Content-Length:"
#define DEF_HTTP_TYPE       "Content-Type"

class HttpServer : public QObject
{
    Q_OBJECT
public:
    static HttpServer &instance();
    void start(const QHostAddress &addr = QHostAddress::Any, const qint64 &port = 8000);
    void stop();

private:
    explicit HttpServer(QObject *parent = 0);
    ~HttpServer();
    Q_DISABLE_COPY(HttpServer)

signals:

public slots:

public slots:
    void slotNewConnection();
    void slotReadyRead();

private:
    QTcpServer *m_pTcpServer;

    int m_nRequestSize;
    int m_nContentLength;
};

#endif // HTTPSERVER_H
