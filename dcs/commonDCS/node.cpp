#include "node.h"

Node::Node()
{
    child.clear();

    parent      = 0;
    typeTree    = UNCERTAIN;
    pathName    = "/";
    displayName = "";
    idName      = "";
    picName     = "";
    left        = 0;
    right       = 0;
    bytes       = 0;
    offset      = 0;
    alignBytes  = 0;
}

Node::~Node()
{
    // TODO Auto-generated destructor stub
}
