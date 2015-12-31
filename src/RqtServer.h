#ifndef RQT_SERVER_H
#define RQT_SERVER_H

#include <ros/ros.h>

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class RqtServer : public QObject
{
    Q_OBJECT
public:
    explicit RqtServer(quint16 port, QObject *parent = Q_NULLPTR);
    virtual ~RqtServer();

private Q_SLOTS:
    void onNewConnection();
    void processMessage(QString message);
    void socketDisconnected();

private:
    QWebSocketServer* m_pWebSocketServer;
    QList<QWebSocket*> m_clients;
};

#endif /* RQT_SERVER_H */
