#ifndef GENERICNODE_H_
#define GENERICNODE_H_

#include "node.h"
#include "variantNode.h"

//! базовый узел для дерева описывающее структуру данных
class GenericNode:public Node
{
public:
    GenericNode();
    //! комментарий
    QString comment;
    //! короткое имя узла
    QString shortName;
    //! добавить кол-во байт
    virtual void addBytes(char b);
    //! Признак отображать пользователю данный узел или нет(true - )
    bool isDisplay;

    //! потомки которые видимы пользователю
    QList<Node* > childVision;
    //! добавить потомка в список видимых элементов
    void addVisionChild(Node* node)
    {
        childVision.push_back(node);
        node->pathName=this->pathName+"/"+this->displayName;
    }
    //! кол-во видимых элементов
    int sizeVisionChild()
    {
        int count=0;
        for(int i=0;i<child.size();i++)
        {
            if(((GenericNode*)child[i])->isDisplay==true) count++;
        }
        return count;
    }

    virtual ~GenericNode();
};

#endif /* GENERICNODE_H_ */
