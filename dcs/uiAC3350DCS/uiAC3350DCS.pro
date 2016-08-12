#-------------------------------------------------
#
# Project created by QtCreator 2016-04-29T17:06:51
#
#-------------------------------------------------

QT       += core gui xml network widgets svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lamps
TEMPLATE = app


SOURCES += main.cpp\
        mainwindowlamps.cpp \
    trans/cl_TransferdataUDP.cpp \
    trans/DomParser.cpp \
    trans/GenericNode.cpp \
    trans/GroupLabel.cpp \
    trans/Node.cpp \
    trans/Parameter.cpp \
    trans/Structure.cpp \
    trans/BinaryPresent.cpp \
    formlamps.cpp \
    formlamp.cpp

HEADERS  += mainwindowlamps.h \
    trans/cl_TransferdataUDP.h \
    trans/DomParser.h \
    trans/GenericNode.h \
    trans/GroupLabel.h \
    trans/Node.h \
    trans/Parameter.h \
    trans/Structure.h \
    trans/BinaryPresent.h \
    formlamps.h \
    formlamp.h

FORMS    += \
  mainwindowlamps.ui \
    formlamps.ui \
    formlamp.ui

RESOURCES += \
    res.qrc
