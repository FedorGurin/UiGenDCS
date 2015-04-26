#-------------------------------------------------
#
# Project created by QtCreator 2014-11-07T17:57:18
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = mppm
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    cl_TransferdataUDP.cpp \
    enginedata.cpp

HEADERS += \
    enginedata.h
