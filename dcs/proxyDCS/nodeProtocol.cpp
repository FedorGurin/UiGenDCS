
#include "nodeProtocol.h"

NodeProtocol::NodeProtocol()
{
    child.clear();

    parent  = 0;
    pathName= "/";
    name    = "";
    left    = 0;
    right   = 0;
}

NodeProtocol::~NodeProtocol()
{

}
