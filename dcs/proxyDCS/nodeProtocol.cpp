
#include "nodeProtocol.h"
#include <QDebug>

NodeProtocol::NodeProtocol()
{
    child.clear();

    parent  = 0;
    pathName= "/";
    name    = "Unknown";
    left    = 0;
    right   = 0;
}

NodeProtocol::~NodeProtocol()
{

}
NodeBlock::NodeBlock(const QDomElement& element,NodeProtocol *parent):NodeProtocol()
{
    name        = element.attribute("name",         "Unknown");
    version     = element.attribute("version",      "0");
    uid         = element.attribute("uid",          "-1").toInt();
    nameModule  = element.attribute("nameModule",   "Unknown");

    parent->addChild(this);
    addParent(parent);
}
NodeInputBlock::NodeInputBlock(const QDomElement& element,
                               NodeProtocol *parent)
    :NodeBlock(element,parent)
{
    NodeProtocol *item=0;
    QDomElement ele=element.firstChildElement();
    while(!ele.isNull())
    {
        QString tagName = ele.tagName();
        item=0;
        if(tagName  == "param")    {item=new NodeParam(ele,this);}
        ele=ele.nextSiblingElement();
    }

}
NodeOutputBlock::NodeOutputBlock(const QDomElement& element,
                               NodeProtocol *parent)
    :NodeBlock(element,parent)
{
    NodeProtocol *item=0;
    QDomElement ele=element.firstChildElement();
    while(!ele.isNull())
    {
        QString tagName = ele.tagName();
        item=0;
        if(tagName  == "param")    {item=new NodeParam(ele,this);}
        ele=ele.nextSiblingElement();
    }

}
NodeUseCommand::NodeUseCommand(const QDomElement& element,
                               NodeProtocol *parent)
    :NodeBlock(element,parent)
{

}
NodeDefCommand::NodeDefCommand(const QDomElement& element,
                               NodeProtocol *parent)
    :NodeBlock(element,parent)
{
    NodeParam *item=0;
    QDomElement ele=element.firstChildElement();
    while(!ele.isNull())
    {
        QString tagName = ele.tagName();
        item=0;
        if(tagName  == "param")
        {
            item=new NodeParam(ele,this);
            QString direct = ele.attribute("direct", "Unknown");
            if(direct == "input")
            {
                args.append(item);
            }else if(direct == "output")
            {
                result.append(item);
            }else
            {
                qDebug()<<"Warning: field <Direct> is unknown.";
                qDebug()<<"Warning: incorrect command:"<<this->name;
            }
        }
        ele=ele.nextSiblingElement();
    }
}
NodeParam::NodeParam(const QDomElement& element,
                     NodeProtocol *parent)
    :NodeBlock(element,parent)
{

}
