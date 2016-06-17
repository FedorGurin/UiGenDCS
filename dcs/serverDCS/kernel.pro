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
    kernel/kernel_mppm.cpp \   
    kernel/transferdataUDP.cpp \
    ../commonDCS/genericNode.cpp \
    ../commonDCS/groupLabel.cpp \
    ../commonDCS/node.cpp \
    ../commonDCS/parameter.cpp \
    ../commonDCS/pm.cpp \
    ../commonDCS/sio.cpp \
    ../commonDCS/structure.cpp \
    ../commonDCS/variantNode.cpp \
    ../commonDCS/variantState.cpp


HEADERS += \
    kernel/binaryPresent.h \
    kernel/domParser.h \
    kernel/kernel_mppm.h \
    kernel/transferdataUDP.h \
    ../commonDCS/genericNode.h \
    ../commonDCS/groupLabel.h \
    ../commonDCS/node.h \
    ../commonDCS/parameter.h \
    ../commonDCS/pm.h \
    ../commonDCS/sio.h \
    ../commonDCS/structure.h \
    ../commonDCS/variantNode.h \
    ../commonDCS/variantState.h
