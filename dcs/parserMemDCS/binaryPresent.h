#ifndef BINARYPRESENT_H
#define BINARYPRESENT_H

#include <QObject>
#include "Node.h"
class TransferDataUDP;

class BinaryPresent:public QObject
{
    Q_OBJECT;
public:
    BinaryPresent(QObject *parent=0);
    void setData(Node* node);              //формирование запроса на запись по всем параметрам ПМ
    void getData(Node* node);              //формирование запроса на чтение по всем параметрам ПМ

    //рекурсивные функции
    void recursSetData(Node* node,QDataStream &in, int &bitField);
    void recursGetData(Node* node,QDataStream &out,int &tempBit);

    //! прочитать с выравниванием в nums байт
    void getAllign(QDataStream &out,int nums);
};

#endif // BINARYPRESENT_H
