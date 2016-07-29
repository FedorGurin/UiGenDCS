#ifndef NODE_PROTOCOL_H_
#define NODE_PROTOCOL_H_

#include <QString>
#include <QDomElement>
#include <QList>

class NodeProtocol
{
public:
    NodeProtocol();
    //! тип узла
    enum Type{EMPTY,
              BLOCK_INPUT_DATA,     /*блок описывающий входные данные*/
              BLOCK_OUTPUT_DATA,    /*блок описывающий выходные данные*/
              PARAM,                /*узел описывающий параметр*/
              USE_COMMAND,          /*узел описывающий команду которую будем использовать*/
              DEF_COMMAND};         /*узел объявляющий новую команду*/

    QString name;

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
    virtual ~Node();

};

#endif /* NODE_H_ */
