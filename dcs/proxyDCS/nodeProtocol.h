#ifndef NODE_PROTOCOL_H_
#define NODE_PROTOCOL_H_

#include <QString>
#include <QDomElement>
#include <QList>
#include <stdint.h>
class NodeProtocol
{
public:
    NodeProtocol();
    //! тип узла
    enum Type{EMPTY,
              BLOCK,
              BLOCK_INPUT_DATA,     /*блок описывающий входные данные*/
              BLOCK_OUTPUT_DATA,    /*блок описывающий выходные данные*/
              PARAM,                /*узел описывающий параметр*/
              USE_COMMAND,          /*узел описывающий команду которую будем использовать*/
              DEF_COMMAND};         /*узел объявляющий новую команду*/

    QString name;
    QString pathName;


    //! добавить родителя
    void addParent(NodeProtocol* p)
    {
        parent=p;
        pathName=p->pathName;
    }
    //! добавить потомка
    void addChild(NodeProtocol* ch)
    {
        ch->parent=this;
        if(child.isEmpty()==false)
        {
            ch->left=child.last();
            ch->left->right=ch;
        }

        child.push_back(ch);
        ch->pathName=this->pathName+"/"+this->name;
    }

    NodeProtocol *parent;//родителький элемент

    NodeProtocol *left; //элемент левее
    NodeProtocol *right;//элемент правее

    NodeProtocol* leftNode()// вернуть узел слева
    {
        return left;
    }
    NodeProtocol* rightNode()//вернуть узел справа
    {
        return right;
    }

    QList<NodeProtocol* > child;// дочерние элементы


    virtual int type()const{return EMPTY;}
    virtual ~NodeProtocol();

};
class NodeBlock :public NodeProtocol
{
public:

    NodeBlock (const QDomElement&,NodeProtocol *);

    //! номер версии
    QString version;
    //! уникальный идентификатор
    uint32_t uid;
    //! имя модуля
    QString nameModule;

    int type()const{return NodeProtocol::BLOCK;}
};
class NodeInputBlock :public NodeBlock
{
public:
    NodeInputBlock (const QDomElement&,NodeProtocol *);
    int type()const{return NodeProtocol::BLOCK_INPUT_DATA;}
};
class NodeOutputBlock :public NodeBlock
{
public:
    NodeOutputBlock (const QDomElement&,NodeProtocol *);
    int type()const{return NodeProtocol::BLOCK_OUTPUT_DATA;}

};
class NodeParam :public NodeBlock
{
public:
    NodeParam (const QDomElement&,NodeProtocol *);
    int type()const{return NodeProtocol::PARAM;}

};
//!
class NodeUseCommand :public NodeBlock
{
public:
    NodeUseCommand (const QDomElement&,NodeProtocol *);
    QList<NodeParam* > args;
    QList<NodeParam* > result;

    int type()const{return NodeProtocol::USE_COMMAND;}

};
//! узел с командами
class NodeDefCommand :public NodeBlock
{
public:
    NodeDefCommand (const QDomElement&,NodeProtocol *);
    QList<NodeParam* > args;
    QList<NodeParam* > result;

    int type()const{return NodeProtocol::DEF_COMMAND;}

};


#endif /* NODE_H_ */
