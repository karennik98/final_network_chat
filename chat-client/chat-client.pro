#-------------------------------------------------
#
# Project created by QtCreator 2012-02-20T22:18:32
#
#-------------------------------------------------

QT       += core gui network

TARGET = chat-client
TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES +=  main.cpp\
            chatwindow.cpp \
            ChatClient.cpp \
            ChatMessages.cpp \
    ChatAuthWindow.cpp \
    smileswidgets.cpp \
    ListOfChannels.cpp \
    ConnectionProperties.cpp \
    RegisterBot.cpp \
    createchanneldialog.cpp \
    ChatWidgets.cpp \
    ChannelThemeDialog.cpp \
    UserInfoDialog.cpp \
    StatusDialog.cpp \
    OwnerProfile.cpp

HEADERS  += chatwindow.h \
            ChatClient.h \
            ChatMessages.h \
    ChatAuthWindow.h \
    smileswidgets.h \
    ListOfChannels.h \
    ConnectionProperties.h \
    RegisterBot.h \
    createchanneldialog.h \
    ChatWidgets.h \
    ChannelThemeDialog.h \
    UserInfoDialog.h \
    StatusDialog.h \
    OwnerProfile.h

FORMS    += chatwindow.ui \
    ChatAuthWindow.ui \
    ConnectionProperties.ui \
    ListOfChannels.ui \
    createchanneldialog.ui \
    ChannelThemeDialog.ui \
    UserInfoDialog.ui \
    StatusDialog.ui \
    OwnerProfile.ui
