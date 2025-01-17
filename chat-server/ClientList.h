#ifndef CLIENTLIST_H
#define CLIENTLIST_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QtNetwork/QTcpSocket>
#include <QtSql>
#include <QTableView>
#include "ChatMessages.h"
#include "logger.h"
/*
TODO for future:
*/
class ChatClient
{
private:
    QString m_username;
    QString m_userInfo;
    QString m_userPassword;
    QString m_userState;
    QTcpSocket *m_userSocket;
public:
    ChatClient(): m_userSocket(nullptr) {}

    QString &username();
    QString &userInfo();
    QString &password();
    QString &userState();
    QTcpSocket *userSocket() const;

    void setUsername(QString name);
    void setUserInfo(QString info);
    void setPassword(QString pass);
    void setUserState(QString state);
    void setUserSocket(QTcpSocket *socket);
};

class ChatChannel
{
private:
    QString m_name;
    QString m_description;
    QString m_topic;

public:
    QStringList userList;
    // should be private. but i couldn't find a nice way to provide
    // an interface to iterate all the clients in the channel
    ChatChannel() {}
    QString &name();
    void setName(QString name);

    QString &description();
    void setDescription(QString desc);

    QString &topic();
    void setTopic(QString topic);

    void addClient(QString username);
    void deleteClient(QString username);

    bool hasClient(QString username);

    void deleteAllClients();
};

class DBManager: public QObject
{
    Q_OBJECT
private:
    QSqlDatabase m_DB;
    QString m_DBName;
    const QString m_clientTableName;
    const QString m_channelTableName;
    const QString m_membershipTableName;
    const QString m_DBFileName;
    bool createClientsTable();
    bool createChannelsTable();
    bool createMembershipTable();
public:
    explicit DBManager(QObject *parent = 0);
    ~DBManager();
    void connectToDB();
    void disconnectDB();
    //general methods
    void createDB();
    // client table
    bool hasClient(QString username);
    ChatClient getClient(QString username);
    void setClient(ChatClient &client);

    // channel table
    bool hasChannel(QString channelName);
    ChatChannel getChannel(QString channelName);
    void setChannel(ChatChannel &channel);
    //membership table
    bool isMembership(QString username, QString channelName);
    void addMembership(QString username, QString channelName);
    void deleteMembership(QString username, QString channel);
    // methods for initializing channels in general client list
    QVector<ChatChannel> getChannelList();
signals:
    void logMessage(ErrorStatus, QString&);
};

class GeneralClientList: public QObject
{
    Q_OBJECT
private:
    QMap<QString, ChatClient> m_generalClientList;
    QVector<ChatChannel> m_channelList;
    DBManager m_DB;

public:
    using userSocketsList_t = QVector<QTcpSocket *>;
    using userSocketsListIterator_t = QVectorIterator<QTcpSocket *>;

    enum AuthResult
    {
        arAllreadyAuthorized,
        arAuthSuccess,
        arWrongAuthData
    };
    enum RegResult
    {
        rrBadUsername,
        rrOccupiedUsername,
        rrRegSuccess
    };
    enum CreateChannelResult
    {
        ccrTooManyChannels,
        ccrBadName,
        ccrSuccess
    };
    explicit GeneralClientList(QObject *parent = 0);
    void readChannelsFromDB();
    ChatChannel getChannel(QString &channelName);
    ChatClient getClient(const QString &username);
    bool hasClient(QString username);
    bool hasChannel(QString channelName);
    QMap<QString, QString> getChannelsForClient(QString username);
    QStringList getClientsForChannel(QString channelName);
    QMap<QString, QString> getAllChanells();
    RegResult registrate(QString username, QString password);
    AuthResult authorize(QString username, QString password, QTcpSocket *socket);
    void disconnect(QString username);
    void joinChannel(QString username, QString channelName);
    void leaveChannel(QString username, QString channelName);
    void disconnectAll();
    userSocketsList_t *getAllSockets();    
    CreateChannelResult createChannel(QString channelName, QString description, QString topic);
    void updateClient(ChatClient &client);
    void updateChannel(ChatChannel &channel);
signals:
    void logMessage(ErrorStatus, QString &);

private slots:
    void replyLog(ErrorStatus, QString &param);

};

#endif // CLIENTLIST_H
