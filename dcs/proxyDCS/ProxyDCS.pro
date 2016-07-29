#-------------------------------------------------
#
# Project created by QtCreator 2016-06-14T10:20:29
#
#-------------------------------------------------

QT       += network xml

QT       -= gui

TARGET = ProxyDCS
TEMPLATE = lib
CONFIG += staticlib

SOURCES += proxyDCS.cpp \
    nodeProtocol.cpp \
    domParserProtocol.cpp

HEADERS += proxyDCS.h \
    nodeProtocol.h \
    domParserProtocol.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
