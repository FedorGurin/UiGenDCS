
#include "sio.h"
#include "../globalFunc/math_func.h"

SIO::SIO(const QDomElement& element, GenericNode *parent):GenericNode()
{
    displayName=element.attribute("displayName","");
    idName=     element.attribute("idName","");
    comment=    element.attribute("comment","");
    isDisplay=  ((element.attribute("isDisplay")).toInt());
    shortName=  element.attribute("shortName","");
    readOnly=   element.attribute("readOnly","0").toInt();

    if(idName=="")
        idName=shortName;

    fileNameHelps=element.attribute("fileNameHelps","");
    if(fileNameHelps!="")
    {
        fileNameHelps=/*qApp->applicationDirPath()+"/helps/"+*/fileNameHelps;
        isHaveHelps=true;
    }else
        isHaveHelps=false;

    //listForCompleter<<displayName;

    parent->addChild(this);
    addParent(parent);

    if(isDisplay==true)
        parent->addVisionChild(this);

    //addr=0;
    indexInTable=-1;
    nameRequest.clear();

    GenericNode *p=parent;
    while(p->type()!=Node::PM)
    {
        p=(GenericNode*)p->parent;
    }
    nameRequest=p->shortName;
    //if(parent->type()==Node::PM)
    //

    nameRequest+="_"+shortName;
}

SIO::~SIO() {
        // TODO Auto-generated destructor stub
}
