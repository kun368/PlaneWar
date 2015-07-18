#-------------------------------------------------
#
# Project created by QtCreator 2015-07-07T12:09:23
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PlaneWar
TEMPLATE = app

CONFIG += c++11


SOURCES += main.cpp \
    myview.cpp \
    myplane.cpp \
    gamecontroller.cpp \
    enemy.cpp \
    bullet.cpp \
    ball.cpp \
    logindlg.cpp \
    collision.cpp \
    constants.cpp \
    flowback.cpp \
    lifeadder.cpp \
    circle.cpp \
    helpdlg.cpp \
    boss.cpp \
    bossball.cpp \
    wingplane.cpp \
    wingbullet.cpp \
    rank.cpp \
    tip.cpp

HEADERS  += \
    myview.h \
    myplane.h \
    gamecontroller.h \
    enemy.h \
    bullet.h \
    ball.h \
    constants.h \
    logindlg.h \
    collision.h \
    flowback.h \
    lifeadder.h \
    circle.h \
    helpdlg.h \
    boss.h \
    bossball.h \
    wingplane.h \
    wingbullet.h \
    rank.h \
    tip.h

FORMS    += \
    logindlg.ui \
    helpdlg.ui

DISTFILES +=

RESOURCES += \
    my.qrc

RC_FILE  += myico.rc
