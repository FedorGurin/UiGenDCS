
#ifndef STRUCTURE_H_
#define STRUCTURE_H_
#include "genericNode.h"

class Structure: public GenericNode {
public:
//    Structure(const QString& name="",
//              const QString& idName_="",
//              const QString& comm="",
//              const QString& disp=QString::number(1),
//              const QString& howEle="1");

    Structure(const QDomElement&,GenericNode *);
    Structure(const Structure*, GenericNode *glParent=0 /*глобальный родитель*/);

    //! Битовая структура
    bool isFieldBits;

    //! номер начального бита
    unsigned int numStartBit;

    //! номер конечного бита
    unsigned int numEndBit;

    //! признак того, что нумерация как в МКИО
    bool mkio;

    //! размерность битового поля в байтах
    int sizeFieldBits;

    //! кол-во элементов
    int howElements;

    //! начальный индекс
    int startIndex;

    //! добавить массив структур
    void addMassiveStruct();

    //! добавить параметр
    void addParameter();

    //! задание имени отображение
    void setDisplayName(QString );

    //!
    void setComment(QString);

    //!
    virtual int type()const{return Node::STRUCT;}

    //!
    virtual ~Structure();
};

#endif /* STRUCTURE_H_ */
