/*
 * GenericNode.cpp
 *
 *  Created on: 02.09.2008
 *      Author: Fedor
 */

#include "GenericNode.h"


GenericNode::GenericNode() :Node(){
    // TODO Auto-generated constructor stub
    parent=0;
    child.clear();
    typeTree=DATA;
    variantNode=0;
    isDisplay=true;
    isHaveHelps=false;
    dataHelps="";
    fileNameHelps="";
    offset=0;
    directAddr=0;
    bytes=0;
    alignBytes=0;
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

void GenericNode::joinTree(Node *nodes)
{
    for(int i=0;i<this->child.size();i++)
    {
        for(int j=0;j<nodes->child.size();j++)
        {
            //qDebug()<<"DataNode is "<<displayName<<"VariantNode is "<<nodes->displayName;
            if(child[i]->idName==nodes->child[j]->idName)
            {
                ((GenericNode*)(this->child[i]))->joinTree(nodes->child[j]);
            }
        }
    }
}
GenericNode::~GenericNode() {
    // TODO Auto-generated destructor stub
    //qDeleteAll(child);
}
