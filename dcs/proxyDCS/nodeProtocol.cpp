
#include "nodeProtocol.h"

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
    name        = element.attribute("name","Unknown");
    version     = element.attribute("version","0");
    uid         = element.attribute("uid","-1").toInt();
    nameModule  = element.attribute("nameModule","Unknown");

    parent->addChild(this);
    addParent(parent);
}
NodeInputBlock::NodeInputBlock(const QDomElement& element,
                               NodeProtocol *parent)
    :NodeBlock(element,parent)
{

}
NodeOutputBlock::NodeOutputBlock(const QDomElement& element,
                               NodeProtocol *parent)
    :NodeBlock(element,parent)
{

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

}
NodeParam::NodeParam(const QDomElement& element,
                     NodeProtocol *parent)
    :NodeBlock(element,parent)
{

}
