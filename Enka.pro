#-------------------------------------------------
#
# Project created by QtCreator 2016-06-01T18:04:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Enka
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    deck.cpp \
    card.cpp \
    player.cpp \
    icon.cpp

HEADERS  += mainwindow.h \
    deck.h \
    card.h \
    player.h \
    icon.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
