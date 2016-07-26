QT += core network xml
QT -= gui

TARGET = testDCS
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ../../globalFunc/utils_func.cpp \
    ../../proxyDCS/proxyDCS.cpp


HEADERS += \
    ../../globalFunc/utils_func.h \
    ../../proxyDCS/proxyDCS.h


