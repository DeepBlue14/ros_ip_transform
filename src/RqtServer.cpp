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
    pubPtr = new ros::Publisher();
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


void RqtServer::messageBridge(const std_msgs::String::ConstPtr& msg)
{
    //convert ROS string --> STD string --> QT string
    std::string stdMsg = msg->data;
    qtMsg = QString::fromStdString(stdMsg);
    
    //FIXME: ???should it make one falseprince socket in the constructor; or create one for each subscriber???
    QWebSocket falsePrince;
    connect(&falsePrince, &QWebSocket::textMessageReceived, this, &RqtServer::processMessage);
    
    //if(qtMsg.compare("Arise, my robot army!") != 0 )
    {
        std::cout << "about to emit signal" << std::endl;
        emit falsePrince.textMessageReceived(qtMsg);
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
        std::cout << "looping" << std::endl;
        if(pClient != pSender) //don't echo message back to sender
        {
            std::cout << "(RqtServer) sending message: \"" << message.toStdString() << std::endl;
            pClient->sendTextMessage(message);
        }
    }
    
    if(!message.contains(QRegExp("I am robot_[0-9]{3}$")) )
    {
        std::cout << "publishing user message:" << message.toStdString() << std::endl;
        std_msgs::String msg;
        std::stringstream ss;
        ss << message.toStdString();
        msg.data = ss.str();
        pubPtr->publish(msg);
        message = "null";
    }
    
}


ros::Publisher* RqtServer::getPublisher()
{
    return pubPtr;
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
