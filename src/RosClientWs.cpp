#include "RosClientWs.h"


RosClientWs::RosClientWs(const QUrl& url, QObject* parent) : QObject(parent)
{
    pub = new Publisher();
    urlPtr = new QUrl(url);
    cout << "WebSocket server:" << url.toString().toStdString() << endl;
    connect(&webSocket, &QWebSocket::connected, this, &RosClientWs::handleConnectRequest);
    connect(&webSocket, &QWebSocket::disconnected, this, &RosClientWs::signalClosed);
    webSocket.open(QUrl(url) );
}


void RosClientWs::handleConnectRequest()
{
    cout << "WebSocket connected" << endl;
    connect(&webSocket, &QWebSocket::textMessageReceived, this, &RosClientWs::handleRecv);
    webSocket.sendTextMessage(QStringLiteral("Hello, world!") );
    webSocket.sendTextMessage(QStringLiteral("Hello, world!") );
}


void RosClientWs::handleRecv(QString message)
{
    cout << "Message received:" << message.toStdString() << endl;
    
    std_msgs::String rosStr;
    rosStr.data = message.toStdString();
    
    pub->publish(rosStr);
}


void RosClientWs::connect2Server(RosClientWs* client, QCoreApplication* app)
{
    appPtr = app;
    connect(client, &RosClientWs::signalClosed, app, &QCoreApplication::quit);
}


void RosClientWs::spinWs()
{
    appPtr->exec();
}


Publisher* RosClientWs::getPublisher()
{
    return pub;
}


RosClientWs::~RosClientWs()
{
    webSocket.close();
}
