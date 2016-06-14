/*
 * Structure.cpp
 *
 *  Created on: 27.08.2008
 *      Author: Fedor
 */

#include "Structure.h"
#include "Parameter.h"

#include "GroupLabel.h"



Structure::Structure(const QDomElement& element,GenericNode *parent):GenericNode()
{
    displayName=      element.attribute("displayName","");
    comment=         (element.attribute("comment",""));
    isDisplay=      ((element.attribute("isDisplay","1")).toInt());
    howElements=     (element.attribute("howElements","1")).toInt();
    isFieldBits=     (element.attribute("isFieldBits","0")).toInt();
    numStartBit=     (element.attribute("numStartBit","0")).toInt();
    numEndBit=       (element.attribute("numEndBit","1")).toInt();
    isDisplay=      ((element.attribute("isDisplay","1")).toInt());
    mkio=            (element.attribute("mkio","1")).toInt();
    sizeFieldBits=   (element.attribute("sizeField","32")).toInt();
    startIndex=      (element.attribute("startIndex","0")).toInt();

    idName=element.attribute("idName","");
    if(idName=="")
        idName=displayName;


    if(isDisplay==true)
        parent->addVisionChild(this);

    //! добавление элемента в общее дерево
    addParent(parent);
    parent->addChild(this);

    //! подсчет смещения относительно начала структуры
    if(leftNode()!=0)
    {
        offset=leftNode()->offset+leftNode()->bytes;
    }else
        offset=parent->offset;

    if(isFieldBits==1)
        bytes=4;
    else
        bytes=0;

    parent->addBytes(bytes);
    qDebug("bytesToParents=%d\n",bytes);
}
Structure::Structure(const Structure* st, GenericNode *glParent /*глобальный предок*/):GenericNode()
{
    const Node *node=0;

    //! добавляем текущий элемент в дерево
    if(glParent!=0)
    {
        qDebug("parent detected\n");
        glParent->addChild(this);
        addParent(glParent);
    }

    displayName=    st->displayName;
    comment=        st->comment;
    shortName=      st->shortName;
    idName=         st->idName;
    isFieldBits=    st->isFieldBits;
    numStartBit=    st->numStartBit;
    numEndBit=      st->numEndBit;
    mkio=           st->mkio;
    sizeFieldBits=  st->sizeFieldBits;
    startIndex=     st->startIndex;
    howElements     = 1;

    //! подсчет смещения относительно начала структуры
    if(leftNode()!=0)
    {
        qDebug("in leftNode=%d, bytes=%d\n, parent=%d\n",leftNode()->offset,leftNode()->bytes,glParent->bytes);
        offset=leftNode()->offset+leftNode()->bytes;
        qDebug("in leftNode=%d, bytes=%d\n, parent=%d, offset_cur=%d\n",leftNode()->offset,
               leftNode()->bytes,
               glParent->bytes,
               offset);

    }else if(parent == 0)
        offset=0;
    else
        offset=parent->offset;
    //////////////////////////////////////////////////////////////

    if(isFieldBits==1)
    {
        bytes=4;
        glParent->addBytes(bytes);
    }
    else
        bytes=0;

    for(int i=0;i<st->child.size();i++)
    {
        node=st->child[i];
        switch(node->type())
        {
        case STRUCT:
            {
                //! нет увеличения текущей структуры при создании новой структуры
                //! создание новой структуры
                const Structure* nodeS=static_cast<const Structure*>(node);
                Structure *newStruct=new Structure(nodeS,this);

                if(st->isDisplay==true)
                    addVisionChild(newStruct);
                break;
            }
        case PARAM:
            {
                const Parameter* nodeP=static_cast<const Parameter*>(node);
                Parameter *param=new Parameter(nodeP,this);

                if(st->isDisplay==true)
                    addVisionChild(param);
                break;
            }
        case GROUP:
            {
                const GroupLabel* nodeG=static_cast<const GroupLabel*>(node);
                GroupLabel *newGroupLabel=new GroupLabel(nodeG,this);

                if(st->isDisplay==true)
                    addVisionChild(newGroupLabel);

                break;
            }
        };
    }
}
void Structure::addMassiveStruct(void)
{
    if(howElements>1)
    {
        Structure *newStruct=0;
        for(int i=1;i<howElements;i++)
        {
            newStruct=new Structure(this,(GenericNode*)this->parent);

            newStruct->displayName+="["+QString::number(i+1+startIndex)+"]";
            newStruct->idName+="["+QString::number(i+1+startIndex)+"]";

            if(isDisplay==true)
                ((GenericNode*)parent)->addVisionChild(newStruct);

        }
        displayName+="["+QString::number(1+startIndex)+"]";
        idName+="["+QString::number(1+startIndex)+"]";
    }
}
Structure::~Structure() {
        // TODO Auto-generated destructor stub
}
