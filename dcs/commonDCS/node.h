#ifndef NODE_H_
#define NODE_H_

#include <QString>
#include <QDomElement>
#include <QList>
#include <QVector>
#include <QModelIndex>
#include <QObject>

class Node
{
public:
    Node();
    //! тип узла
    enum Type{EMPTY,
              STRUCT,
              PARAM,
              PM,
              SIO,
              VARIANTSTATE,
              VARIANTPM,
              GROUP,
              TEST};

    enum TypeTree{//тип дерева
        UNCERTAIN,//не определено
        VARIANT,  //варианты
        DATA};    //данные

    //! текущий тип дерева
    TypeTree typeTree;
    QString displayName;//имя которое будет отображаться пользователю
    //! имя в протоколе информационного обмена
    QString picName;
    //! имя идентификатор
    QString idName;
    //! внутреннее имя
    QString internalName;
    //! имя пути к данному узлу
    QString pathName;
    //! добавить родителя
    void addParent(Node* p)
    {
        parent=p;
        pathName=p->pathName;
    }
    //! добавить потомка
    void addChild(Node* ch)
    {
        ch->parent=this;
        if(child.isEmpty()==false)
        {
            ch->left=child.last();
            ch->left->right=ch;
        }

        child.push_back(ch);
        ch->pathName=this->pathName+"/"+this->displayName;
    }
    void addModelIndex(QModelIndex i, int column)
    {
        if(column>=index.size())
        {
            index.resize(column+1);
        }
        index[column]=i;
    }
    QModelIndex modelIndexByCol(int column)
    {
        return index[column];
    }

    Node *parent;//родителький элемент

    Node *left; //элемент левее
    Node *right;//элемент правее

    Node* leftNode()// вернуть узел слева
    {
        return left;
    }
    Node* rightNode()//вернуть узел справа
    {
        return right;
    }

    QList<Node* > child;// дочерние элементы
    QVector<QModelIndex> index;

    virtual int type()const{return EMPTY;}
    virtual ~Node();
    //////////Нужно перенести в GenericNode
    //! адрес памяти по которому лежит структура относительно начала
    unsigned offset;
    //! выравнивание указанным кол-вом байтов
    unsigned alignBytes;
     //! общее кол-во элементов байтов, которое занимает этот элемент с потомками
    unsigned bytes;
    //! прямой адрес в памяти
    unsigned directAddr;

};

#endif /* NODE_H_ */
