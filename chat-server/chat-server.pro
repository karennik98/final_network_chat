#-------------------------------------------------
#
# Project created by QtCreator 2012-02-18T02:08:40
#
#-------------------------------------------------

QT       += core gui network sql

TARGET = chat-server
TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += 	main.cpp\
        	statswindow.cpp \
    		ChatMessages.cpp \
            ChatServer.cpp \
    		configmanager.cpp \
    		logger.cpp \
            ClientList.cpp

HEADERS +=	statswindow.h \
    		ChatMessages.h \
            ChatServer.h \
    		configmanager.h \
            logger.h \
            ClientList.h

FORMS    += statswindow.ui
