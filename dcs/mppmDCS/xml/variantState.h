/*
 * VariantState.h
 *
 *  Created on: 16.09.2008
 *      Author: Fedor
 */

#ifndef VARIANTSTATE_H_
#define VARIANTSTATE_H_

#include <QDomElement>
#include "Node.h"
#include "VariantNode.h"
//! Класс описывающий варианты сосотяния
class VariantState :public Node
{
public:
    VariantState();
    VariantState(const QDomElement&, VariantState*);
    VariantState(const QString&);    

    QString comment;
    //! Указатель на узел варианта
    VariantNode *variant;
    //! Сохранить текущие данные в XML файл
    void save(QDomDocument &domDocument,QDomElement& parent, VariantState *parentNode);
    //! Добавить новый вариант в текущий вариант состояния
    void addVariant(VariantState* node)
    {
        this->addChild(node);
    }
    //! добавить хвостик от variantPM для того, что бы различать одинаковые имена
    void addTailVariantPM(VariantNode *);
    //! Активировать все варианты находящиеся в этом варианте состояний
    void setVariant(void);

    //! удаление варианта состояния
    void deleteVariantState();

    void setVariantState()  {_type=VARIANTSTATE;}//вариант состояния
    void setVariantPM()     {_type=VARIANTPM;}
    void setPModule()       {_type=PM;}// помечаем, что данный узел содержит имя программный модуль
    void setSIO()           {_type=SIO;}

    virtual ~VariantState();
    int type()const{return _type;}
private:
    Type _type;
};

#endif /* VARIANTSTATE_H_ */
