QT += core
QT -= gui

CONFIG += c++11

TARGET = kami
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

HEADERS += \
    colorful.h \
    kbhit.h \
    gamemanager.h
