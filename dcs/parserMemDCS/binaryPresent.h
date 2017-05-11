#ifndef BINARYPRESENT_H
#define BINARYPRESENT_H

#include <QObject>
#include "Node.h"
class TransferDataUDP;

class BinaryPresent:public QObject
{
    Q_OBJECT;
public:
    void setData(Node* fromNode, QByteArray *toMem); //формирование запроса на запись по всем параметрам ПМ
    void getData(Node* toNode, QByteArray *fromMem);   //формирование запроса на чтение по всем параметрам ПМ

    //рекурсивные функции
    void recursSetData(Node* node,QDataStream &in, int &bitField);
    void recursGetData(Node* node,QDataStream &out,int &tempBit);

    //! прочитать с выравниванием в nums байт
    void getAllign(QDataStream &out,int nums);

    //! объект на представление
    static BinaryPresent* obj()
    {
        if(binary == 0)
            binary = new BinaryPresent(0);
        return binary;
    }

private:
    BinaryPresent(QObject *parent);

    static BinaryPresent *binary;
};

#endif // BINARYPRESENT_H
