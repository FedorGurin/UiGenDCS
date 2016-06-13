/*
 * DomParser.cpp
 *
 *  Created on: 27.08.2008
 *      Author: Fedor Gurin
 */

#ifndef BINARYPRESENT_H
#define BINARYPRESENT_H
#include "transferdataUDP.h"
#include "GenericNode.h"
#include "VariantState.h"
//#include "dumpform.h"
#include <QObject>

class TransferDataUDP;

class BinaryPresent:public QObject
{
    Q_OBJECT;
public:
    BinaryPresent(QObject *parent=0);

    void setData(GenericNode* node, uint uid);              //формирование запроса на запись по всем параметрам ПМ
    void setData(QVector<GenericNode* > *list, uint uid);   //формирование запроса на запись "выборочных параметров"

    void getData(QVector<GenericNode* > *list, uint uid);   //фомирование запроса на чтение "выборочные параметры"
    void getData(GenericNode* node, uint uid);              //формирование запроса на чтение по всем параметрам ПМ
    void getMemIndex(GenericNode* node, uint uid);          //индекс в памяти

    QByteArray memBlock(QVector<GenericNode* > *list, uint uid);
    QByteArray memBlock(GenericNode* node, uint uid);

    TransferDataUDP * toUDP(){return transferUDP;}
    GenericNode* recursSIONode(GenericNode *node);
    GenericNode* recFindPModule(GenericNode *node,bool stop);
    void reciveData(QDataStream &out);

    GenericNode *node;
    //! класс обмена
    TransferDataUDP *transferUDP;
    //рекурсивные функции
    void recursSetData(GenericNode* node,QDataStream &in, int &bitField);
    void recursGetData(GenericNode* node,QDataStream &out,int &tempBit);

//    void callbackStatusRequest(bool st,uint uid);
    void hideDump(){dumpForm->hide();}
    void showDump(){dumpForm->show();}
    //! прочитать с выравниванием в nums байт
    void getAllign(QDataStream &out,int nums);
private:
    DumpForm *dumpForm;

signals:
    //! результат обработки запроса
    void statusR(bool status_op,uint uid);
};

#endif // BINARYPRESENT_H
