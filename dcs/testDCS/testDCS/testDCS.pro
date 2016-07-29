QT += core network xml
QT -= gui

TARGET = testDCS
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  ../../globalFunc/utils_func.cpp \
            ../../proxyDCS/domParserProtocol.cpp \
            ../../proxyDCS/nodeProtocol.cpp \
            ../../proxyDCS/proxyDCS.cpp \
            main.cpp




HEADERS += \
    ../../globalFunc/utils_func.h \
    ../../proxyDCS/domParserProtocol.h \
    ../../proxyDCS/nodeProtocol.h \
    ../../proxyDCS/proxyDCS.h \



