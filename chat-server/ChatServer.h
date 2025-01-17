#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include "ChatMessages.h"
#include "ClientList.h"
#include "configmanager.h"
#include "logger.h"

class ChatServer : public QObject
{
    Q_OBJECT

public:
    explicit ChatServer(QObject *parent = nullptr);

    bool startServer(const quint16 nPort);
    void stopServer(const QString &shutdownReason = "");

private:
    void processMessage(ChannelMessage *msg);
    void processMessage(AuthorizationRequest *msg, QTcpSocket *socket);
    void processMessage(DisconnectMessage *msg);
    void processMessage(RegistrationRequest *msg, QTcpSocket *socket);
    void processMessage(ChannelListRequest *msg, QTcpSocket *socket);
    void processMessage(ChannelJoinRequest *msg, QTcpSocket *socket);
    void processMessage(ChannelLeaveMessage *msg);
    void processMessage(ChannelCreateRequest *msg);
    void processMessage(ChannelThemeChanged *msg);
    void processMessage(ClientStatusChanged *msg);
    void processMessage(UserInfoRequest *msg, QTcpSocket *socket);
    void processMessage(UserInfoChanged *msg);
    void processMessage(PasswordChangeRequest *msg);

    void sendMessageToClient(QTcpSocket *socket, ChatMessageBody *msgBody);
    void sendMessageToClient(QString username, ChatMessageBody *msgBody);

    void sendMessageToChannel(QString channelName, ChatMessageBody *msgBody);

    QString getSendableState(QString clientName);

signals:
    void serverLog(ErrorStatus, QString &message);
    void channelLog(QString &name, QString &message);
    void updateTable(QString tablename);

private slots:
    void serverGotNewConnection();
    void serverGotNewMessage();
    void replyLog(ErrorStatus status, QString &str);

public slots:

    void setConfig(ChatServerConfig *pointer);

public:
    enum { defaultPort = 33033 };

private:
    QTcpServer *m_tcpServer;
    quint16 m_nextBlockSize;
    quint16 m_port;
    GeneralClientList m_clientList;
};

#endif // CHATSERVER_H
