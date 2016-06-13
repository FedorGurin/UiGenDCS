
#ifndef SIO_H_
#define SIO_H_

#include "genericNode.h"

//! Структура блока с параметрами(Setup/Input/Output)
class SIO: public GenericNode{
public:
    //! конструктор
    SIO(const QDomElement&, GenericNode*);

    //! Варианты программных модулей
    QList<Node* > variants;
    //! тип узла
    virtual int type() const {return Node::SIO;}
    //! адрес начала данных на УЦВС, он же идентификатор запроса
    //unsigned addr;
    //! индекс в таблице запросов
    int indexInTable;
    //! идентификатор строка
    QString nameRequest;
    //! размер всех параметров в байтах
    unsigned buffer;
    //! разрешенно только чтение структуры
    int readOnly;
    //! деструктор
    virtual ~SIO();
};
#endif /* SIO_H_ */
