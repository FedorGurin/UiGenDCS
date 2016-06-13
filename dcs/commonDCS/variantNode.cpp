/*
 * VariantNode.cpp
 *
 *  Created on: 07.09.2008
 *      Author: Fedor
 */

#include "VariantNode.h"
#include "Parameter.h"
#include "VariantState.h"


VariantNode::VariantNode():Node() {
	// TODO Auto-generated constructor stub

    parent=0;
    value="?";
    typeTree=VARIANT;
    dataNode=0;
    variant=0;
    variantState.clear();

    _type=EMPTY;

    valueParam=0;
}


VariantNode::VariantNode(Node* nodeData,QString& nameVariant)
{
    parent=0;
    value="?";
    typeTree=VARIANT;
    dataNode=nodeData;
    variant=0;    
    variantState.clear();

    _type=EMPTY;

    //! Найдем родителя с узлом pmodule
    displayName=nameVariant;
    setVariantPM();
    Node* tempNode=nodeData;
    do
    {
        tempNode=(Node*)tempNode->parent;

    }while(tempNode->type()!=Node::PM);

    VariantNode* variantPM=new VariantNode();
    variantPM->displayName=tempNode->displayName;
    variantPM->idName=tempNode->idName;
    variantPM->setPModule();
    variantPM->addParent(this);
    addChild(variantPM);    
    recursCreateVariant(tempNode,variantPM,nodeData->displayName);
}
VariantNode::VariantNode(Node* nodeData,QString& nameVariant,QList<Node* > listNodesToSave)
{
    parent=0;
    value="?";
    typeTree=VARIANT;
    dataNode=nodeData;
    variant=0;
    variantState.clear();

    _type=EMPTY;

    qDebug("CreateVariantNode\n");
    //! Найдем родителя с узлом pmodule
    displayName=nameVariant;
    idName=nameVariant;
    setVariantPM();
    Node* tempNode=nodeData;
    do
    {
        tempNode=(Node*)tempNode->parent;

    }while(tempNode->type()!=Node::PM);
    ((GenericNode*)tempNode)->setZeroVariantNode();;

    /*VariantNode* variantPM=new VariantNode();
    variantPM->displayName=tempNode->displayName;
    variantPM->setPModule();
    variantPM->addParent(this);
    addChild(variantPM);
    ((GenericNode*)tempNode)->variantNode=variantPM;

    //VariantNode* tempVariantRoot=new VariantNode();*/

    for(int i=0;i<listNodesToSave.size();i++)
    {
        VariantNode* tempVariantRoot=new VariantNode();
        qDebug("findDataNode() iter %d\n ",i);
        findDataNode(tempVariantRoot,listNodesToSave[i]);
        qDebug("finUpDataNode()\n ");
        finUpDataNode(tempVariantRoot,listNodesToSave[i]);
    }
    GenericNode* tempGenericNode=((GenericNode*)tempNode);
    tempGenericNode->variantNode->addParent(this);
    addChild(tempGenericNode->variantNode);

    //isHaveCommonParent(&listNodesToSave);
    //qDebug("Size=%d\n",listNodesToSave.size());

}
void VariantNode::deleteVariant(void)
{
    qDebug("run func delete Varinat");
    if(type()==VARIANTPM)
    {
        ((VariantNode*)parent)->deleteVariantNode(this);

        for(int i=0;i<variantState.size();i++)
        {
            (((VariantState*)variantState[i])->variant)=0;
        }
        delete this;        
    }
    qDebug("exit func delete Variant\n");

}
void VariantNode::isHaveCommonParent(QList<Node* > *listNodes)
{
    //! список узлов который нужно удалить
    QList<Node* > nodeToDelete;
    for(int i=0;i<listNodes->size();i++)
    {
        for(int j=i+1;j<listNodes->size();j++)
        {
            if(((*listNodes)[i])->parent==((*listNodes)[j])->parent)
            {
                nodeToDelete.push_back(((*listNodes)[j]));
            }
        }
    }
    for(int i=0;i<nodeToDelete.size();i++)
    {
        listNodes->removeOne(nodeToDelete[i]);
    }
}

//! остановкой данной рекурсии является нахождения элемента PM
void VariantNode::finUpDataNode(VariantNode* varNode/*структуры которую мы создаем*/,
                   Node *dataNode/*узел который нужно найти*/)
{
    GenericNode *parentNode=((GenericNode*)(dataNode->parent));
    if(parentNode->type()==Node::STRUCT)
    {
        if(parentNode->variantNode==0)
        {
            VariantNode* tempNode=new VariantNode;
            tempNode->displayName=parentNode->displayName;
            tempNode->idName=parentNode->idName;
            tempNode->setStruct();
            parentNode->variantNode=tempNode;

            varNode->addParent(tempNode);
            tempNode->addChild(varNode);
        }else
        {
            varNode->addParent(parentNode->variantNode);
            parentNode->variantNode->addChild(varNode);
            return;
        }
    }else if(parentNode->type()==Node::SIO)
    {
        if(parentNode->variantNode==0)
        {
            VariantNode* tempNode=new VariantNode;
            tempNode->displayName=parentNode->displayName;
            tempNode->idName=parentNode->idName;
            tempNode->setSIO();
            parentNode->variantNode=tempNode;
            varNode->addParent(tempNode);
            tempNode->addChild(varNode);
        }else
        {
            varNode->addParent(parentNode->variantNode);
            parentNode->variantNode->addChild(varNode);
            return;
        }
    }
    if(parentNode->type()==Node::PM)
    {
        if(parentNode->variantNode==0)
        {
            VariantNode* tempNode=new VariantNode;
            tempNode->displayName=parentNode->displayName;
            tempNode->idName=parentNode->idName;
            tempNode->setPModule();
            parentNode->variantNode=tempNode;
            varNode->addParent(tempNode);
            tempNode->addChild(varNode);
        }else
        {
            varNode->addParent(parentNode->variantNode);
            parentNode->variantNode->addChild(varNode);
        }
    }else
    {


            if(varNode->parent!=0) finUpDataNode(((VariantNode*)varNode->parent),dataNode->parent);
            else finUpDataNode(varNode,dataNode->parent);

    }
}
bool VariantNode::findDataNode(VariantNode* tempNode/*структуры которую мы создаем*/,
                               Node *nodesToSave/*узел который нужно найти*/)
{
    //VariantNode* tempNode=0;
    GenericNode *tempNodeData=(GenericNode*)nodesToSave;

    if(nodesToSave->type()==Node::PARAM)
    {
        Parameter* param=(Parameter*)nodesToSave;

        tempNode->displayName=nodesToSave->displayName;
        tempNode->idName=nodesToSave->idName;
        tempNode->setParam();

        tempNode->value=param->value;
        tempNode->valueParam=&param->value;
        tempNode->dataNode=param;

        tempNodeData->variantNode=tempNode;

    }else if(nodesToSave->type()==Node::STRUCT)
    {
        tempNode->displayName=nodesToSave->displayName;
        tempNode->idName=nodesToSave->idName;
        tempNode->setStruct();
        tempNodeData->variantNode=tempNode;
    }else if(nodesToSave->type()==Node::SIO)
    {
        tempNode->displayName=nodesToSave->displayName;
        tempNode->idName=nodesToSave->idName;
        tempNode->setSIO();

        tempNodeData->variantNode=tempNode;
    }
    for(int i=0;i<nodesToSave->child.size();i++)
    {
       // if(nodesToSave->type()!=Node::GROUP)
       // {
            VariantNode *variantNode=new VariantNode();
            findDataNode(variantNode,nodesToSave->child[i]);
            if(variantNode!=0)
            {
                variantNode->addParent(tempNode);
                tempNode->addChild(variantNode);
            }
        //}else
        //{
            //findDataNode(this,nodesToSave->child[i]);
            //qDebug("Search group\n");
            /*variantNode->addParent(tempNode);
            tempNode->addChild(variantNode);*/
        //}


    }
    return true;
}
//! сохранение в варианте выбранных значений
void VariantNode::recursCreateVariant(Node* dataNode,VariantNode* variantNode,QString& nameNodeSIO,Node* nodesToSave)
{
    for(int i=0;i<dataNode->child.size();i++)
    {
        if(dataNode->child[i]->type()==Node::SIO)
        {
            if((dataNode->child[i])->idName==nameNodeSIO)
            {
                VariantNode* tempNode=new VariantNode;
                tempNode->displayName=(dataNode->child[i])->displayName;
                tempNode->idName=(dataNode->child[i])->idName;
                tempNode->addParent(variantNode);
                variantNode->addChild(tempNode);
                tempNode->setSIO();
                recursCreateVariant(dataNode->child[i],tempNode,nameNodeSIO,nodesToSave);
            }
        }
        /*else if(dataNode->child[i]->type()==Node::BIT)
        {
            printf("Size list=%d\n",listNodesToSave.size());
            Node *tempNodeCompare=dataNode->child[i];
            if(listNodesToSave.contains(tempNodeCompare)==true)
            {
                printf("Equal\n");

                Bit* bit=(Bit*)dataNode->child[i];
                VariantNode* tempNode=new VariantNode;
                tempNode->displayName=(dataNode->child[i])->displayName;
                tempNode->addParent(variantNode);
                variantNode->addChild(tempNode);
                tempNode->setBit();
                tempNode->value=bit->value;
                tempNode->valueParam=&bit->value;
                tempNode->dataNode=bit;
            }
        }
        else if(dataNode->child[i]->type()==Node::STRUCT)
        {
            VariantNode* tempNode=new VariantNode;
            tempNode->displayName=(dataNode->child[i])->displayName;
            tempNode->addParent(variantNode);
            variantNode->addChild(tempNode);
            tempNode->setStruct();
            recursCreateVariant(dataNode->child[i],tempNode,nameNodeSIO,listNodesToSave);
        }*/
        else if(dataNode->child[i]->type()==Node::PARAM)
        {
            Node *tempNodeCompare=dataNode->child[i];
            //if(listNodesToSave.contains(tempNodeCompare)==true)
            if(tempNodeCompare==nodesToSave)
            {
                qDebug("Equal\n");

                Parameter* param=(Parameter*)dataNode->child[i];

                VariantNode* tempNode=new VariantNode;
                tempNode->displayName=(dataNode->child[i])->displayName;
                tempNode->idName=(dataNode->child[i])->idName;
                tempNode->addParent(variantNode);

                variantNode->addChild(tempNode);
                tempNode->setParam();
                tempNode->value=param->value;
                tempNode->valueParam=&param->value;
                tempNode->dataNode=param;
            }
        }else recursCreateVariant(dataNode->child[i],variantNode,nameNodeSIO,nodesToSave);
    }
}
void VariantNode::recursCreateVariant(Node* dataNode,VariantNode* variantNode,QString& nameNodeSIO)
{

    for(int i=0;i<dataNode->child.size();i++)
    {

        if(dataNode->child[i]->type()==Node::SIO)
        {
            if((dataNode->child[i])->idName==nameNodeSIO)
            {
                VariantNode* tempNode=new VariantNode;
                tempNode->displayName=(dataNode->child[i])->displayName;
                tempNode->idName=(dataNode->child[i])->idName;
                tempNode->addParent(variantNode);
                variantNode->addChild(tempNode);
                tempNode->setSIO();
                recursCreateVariant(dataNode->child[i],tempNode,nameNodeSIO);
            }
        }
//        else if(dataNode->child[i]->type()==Node::BIT)
//        {
//            Bit* bit=(Bit*)dataNode->child[i];
//            VariantNode* tempNode=new VariantNode;

//            tempNode->displayName=(dataNode->child[i])->displayName;
//            tempNode->idName=(dataNode->child[i])->idName;

//            tempNode->addParent(variantNode);
//            variantNode->addChild(tempNode);
//            tempNode->setBit();
//            tempNode->value=bit->value;
//            tempNode->valueParam=&bit->value;
//            tempNode->dataNode=bit;
//        }
        else if(dataNode->child[i]->type()==Node::STRUCT)
        {
            VariantNode* tempNode=new VariantNode;
            tempNode->displayName=(dataNode->child[i])->displayName;
            tempNode->idName=(dataNode->child[i])->idName;
            tempNode->addParent(variantNode);
            variantNode->addChild(tempNode);
            tempNode->setStruct();
            recursCreateVariant(dataNode->child[i],tempNode,nameNodeSIO);
        }
        else if(dataNode->child[i]->type()==Node::PARAM)
        {
            Parameter* param=(Parameter*)dataNode->child[i];

            VariantNode* tempNode=new VariantNode;
            tempNode->displayName=(dataNode->child[i])->displayName;
            tempNode->idName=(dataNode->child[i])->idName;
            tempNode->addParent(variantNode);
            variantNode->addChild(tempNode);
            tempNode->setParam();
            tempNode->value=param->value;
            tempNode->valueParam=&param->value;
            tempNode->dataNode=param;
        }else recursCreateVariant(dataNode->child[i],variantNode,nameNodeSIO);
    }
}
VariantNode::VariantNode(const QDomElement& element, VariantNode* parent)
{
    typeTree=VARIANT;
    valueParam=0;
    dataNode=0;

    displayName=element.attribute("displayName","?");
    idName=element.attribute("idName","?");

    if(element.tagName()=="pmodule")
    {
        setPModule();
    }
    else if(element.tagName()=="param")
    {
        value=element.attribute("value","?");
        setParam();
    }
    else if(element.tagName()=="struct")
    {
        setStruct();
    }
    else if(element.tagName()=="sio")
    {
        setSIO();
    }
//    else if(element.tagName()=="bit")
//    {
//        value=element.attribute("value","?");
//        setBit();
//    }
    else if(element.tagName()=="variantPM")
    {
        comment=element.attribute("comment","No comment");
        setVariantPM();
    }else _type=EMPTY;

    addParent(parent);
    parent->addChild(this);
}
void VariantNode::save(QDomDocument &domDocument,QDomElement& parent, VariantNode *parentNode)
{
    for(int i=0;i<parentNode->child.size();i++)
    {
        Node *node=parentNode->child[i];
        VariantNode *variantNode=static_cast<VariantNode* >(node);
        switch(node->type())
        {
            case Node::PM:
            {                
                QDomElement ele=domDocument.createElement("pmodule");
                parent.appendChild(ele);
                ele.setAttribute("displayName",variantNode->displayName);
                ele.setAttribute("idName",variantNode->idName);
                save(domDocument,ele,variantNode);
                break;
            }
            case Node::SIO:
            {
                QDomElement ele=domDocument.createElement("sio");
                parent.appendChild(ele);

                ele.setAttribute("displayName",variantNode->displayName);
                ele.setAttribute("idName",variantNode->idName);
                save(domDocument,ele,variantNode);
                break;
            }
            case Node::PARAM:
            {
                QDomElement ele=domDocument.createElement("param");
                parent.appendChild(ele);

                ele.setAttribute("displayName",variantNode->displayName);
                ele.setAttribute("idName",variantNode->idName);
                ele.setAttribute("value",variantNode->value);
                break;
            }
            case Node::STRUCT:
            {
                QDomElement ele=domDocument.createElement("struct");
                parent.appendChild(ele);

                ele.setAttribute("displayName",variantNode->displayName);
                ele.setAttribute("idName",variantNode->idName);
                save(domDocument,ele,variantNode);
                break;
            }
//            case Node::BIT:
//            {
//                QDomElement ele=domDocument.createElement("bit");
//                parent.appendChild(ele);

//                ele.setAttribute("displayName",variantNode->displayName);
//                ele.setAttribute("idName",variantNode->idName);
//                ele.setAttribute("value",variantNode->value);
//                break;

//            }
        default:
            {
                save(domDocument,parent,variantNode);
            }
        };
    }
}
void VariantNode::setVariant()
{
    if(type()==Node::PARAM)
    {        
        if(dataNode!=0)
        {
            Parameter* ptr=static_cast<Parameter* >(dataNode);
            if(ptr!=0)
            {
                ptr->valueVariant=&value;
                ptr->refreshValues();//! Обновить значение узла данных
            }
        }
    }/*else if(type()==Node::BIT)
    {*/
//        Bit* ptr=static_cast<Bit* >(dataNode);

//        ptr->valueVariant=&value;

//        ptr->refreshValues();//! Обновить значение узла данных
//    }
    else
    {
        for(int i=0;i<child.size();i++) ((VariantNode*)child[i])->setVariant() ;
    }
}
void VariantNode::refreshVariant()
{
    if(type()==Node::PARAM)
    {
        Parameter* ptr=static_cast<Parameter* >(dataNode);

        value=ptr->value;

    }/*else if(type()==Node::BIT)
    {*/
//        Bit* ptr=static_cast<Bit* >(dataNode);

//        value=ptr->value;
//    }
    else   for(int i=0;i<child.size();i++) ((VariantNode*)child[i])->refreshVariant() ;
}
VariantNode::~VariantNode() {
	// TODO Auto-generated destructor stub
}
