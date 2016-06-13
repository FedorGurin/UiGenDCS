#-------------------------------------------------
#
# Project created by QtCreator 2016-01-14T11:11:41
#
#-------------------------------------------------

QT       += core xml network

QT       -= gui

TARGET = binData
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    kernel/binaryPresent.cpp \    
    kernel/domParser.cpp \
    kernel/enginedata.cpp \
    kernel/genericNode.cpp \
    kernel/groupLabel.cpp \
    kernel/kernel_mppm.cpp \
    kernel/node.cpp \
    kernel/parameter.cpp \
    kernel/pm.cpp \
    kernel/sio.cpp \
    kernel/structure.cpp \
    kernel/transferdataUDP.cpp \
    kernel/variantNode.cpp \
    kernel/variantState.cpp

HEADERS += \
    kernel/binaryPresent.h \
    kernel/domParser.h \
    kernel/enginedata.h \
    kernel/genericNode.h \
    kernel/groupLabel.h \
    kernel/kernel_mppm.h \
    kernel/node.h \
    kernel/parameter.h \
    kernel/pm.h \
    kernel/sio.h \
    kernel/structure.h \
    kernel/transferdataUDP.h \
    kernel/variantNode.h \
    kernel/variantState.h
