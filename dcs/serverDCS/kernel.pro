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
    kernel/transferdataUDP.cpp


HEADERS += \
    kernel/binaryPresent.h \
    kernel/domParser.h \
    kernel/kernel_mppm.h \
    kernel/transferdataUDP.h
