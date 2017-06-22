QT += core gui network xml widgets
#QT -= core
TARGET = testDCS
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app
#INCLUDEPATH += include \

SOURCES +=  \
            ../../globalFunc/utils_func.cpp \
            ../../proxyDCS/domParserProtocol.cpp \
            ../../proxyDCS/nodeProtocol.cpp \
            ../../proxyDCS/proxyDCS.cpp \
            main.cpp \
    form.cpp





HEADERS +=  \
    ../../globalFunc/utils_func.h \
    ../../proxyDCS/domParserProtocol.h \
    ../../proxyDCS/nodeProtocol.h \
    ../../proxyDCS/proxyDCS.h \
    form.h \



FORMS += \
    form.ui



