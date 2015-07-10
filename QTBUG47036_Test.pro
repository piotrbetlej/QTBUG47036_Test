#-------------------------------------------------
#
# Project created by QtCreator 2015-07-06T21:05:50
#
#-------------------------------------------------

QT       += core network
QT       -= gui

TARGET = QTBUG47036_Test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp sockettx.cpp \
    worker.cpp \
    receiver.cpp
HEADERS += sockettx.h \
    worker.h \
    receiver.h
