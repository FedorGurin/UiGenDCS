#ifndef INODETRANS_H
#define INODETRANS_H
#include <QList>
#include <QString>

class INodeTrans
{
public:
    INodeTrans();
    enum Type{
        COMMENT,/*комментарий*/
        MESSAGE,/*сообщение*/
        EQUAL,  /*равенство*/
        DELAY,  /*задержка*/
        EMPTY,  /*пусто*/
        ENTRY,  /*точка входа*/
        FUNC,   /*функция*/
        SPECIAL,/*спец. оператор*/
        VALUE   /*значение*/
    };
    //! добавить родителя
    void addParent(INodeTrans* p)
    {
        parent=p;
    }
    //! добавить потомка
    void addChild(INodeTrans* ch)
    {
        ch->parent=this;
        if(child.size()!=0)
        {
            ch->prev=child.back();
            child.back()->next=ch;
        }
        child.push_back(ch);
    }
    INodeTrans *prev;
    INodeTrans *next;
    INodeTrans *parent;
    int line;//! номер строки в скрипте
    QList<INodeTrans* > child;
    virtual int type()const{return ENTRY;}
};
class INodeMessage:public INodeTrans
{
public:
    INodeMessage():INodeTrans(){typeMessage=0;}
    QString message;
    int typeMessage;//0-информационное,1-консольное, 2 - с вопросом
    virtual int type()const{return MESSAGE;}
};
class INodeDelay:public INodeTrans
{
public:
    INodeDelay():INodeTrans(){}
    int sec;
    virtual int type()const{return DELAY;}
};
class INodeSpecial:public INodeTrans
{
public:
    INodeSpecial():INodeTrans(){}
    QString command;
    QString param;
    virtual int type()const{return SPECIAL;}
};
//! Значение
class INodeValue:public INodeTrans
{
public:
    INodeValue(QString value);
    //! анализирование строки
    void analysis(QString value);
    //! название переменной
    QString name;
    //! индекс(-1 индекса не существует)
    int index;
    //! тип
    virtual int type()const{return VALUE;}
};
//! элемент типа равенство
class INodeEqual:public INodeTrans
{
public:
    INodeEqual();

    void setValueLeft(QString value);
    void setValueRight(QString value);

    QString valueLeft_;  //строка слева  от оператора присвоения
    QString valueRigth_; //строка справа от оператора присвоения

    INodeValue* valueL;
    INodeValue* valueR;
    virtual int type()const{return EQUAL;}
};
#endif // NODETRANS_H
