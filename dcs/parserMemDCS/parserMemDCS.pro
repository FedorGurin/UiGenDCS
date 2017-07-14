#-------------------------------------------------
#
# Project created by QtCreator 2017-04-11T18:03:05
#
#-------------------------------------------------

QT       += xml
QT       -= gui

CONFIG += debug_and_release
CONFIG +=build_all

TARGET = parserMemDCS
TEMPLATE = lib
CONFIG += staticlib

unix{
    VERSION = 1.0.1

    CONFIG(debug, debug|release):TARGET = parserMemDCSd
    CONFIG(release, debug|release):TARGET = parserMemDCS
} else{
    CONFIG(debug, debug|release):TARGET = libParserMemDCSd
    CONFIG(release, debug|release):TARGET = libParserMemDCS
    #TARGET = $$qtLibraryTarget(libsubmodel)
}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
#DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    binaryPresent.cpp \
    domParser.cpp \
    node.cpp \
    parameter.cpp \
    structure.cpp \
    parserMemDCS.cpp

HEADERS += \
    binaryPresent.h \
    domParser.h \
    node.h \
    parameter.h \
    structure.h \
    parserMemDCS.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
