
#ifndef PMODULE_H_
#define PMODULE_H_

#include <QStringList>
#include "genericNode.h"

class PModule :public GenericNode
{
public:

    PModule (const QDomElement&,GenericNode *);

    virtual void addBytes(char b){ Q_UNUSED(b);}//пустая функция = останов рекурсии

    int type()const{return Node::PM;}

    virtual ~PModule();
};

#endif /* PMODULE_H_ */
