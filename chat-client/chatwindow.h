#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include "smileswidgets.h"
#include "ChatClient.h"
#include "RegisterBot.h"
#include "ListOfChannels.h"
#include "ChatWidgets.h"
#include "StatusDialog.h"
#include "UserInfoDialog.h"
#include "OwnerProfile.h"

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();
	
private:
    Ui::ChatWindow *ui;
    ChatClient *m_client;
    smilesWidget *m_smiles;
    ListOfChannels *m_channelListDialog;
    ChatTabWidget *m_tabWidget;
    QMenu m_menu;
    StatusDialog m_statusDialog;
    UserInfoDialog m_userInfoDialog;
    OwnerProfile m_ownerProfile;
    void setMyChannelList(QMap<QString,QString> list);

protected:
    virtual void closeEvent(QCloseEvent *event);

signals:
    void sendMessage(const QString &, const QString &);
    void sendAllChannelsList(QMap<QString,QString>);
    void requestUserList(QString);
    void replyJoinRequestResult(QString, bool);
    void statusChanged(QString status);

private slots:
    void postMessage();
    void setText(QString text);
    void insertText(QString smileName);
    void processChannelList(QMap<QString,QString> list, ChatClient::ChannelListType type);
    void getChannelJoinResult(QString channelName, bool result);
    void onChangeStatus(QString status);
    void onChangeStatus(int index);

    void on_menuButton_clicked();

public slots:
    void connectToServer(QString username, QString password, QTcpSocket *socket);
};

#endif // CHATWINDOW_H
