#ifndef GROUPLABEL_H
#define GROUPLABEL_H
#include "genericNode.h"

//! Класс групирует модели БРЭО
class GroupLabel:public GenericNode
{
public:
    GroupLabel(const QDomElement&, GenericNode*);
    GroupLabel(const GroupLabel*,Node *glParent);

    virtual int type() const {return Node::GROUP;}
};

#endif // GROUPLABEL_H
