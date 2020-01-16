#include "httpserver.h"

HttpServer::HttpServer(QObject *parent) : QObject(parent)
{
    qDebug() << __FUNCTION__;

    m_pTcpServer = new QTcpServer(this);
    m_pTcpServer->setMaxPendingConnections(1024);

    QObject::connect(m_pTcpServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
}

HttpServer::~HttpServer()
{
    qDebug() << __FUNCTION__;
}

HttpServer &HttpServer::instance()
{
    qDebug() << __FUNCTION__;

    static HttpServer objHttpServer;
    return objHttpServer;
}

void HttpServer::run(const QHostAddress &addr, const qint64 &port)
{
    qDebug() << __FUNCTION__ << addr.toString() << port;

    m_pTcpServer->listen(addr, port);
}

void HttpServer::slotNewConnection()
{
    qDebug() << __FUNCTION__;

    // Get the time
    m_nRequestSize = 0;
    m_nContentLength = 0;

    QTcpSocket *pTcpSocket = m_pTcpServer->nextPendingConnection();

    QObject::connect(pTcpSocket, SIGNAL(readyRead()), this, SLOT(slotNewConnection()));
}

void HttpServer::slotReadyRead()
{
    qDebug() << __FUNCTION__;

    QTcpSocket *pTcpSocket = qobject_cast<QTcpSocket*>(sender());
    if(pTcpSocket) {
        QByteArray baResponse = QString("<h1><center>Hello World</center></h1>\r\n").toUtf8();
        QString sHttp = "HTTP/1.1 200 OK\r\n";
        sHttp += "Server: nginx\r\n";
        sHttp += "Content-Type: text/html;charset=utf-8\r\n";
        sHttp += "Connection: keep-alive\r\n";
        sHttp += QString("Content-Length: %1\r\n\r\n").arg(QString::number(baResponse.size()));

        pTcpSocket->write(sHttp.toUtf8());
        pTcpSocket->write(baResponse);
        pTcpSocket->flush();
        pTcpSocket->close();

        qDebug() << "Response data:" << QString(baResponse);
        qDebug() << "Response size:" << baResponse.size();

        /*QByteArray baRequest = pTcpSocket->readAll();
        QString sRequest(baRequest);

        qDebug() << "Request data:" << QString(baRequest);
        qDebug() << "Request size:" << baRequest.size();

        bool bMatchHeader = sRequest.startsWith(DEF_HTTP_VERSION);
        if(bMatchHeader) {
            int nIdxBegin = sRequest.indexOf(DEF_HTTP_LENGTH);
            if(0 <= nIdxBegin) {
                int nIdxEnd = sRequest.indexOf("\r\n", nIdxBegin);

                QString sSub = sRequest.mid(nIdxBegin + strlen(DEF_HTTP_LENGTH), nIdxEnd - nIdxBegin - strlen(DEF_HTTP_LENGTH));
                m_nContentLength = sSub.toInt();
                qDebug() << "Content-Length:" << m_nContentLength;

                if(baRequest.size() > m_nContentLength) {
                    goto do_exit;
                }
            }
        }
        else {
            m_nRequestSize += baRequest.size();
        }

        if(m_nRequestSize == m_nContentLength) {
do_exit:
            QByteArray baResponse = QString("<h1><center>Hello World</center></h1>\r\n").toUtf8();
            QString sHttp = "HTTP/1.1 200 OK\r\n";
            sHttp += "Server: nginx\r\n";
            sHttp += "Content-Type: text/html;charset=utf-8\r\n";
            sHttp += "Connection: keep-alive\r\n";
            sHttp += QString("Content-Length: %1\r\n\r\n").arg(QString::number(baResponse.size()));

            pTcpSocket->write(sHttp.toUtf8());
            pTcpSocket->write(baResponse);
            pTcpSocket->flush();
            pTcpSocket->close();

            qDebug() << "Response data:" << QString(baResponse);
            qDebug() << "Response size:" << baResponse.size();
        }*/
    }
}
