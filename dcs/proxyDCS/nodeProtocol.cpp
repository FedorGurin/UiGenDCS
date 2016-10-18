
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
char* NodeParam::binData(NodeParam* node)
{
    if(node->bin==0)
        node->bin=new char[node->bytes];

    switch(node->typeP)
    {
    case LDOUBLE:
    {
        long double p=node->value.toDouble()*node->factorValue;
        memcpy(node->bin,&p,node->bytes);
        break;
    }
    case DOUBLE:
    {
        double p=node->value.toDouble()*node->factorValue;
        memcpy(node->bin,&p,node->bytes);
        break;
    }
    case INT:
    {
        int p=node->value.toInt()*node->factorValue;
        memcpy(node->bin,&p,node->bytes);
        break;
    }
    case FLOAT:
    {
        float p=node->value.toFloat()*node->factorValue;
        memcpy(node->bin,&p,node->bytes);
        break;
    }
    case BOOL:
    {
        int p=node->value.toInt();
        memcpy(node->bin,&p,node->bytes);
        break;
    }
    case BIT:
    {

        break;
    }
    case UCHAR:
    {
        quint8 p=node->value.toUInt()*((uint)node->factorValue);
        memcpy(node->bin,&p,node->bytes);
        break;
    }
    case CHAR:
    {
        qint8 p=node->value.toInt()*((int)node->factorValue);
        memcpy(node->bin,&p,node->bytes);
        break;
    }
    case INT16:
    {
        quint16 p=node->value.toInt()*node->factorValue;
        memcpy(node->bin,&p,node->bytes);
        break;
    }
    case UINT:
    {
        unsigned p=node->value.toUInt()*node->factorValue;
        memcpy(node->bin,&p,node->bytes);
        break;
    }
    case MCHAR:
    {
        memcpy(node->bin,node->value.toLatin1().data(),node->bytes);
        break;
    }
    };

    return node->bin;
}
NodeParam::NodeParam(const QDomElement& element,
                     NodeProtocol *parent)
    :NodeBlock(element,parent)
{
    bin = 0;

}
