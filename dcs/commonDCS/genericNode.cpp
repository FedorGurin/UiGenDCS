
#include "genericNode.h"


GenericNode::GenericNode() :Node(){

    child.clear();
    parent      = 0;
    isDisplay   = true;
    offset      = 0;
    directAddr  = 0;
    bytes       = 0;
    alignBytes  = 0;
}

void GenericNode::addBytes(char b)
{
    bytes+=b;

    if(parent!=0)
    {
        if(parent->type()!=Node::PM)
        {
            ((GenericNode*)parent)->addBytes(b);
        }
    }
}
GenericNode::~GenericNode() {

}
