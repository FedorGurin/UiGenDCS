/*
 * PModule.cpp
 *
 *  Created on: 27.08.2008
 *      Author: Fedor
 */

#include "pm.h"
#include "../globalFunc/math_func.h"

PModule::PModule(const QDomElement& element,GenericNode *parent):GenericNode()
{
    shortName=  element.attribute("shortName");
    displayName=element.attribute("displayName","None");
    idName=     element.attribute("idName","");

    if(idName=="")
        idName=shortName;

    comment=    element.attribute("comment");
    isDisplay=  ((element.attribute("isDisplay")).toInt());

    fileNameHelps=element.attribute("fileNameHelps","");
    if(fileNameHelps!="")
    {
        fileNameHelps=/*qApp->applicationDirPath()+"/helps/"+*/fileNameHelps;
        isHaveHelps=true;
    }
    else
        isHaveHelps=false;

    listForCompleter<<displayName;

    parent->addChild(this);
    addParent(parent);

    if(isDisplay==true)
        parent->addVisionChild(this);
}

PModule::~PModule()
{
    // TODO Auto-generated destructor stub
}
