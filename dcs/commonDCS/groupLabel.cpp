#include "groupLabel.h"
#include "structure.h"
#include "parameter.h"

GroupLabel::GroupLabel(const QDomElement& element, GenericNode *parent):GenericNode()
{
    displayName=    element.attribute("displayName");
    comment=        element.attribute("comment");
    isDisplay=      ((element.attribute("isDisplay")).toInt());

    parent->addChild(this);
    addParent(parent);

    //! подсчет смещения относительно начала структуры
    if(leftNode()!=0)
    {
        offset=leftNode()->offset+leftNode()->bytes;
    }else
        offset=parent->offset;

    if(isDisplay==true)
        parent->addVisionChild(this);

    parent->addBytes(bytes);
}
GroupLabel::GroupLabel(const GroupLabel* st,Node *glParent /*глобальный родитель*/):GenericNode()
{
    const Node *node=0;

    if(glParent!=0)
    {
        glParent->addChild(this);
        addParent(glParent);
    }

    displayName=    st->displayName;
    comment=        st->comment;
    shortName=      st->shortName;

    //! подсчет смещения относительно начала структуры
    if(leftNode()!=0)
    {
        offset=leftNode()->offset+leftNode()->bytes;

    }else if(parent==0)
        offset=0;
    else
        offset=parent->offset;
    //////////////////////////////////////////////////////////////
    for(int i=0;i<st->child.size();i++)
    {
        node=st->child[i];
        switch(node->type())
        {
        case STRUCT:
            {
                const Structure* nodeS=static_cast<const Structure*>(node);
                Structure *newStruct=new Structure(nodeS,this);

                if(st->isDisplay==true)
                    addVisionChild(newStruct);
                //addChild(newStruct);

//                if(newStruct->leftNode()!=0)
//                {
//                    newStruct->offset=newStruct->leftNode()->offset+newStruct->leftNode()->bytes;
//                }else
//                    newStruct->offset=newStruct->parent->offset;

                break;
            }
        case PARAM:
            {
                const Parameter* nodeP=static_cast<const Parameter*>(node);
                Parameter *param=new Parameter(nodeP,this);
                if(st->isDisplay==true)
                    addVisionChild(param);
                //addChild(param);

//                if(param->leftNode()!=0)
//                {
//                    param->offset=param->leftNode()->offset+param->leftNode()->bytes;
//                }else
//                    param->offset=param->parent->offset;

                //param->offset=param->leftNode()->offset+param->leftNode()->bytes;
                break;
            }
        case GROUP:
            {
                const GroupLabel* nodeG=static_cast<const GroupLabel*>(node);
                GroupLabel *newGroupLabel=new GroupLabel(nodeG,this);

                if(st->isDisplay==true)
                    addVisionChild(newGroupLabel);

//                addChild(newGroupLabel);

//                if(newGroupLabel->leftNode()!=0)
//                {
//                    newGroupLabel->offset=newGroupLabel->leftNode()->offset+newGroupLabel->leftNode()->bytes;
//                }else
//                    newGroupLabel->offset=newGroupLabel->parent->offset;

                //newGroupLabel->offset=newGroupLabel->leftNode()->offset+newGroupLabel->leftNode()->bytes;
                break;
            }
        };
    }
}
