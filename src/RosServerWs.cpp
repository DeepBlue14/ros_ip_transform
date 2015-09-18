#include "RosServerWs.h"


RosServerWs::RosServerWs(uint16_t port, QObject* parent) : QObject(parent)
{
    clientVecPtr = new QVector<QWebSocket*>();
    pub = new Publisher();
    webSocketServer = new QWebSocketServer(QStringLiteral("Chat Server"), QWebSocketServer::NonSecureMode, this);
    if(webSocketServer->listen(QHostAddress::Any, port) )
    {
        cout << "Chat Server listening on port" << port << endl;
        connect(webSocketServer, &QWebSocketServer::newConnection,
                this, &RosServerWs::handleConnectSlot);
    }
}


void RosServerWs::handleConnectSlot()
{
	cout << "@ RosServerWs::handleConnectSlot()" << endl;
    QWebSocket* pSocket = webSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &RosServerWs::handleRecv);
    connect(pSocket, &QWebSocket::disconnected, this, &RosServerWs::handleSockDisconnect);

    clientVecPtr->push_back(pSocket);// << pSocket;
}

void RosServerWs::handleRecv(QString message)
{
	cout << "@ RosServerWs::handleRecv(...)I heard: " << message.toStdString() << endl;
    QWebSocket* pSender = qobject_cast<QWebSocket*>(sender() );
    
    for(size_t i = 0; i < clientVecPtr->size(); i++)
    {
        //if(pClient != pSender) //don't echo message back to sender
        if(clientVecPtr->at(i) == pSender)
        {
            cout << "(Server) sending message: \"" << message.toStdString() << endl;
            clientVecPtr->at(i)->sendTextMessage(message);
        }
    }
}

void RosServerWs::handleSockDisconnect()
{
    QWebSocket* pClient = qobject_cast<QWebSocket*>(sender() );
    if(pClient)
    {
        clientVecPtr->removeAll(pClient);
        pClient->deleteLater();
    }
}


void RosServerWs::connect2Client(int port)
{
    ;
}


void RosServerWs::publishWs(const std_msgs::String::ConstPtr& msg)
{
    cout << "at publishWs(...)" << endl;
}


Publisher* RosServerWs::getPublisher()
{
    return pub;
}


RosServerWs::~RosServerWs()
{
    webSocketServer->close();

    for(size_t i = 0; i < clientVecPtr->size(); i++)
    {
        delete clientVecPtr->at(i);
        delete clientVecPtr;
    }
}
