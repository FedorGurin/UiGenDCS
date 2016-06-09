/*
 * VariantState.cpp
 *
 *  Created on: 16.09.2008
 *      Author: Fedor
 */

#include "VariantState.h"

VariantState::VariantState():Node()
{
    // TODO Auto-generated constructor stub
    typeTree=VARIANT;
    setVariantState();
    variant=0;

}
VariantState::VariantState(const QString &name):Node()
{
    typeTree=VARIANT;
    variant=0;

    displayName=name;
    idName=name;
    setVariantState();
}
void VariantState::deleteVariantState()
{
    if(parent!=0)
    {
        parent->child.removeOne(this);
        delete this;
    }
}
VariantState::VariantState(const QDomElement& element, VariantState* parent):Node()
{
    typeTree=VARIANT;
    variant=0;

    displayName=element.attribute("displayName","?");

    idName=element.attribute("idName","");
    if(idName=="") idName=displayName;

    setVariantState();

    if(element.tagName()=="variantState")
    {                     
        setVariantState();
    }else if(element.tagName()=="variantPM")
    {        
        comment=element.attribute("comment","");
        setVariantPM();

    }else if(element.tagName()=="pmodule")
    {
        comment=element.attribute("comment","");
        setPModule();
    }
    else if(element.tagName()=="sio")
    {
        comment=element.attribute("comment","");
        setSIO();
    }
    else _type=EMPTY;

    addParent(parent);
    parent->addChild(this);

}
//! активировать данный варинат
void VariantState::setVariant(void)
{
    for(int i=0;i<child.size();i++)
    {
        VariantState *variantNode=static_cast<VariantState* >(child[i]);
        if(variantNode->variant!=0)variantNode->variant->setVariant();
    }
}
void VariantState::addTailVariantPM(VariantNode *varNode)
{
    varNode->variantState.push_back(this);
    variant=varNode;
    variant->displayName=QString(varNode->displayName);
    variant->idName=QString(varNode->idName);
    //! добавим хвостик от variantPM
    Node *pmoduleNode=varNode->child[0];
    Node *sioNode=pmoduleNode->child[0];

    VariantState *variantTemp=new VariantState(pmoduleNode->idName);
    variantTemp->setPModule();
    this->addChild(variantTemp);

    VariantState *variantTemp1=new VariantState(sioNode->idName);
    variantTemp1->setSIO();
    variantTemp->addChild(variantTemp1);
}

void VariantState::save(QDomDocument &domDocument,QDomElement& parent, VariantState *parentNode)
{
    for(int i=0;i<parentNode->child.size();i++)
    {
        Node *node=parentNode->child[i];
        VariantState *variantNode=static_cast<VariantState* >(node);
        switch(node->type())
        {
            case (Node::VARIANTSTATE):
            {
                QDomElement ele=domDocument.createElement("variantState");
                parent.appendChild(ele);

                ele.setAttribute("idName",variantNode->idName);
                ele.setAttribute("displayName",variantNode->displayName);
                save(domDocument,ele,variantNode);
                break;
            }
            case Node::VARIANTPM:
            {
                if(variantNode->variant==0) break;
                QDomElement ele=domDocument.createElement("variantPM");
                parent.appendChild(ele);

                ele.setAttribute("idName",variantNode->variant->idName);
                ele.setAttribute("displayName",variantNode->displayName);
                save(domDocument,ele,variantNode);                
                break;
            }
            case Node::PM:
            {
                QDomElement ele=domDocument.createElement("pmodule");
                parent.appendChild(ele);

                ele.setAttribute("idName",variantNode->idName);
                ele.setAttribute("displayName",variantNode->displayName);
                save(domDocument,ele,variantNode);
                break;
            }
            case Node::SIO:
            {
                QDomElement ele=domDocument.createElement("sio");
                parent.appendChild(ele);

                ele.setAttribute("idName",variantNode->idName);
                ele.setAttribute("displayName",variantNode->displayName);
                break;
            }
        };
    }
}
VariantState::~VariantState() {
	// TODO Auto-generated destructor stub
}
