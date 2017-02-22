#ifndef NODE_PROTOCOL_H_
#define NODE_PROTOCOL_H_

#include <QString>
#include <QDomElement>
#include <QList>
#include <stdint.h>

//! базовый класс для всех узлов
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

    NodeProtocol *left; //элемент левее, если 0, то элемента не существует
    NodeProtocol *right;//элемент правее, если 0, то элемента не существует

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
//! класс описание блока параметров
class NodeBlock :public NodeProtocol
{
public:

    NodeBlock (const QDomElement&,NodeProtocol *);

    //! уникальный идентификатор
    uint32_t uid;
    //! номер версии
    QString version;
    //! имя модуля
    QString nameModule;
    //! уникальный идентификатор модуля
    uint32_t uid_module;

    virtual int type()const{return NodeProtocol::BLOCK;}
};
class NodeInputBlock :public NodeBlock
{
public:
    NodeInputBlock (const QDomElement&,NodeProtocol *);
    virtual int type()const{return NodeProtocol::BLOCK_INPUT_DATA;}
};
class NodeOutputBlock :public NodeBlock
{
public:
    NodeOutputBlock (const QDomElement&,NodeProtocol *);
    virtual int type()const{return NodeProtocol::BLOCK_OUTPUT_DATA;}

};
//! класс описывающий один параметр
class NodeParam :public NodeBlock
{
public:
    //! тип данных
    enum TypeData{DOUBLE    = 0,
                  INT       = 1,
                  FLOAT     = 2,
                  BOOL      = 3,
                  BIT       = 4,
                  UCHAR     = 5,
                  UINT      = 6,
                  MCHAR     = 7,
                  CHAR      = 8,
                  INT16     = 9,
                  LDOUBLE   = 10};
    //! узел с параметрами
    NodeParam (const QDomElement&,NodeProtocol *);
    //! тип узла
    virtual int type()const{return NodeProtocol::PARAM;}
    //! заполнение переменной bin
    static char* binData(NodeParam* node);
    //! ед. измерения
    QString messure;
    //! значение параметра
    QString value;
    //! Тип параметра
    TypeData typeP;
    //! комментарий
    QString comment;
    //! общее кол-во элементов байтов, которое занимает этот элемент с потомками
    uint32_t bytes;
    //! адрес памяти по которому лежит структура относительно начала
    uint32_t offset;
    //! выравнивание указанным кол-вом байтов
    uint32_t alignBytes;
    //! прямой адрес в памяти
    uint32_t directAddr;
    //! значение параметра в бинарном виде(с учетом типа)
    char* bin;
};
//!
class NodeUseCommand :public NodeBlock
{
public:
    NodeUseCommand (const QDomElement&,NodeProtocol *);
    //! список параметров с аргументами
    QList<NodeParam* > args;
    //! список параметров с значениями
    QList<NodeParam* > result;

    virtual int type()const{return NodeProtocol::USE_COMMAND;}

};
//! узел с командами
class NodeDefCommand :public NodeBlock
{
public:
    NodeDefCommand (const QDomElement&,NodeProtocol *);
    //! список параметров с аргументами
    QList<NodeParam* > args;
    //! список параметров с значениями
    QList<NodeParam* > result;

    virtual int type()const{return NodeProtocol::DEF_COMMAND;}

};


#endif /* NODE_H_ */
