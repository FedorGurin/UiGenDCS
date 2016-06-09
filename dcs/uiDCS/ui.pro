#-------------------------------------------------
#
# Project created by QtCreator 2015-09-04T15:26:15
#
#-------------------------------------------------

QT       += core \
            gui \
            network \
            xml \
            svg \
            opengl \
            widgets \
            multimedia

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS_DEBUG += -mno-align-double

TARGET = mainDcs
TEMPLATE = app

FORMS += \
    ui/mainformsocket.ui \
    ui/tableformsocket.ui
HEADERS += \
    ui/cl_DataForVxWorks_Su30SM.h \
    ui/cl_DataForVxWorks_Su35_1.h \
    ui/cl_DataForVxWorksT50Bins.h \
    ui/cl_MainFormSocket.h \
    ui/cl_TableFormSocket.h \
    ui/cl_TargetsForm.h \
    ui/cl_transmit.h \
    ui/EngineDataUI.h \
    ui/GenericData.h \
    ui/SettingUI.h
SOURCES +=   main.cpp \
    ui/cl_DataForVxWorks_Su30SM.cpp \
    ui/cl_DataForVxWorks_Su35_1.cpp \
    ui/cl_DataForVxWorksT50Bins.cpp \
    ui/cl_MainFormSocket.cpp \
    ui/cl_TableFormSocket.cpp \
    ui/cl_TargetsForm.cpp \
    ui/cl_transmit.cpp \
    ui/EngineDataUI.cpp \
    ui/SettingUI.cpp



