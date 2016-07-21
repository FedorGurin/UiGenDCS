QT += core network
QT -= gui

TARGET = testDCS
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ../../proxyDCS/proxyDCS.cpp

HEADERS += \
    ../../proxyDCS/proxyDCS.h

