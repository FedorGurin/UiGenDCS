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

TARGET = mppm
TEMPLATE = app

DEPENDPATH += .
INCLUDEPATH += .

FORMS +=
    xml/binform.ui \
    xml/dialform.ui \
    xml/dumpform.ui \
    xml/extendedsearhform.ui \
    xml/formRenameVariant.ui \
    xml/formsetname.ui \
    xml/formsetting.ui \
    xml/formstatusexitprogram.ui \
    xml/formwait.ui \
    xml/sliderhform.ui \
    xml/slidervform.ui \
    xml/xmlmodelview.ui

HEADERS +=
    xml/BinaryPresent.h \
    xml/binform.h \
    xml/cl_TransferdataUDP.h \
    xml/dialform.h \
    xml/DomParser.h \
    xml/dumpform.h \
    xml/enginedata.h \
    xml/extendedsearhform.h \
    xml/formRenameVariant.h \
    xml/formsetname.h \
    xml/formsetting.h \
    xml/formstatusexitprogram.h \
    xml/formwait.h \
    xml/GenericNode.h \
    xml/GroupLabel.h \
    xml/ItemDelegate.h \
    xml/itemselectionmodel.h \
    xml/ListRequest.h \
    xml/ModelData.h \
    xml/Node.h \
    xml/Parameter.h \
    xml/PModule.h \
    xml/SettingXML.h \
    xml/SIO.h \
    xml/sliderhform.h \
    xml/slidervform.h \
    xml/Structure.h \
    xml/VariantNode.h \
    xml/VariantState.h \
    xml/xmlmodelview.h \
    globalFunc/gl_func.h \
    globalFunc/Matrix3D_D.h \
    globalFunc/mercator.h \
    globalFunc/Vector3D_D.h \
    CommonEngineData/CommonEngineData.h

SOURCES +=
    xml/BinaryPresent.cpp \
    xml/binform.cpp \
    xml/cl_TransferdataUDP.cpp \
    xml/dialform.cpp \
    xml/DomParser.cpp \
    xml/dumpform.cpp \
    xml/enginedata.cpp \
    xml/extendedsearhform.cpp \
    xml/formRenamevariant.cpp \
    xml/formsetname.cpp \
    xml/formsetting.cpp \
    xml/formstatusexitprogram.cpp \
    xml/formwait.cpp \
    xml/GenericNode.cpp \
    xml/GroupLabel.cpp \
    xml/ItemDelegate.cpp \
    xml/itemselectionmodel.cpp \
    xml/ListRequest.cpp \
    xml/ModelData.cpp \
    xml/Node.cpp \
    xml/Parameter.cpp \
    xml/PModule.cpp \
    xml/SettingXMLl.cpp \
    xml/SIO.cpp \
    xml/sliderhform.cpp \
    xml/slidervform.cpp \
    xml/Structure.cpp \
    xml/VariantNode.cpp \
    xml/VariantState.cpp \
    xml/xmlmodelview.cpp \   
    main.cpp



