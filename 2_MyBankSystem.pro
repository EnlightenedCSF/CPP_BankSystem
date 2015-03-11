#-------------------------------------------------
#
# Project created by QtCreator 2015-03-11T19:31:07
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = 2_MyBankSystem
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    bank.cpp \
    client.cpp \
    individualclient.cpp \
    legalentity.cpp \
    account.cpp

HEADERS += \
    bank.h \
    client.h \
    individualclient.h \
    legalentity.h \
    account.h
