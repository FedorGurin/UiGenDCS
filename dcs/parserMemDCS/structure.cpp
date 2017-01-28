
#include "structure.h"
#include "parameter.h"
#include "../globalFunc/math_func.h"

Structure::Structure(const QDomElement& element,Node *parent):Node()
{
    displayName     = (element.attribute("displayName",""));
    comment         = (element.attribute("comment",""));   
    howElements     = (element.attribute("howElements","1")).toInt();
    isFieldBits     = (element.attribute("isFieldBits","0")).toInt();
    numStartBit     = (element.attribute("numStartBit","0")).toInt();
    numEndBit       = (element.attribute("numEndBit","1")).toInt();   
    mkio            = (element.attribute("mkio","1")).toInt();
    sizeFieldBits   = (element.attribute("sizeField","32")).toInt();
    startIndex      = (element.attribute("startIndex","0")).toInt();

    idName = element.attribute("idName","");
    if(idName=="")
        idName=displayName;

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
}
Structure::Structure(const Structure* st, Node *glParent /*глобальный предок*/):Node()
{
    const Node *node=0;

    //! добавляем текущий элемент в дерево
    if(glParent!=0)
    {
        //qDebug("parent detected\n");
        glParent->addChild(this);
        addParent(glParent);
    }

    displayName=    st->displayName;
    comment=        st->comment;
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
        //qDebug("in leftNode=%d, bytes=%d\n, parent=%d\n",leftNode()->offset,leftNode()->bytes,glParent->bytes);
        offset=leftNode()->offset+leftNode()->bytes;
//        qDebug("in leftNode=%d, bytes=%d\n, parent=%d, offset_cur=%d\n",leftNode()->offset,
//               leftNode()->bytes,
//               glParent->bytes,
//               offset);

    }else if(parent==0)
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
                addChild(newStruct);
                break;
            }
        case PARAM:
            {
                const Parameter* nodeP=static_cast<const Parameter*>(node);
                Parameter *newParam=new Parameter(nodeP,this);

                addChild(newParam);
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
            //listForCompleter<<newStruct->displayName;
            parent->addChild(newStruct);

            //if(isDisplay==true)
            //    ((GenericNode*)parent)->addVisionChild(newStruct);

        }
        displayName+="["+QString::number(1+startIndex)+"]";
        idName+="["+QString::number(1+startIndex)+"]";
    }
}
Structure::~Structure() {
        // TODO Auto-generated destructor stub
}
