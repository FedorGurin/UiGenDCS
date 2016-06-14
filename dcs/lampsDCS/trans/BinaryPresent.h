/*
 * DomParser.cpp
 *
 *  Created on: 27.08.2008
 *      Author: Fedor Gurin
 */

#ifndef BINARYPRESENT_H
#define BINARYPRESENT_H
#include "cl_TransferdataUDP.h"
#include "GenericNode.h"

#include <QDataStream>
#include <QObject>

class TransferDataUDP;

class BinaryPresent:public QObject
{
    Q_OBJECT;
public:
    BinaryPresent(GenericNode *root_,QObject *parent=0);

    //! объект обмена
    TransferDataUDP * toUDP(){return transferUDP;}

    //рекурсивные функции
    void recursGetData(GenericNode* node,QDataStream &out,int &tempBit);

    //! найти элемент по идентификатору
    GenericNode* findNodeByUid(GenericNode *root,uint uid);

    //! прочитать с выравниванием в nums байт
    void getAllign(QDataStream &out,int nums);
private:
    //! класс обмена
    TransferDataUDP *transferUDP;
    //! корневой элемент
    GenericNode *root;
signals:
    void reciveData(GenericNode *);
public slots:
    //! результат обработки запроса
    void slotReciveData(uint uid,QByteArray &datagram);
};

#endif // BINARYPRESENT_H
