#include "node.h"

Node::Node()
{
    child.clear();

    parent      = 0;
    pathName    = "/";
    displayName = "";
    idName      = "";
    picName     = "";
    left        = 0;
    right       = 0;
    bytes       = 0;
    offset      = 0;
    alignBytes  = 0;
    directAddr  = 0;
}
void Node::addBytes(char b)
{
    bytes+=b;

    if(parent!=0)
        parent->addBytes(b);
}
Node::~Node()
{
    // TODO Auto-generated destructor stub
}
