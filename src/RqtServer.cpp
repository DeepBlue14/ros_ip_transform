#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QWebSocket>
#include <QtCore/QDebug>

#include <iostream>

#include "RqtServer.h"

QT_USE_NAMESPACE

RqtServer::RqtServer(quint16 port, QObject* parent) :
    QObject(parent),
    m_pWebSocketServer(Q_NULLPTR),
    m_clients()
{
    m_pWebSocketServer = new QWebSocketServer(QStringLiteral("Chat Server"),
                                              QWebSocketServer::NonSecureMode,
                                              this);
    if(m_pWebSocketServer->listen(QHostAddress::Any, port) )
    {
        qDebug() << "Chat Server listening on port" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &RqtServer::onNewConnection);
    }
}


void RqtServer::onNewConnection()
{
	std::cout << "@ RqtServer::onNewConnection()" << std::endl;
    QWebSocket* pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &RqtServer::processMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &RqtServer::socketDisconnected);

    m_clients << pSocket;
}

void RqtServer::processMessage(QString message)
{
	std::cout << "@ RqtServer::processMessage(...)" << std::endl;
	std::cout << "I heard: " << message.toStdString() << std::endl;
    QWebSocket* pSender = qobject_cast<QWebSocket*>(sender() );
    Q_FOREACH (QWebSocket* pClient, m_clients)
    {
        if(pClient != pSender) //don't echo message back to sender
        {
            std::cout << "(RqtServer) sending message: \"" << message.toStdString() << std::endl;
            pClient->sendTextMessage(message);
        }
    }
}

void RqtServer::socketDisconnected()
{
    QWebSocket* pClient = qobject_cast<QWebSocket*>(sender() );
    if(pClient)
    {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}


RqtServer::~RqtServer()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end() );
}
