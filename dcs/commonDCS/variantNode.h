/*
 * VariantNode.h
 *
 *  Created on: 07.09.2008
 *      Author: Fedor
 */

#ifndef VARIANTNODE_H_
#define VARIANTNODE_H_
#include <QList>
#include <QString>
#include <QDomElement>
#include "Node.h"

class VariantNode:public Node{
public:
    VariantNode();
    VariantNode(const QDomElement&, VariantNode*);
    VariantNode(Node* nodeData,QString& nameVariant);
    VariantNode(Node* nodeData,QString& nameVariant,QList<Node* > listNodesToSave);

    void recursCreateVariant(Node* dataNode,VariantNode* variantNode,QString& nameNodeSIO);
    void recursCreateVariant(Node* dataNode,VariantNode* variantNode,QString& nameNodeSIO,Node* nodesToSave);
    Type _type;

    Node *dataNode;//Указатель на узел с данными
    Node *variant;//укзатель на вариант программного модуля
    QList<Node* >variantState;//! ссылки на варианты состояния которые содержат данный вариант

    QString value;
    QString* valueParam;
    bool findDataNode(VariantNode* var/*структуры которую мы создаем*/,Node *data/*узел который нужно найти*/);
    void isHaveCommonParent(QList<Node* > *listNodes);
    void finUpDataNode(VariantNode* var/*структуры которую мы создаем*/,Node *data/*узел который нужно найти*/);

    QString pathToVariant()
    {
        QString tempPath="";
        if(this->child.size()!=0)
        {
            if(this->type()!=Node::PARAM)
            {
                tempPath=pathToVariant((VariantNode*)this->child[0]);
            }else tempPath="/";
        }
        return tempPath;
    }
    QString pathToVariant(VariantNode* varNode)
    {
        QString tempPath="";

        if(varNode->child.size()!=0)
        {
            if(this->type()!=Node::PARAM)
            {
                tempPath=pathToVariant((VariantNode*)(varNode->child[0]))+varNode->displayName+"/";
            }else tempPath="/";
        }
        return tempPath;
    }

    //! Переименовать данный вариант
    void rename(QString name)
    {
        displayName=name;
    }
    //! Удалить данный вариант
    void deleteVariant(void);

    //! Удалить данный вариант
    void deleteVariantNode(Node* node)
    {
        child.removeOne(node);
    }

    QString comment;

    void setPModule()       {_type=PM;}// помечаем, что данный узел содержит имя программный модуль
    void setSIO()           {_type=SIO;}
    void setParam()         {_type=PARAM;}
    void setStruct()        {_type=STRUCT;}
    void setVariantPM()     {_type=VARIANTPM;}
    void setVariantState()  {_type=VARIANTSTATE;}//вариант состояния
    //void setBit()           {_type=BIT;}

    void save(QDomDocument &domDocument,QDomElement& parent, VariantNode *parentNode);
    void setVariant();
    //! Обновить значения в варианте
    void refreshVariant();
    int type()const{return _type;}
    virtual ~VariantNode();
};

#endif /* VARIANTNODE_H_ */
