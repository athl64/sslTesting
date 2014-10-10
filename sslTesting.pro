#-------------------------------------------------
#
# Project created by QtCreator 2014-09-30T00:09:45
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sslTesting
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    account_details.cpp

HEADERS  += mainwindow.h \
    account_details.h

FORMS    += mainwindow.ui \
    account_details.ui
