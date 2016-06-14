/*
 * DomParser.cpp
 *
 *  Created on: 27.08.2008
 *      Author: Fedor Gurin
 */

#include "BinaryPresent.h"
#include "Parameter.h"
#include "Structure.h"

#include <QStringList>
typedef union
{
    int ii;
    char ch[4];
}TWriteCHAR;

BinaryPresent::BinaryPresent(GenericNode* root_,QObject *parent):QObject(parent)
{
    //! объект для приема UDP пакетов
    transferUDP=new TransferDataUDP(this);

    //! связывание двух сигналов
    connect(transferUDP,SIGNAL(reciveData(uint,QByteArray&)),
            this,SLOT(slotReciveData(uint,QByteArray&)));

    //! корневой элемент
    root = root_;
}

void BinaryPresent::slotReciveData(uint uid,QByteArray& datagram)
{
    int bitField=0;

    //! узел
    GenericNode* node=0;

    QDataStream in(&datagram, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_4_2);
    in.setByteOrder(QDataStream::LittleEndian);

    //! найти узел с uid, если нет, то node = 0
    node = findNodeByUid(root,uid);

    if(node !=0)
    {
        //! рекурсивно выделяем данные
        recursGetData(root,in,bitField);
        //! сообщаем какой элемент изменился
        emit reciveData(node);
    }


}
GenericNode* BinaryPresent::findNodeByUid(GenericNode *root,uint uid)
{
    return 0;
}

void BinaryPresent::getAllign(QDataStream &out,int nums)
{
    quint8  cc=0;
    for(int i=0;i<nums;i++)
    {
        out>>cc;
    }
}
void BinaryPresent::recursGetData(GenericNode* node,QDataStream &out, int &tempBit)
{
    //! переменные для преобразования
    double          dd=0.0;
    float           ff=0.0;
    unsigned int    uii=0;
    int             ii=0;

    quint8  cc=0;
    qint8   sc=0;
    quint16 si=0;

    for(int i=0;i<node->child.size();i++)
    {
        Node *tempNode=node->child[i];
        if(tempNode->type()==Node::STRUCT  || tempNode->type()==Node::GROUP)
        {
            int tempBit_=0;
            if(tempNode->type()==Node::STRUCT)
            {
                Structure *str=static_cast<Structure* >(tempNode);
                if(str->isFieldBits==1)
                {
                    tempBit=0;
                    out>>tempBit_;

                }
            }
            recursGetData(static_cast<GenericNode* >(tempNode),out,tempBit_);
        }else if(tempNode->type()==Node::PARAM)
        {
            Parameter* param=static_cast<Parameter* >(tempNode);
            getAllign(out,param->alignBytes);
            if(param->typeP==Parameter::FLOAT)
            {
                out>>ff;
                ff/=param->factorValue;
                param->setValue(QString::number(ff,'g',8));
            }else if(param->typeP==Parameter::INT)
            {
                out>>ii;
                ii/=param->factorValue;
                param->setValue(QString::number(ii));
            }else if(param->typeP==Parameter::UINT)
            {
                out>>uii;
                uii/=param->factorValue;
                param->setValue(QString::number(uii));
            }else if(param->typeP==Parameter::UCHAR)
            {
                out>>cc;
                cc/=param->factorValue;
                QString num;
                param->setValue(num.setNum(cc));
            }else if(param->typeP==Parameter::CHAR)
            {
                out>>sc;
                QString num;
                sc/=param->factorValue;
                param->setValue(num.setNum(sc));
            }
            else if(param->typeP==Parameter::INT16)
            {
                out>>si;
                si/=param->factorValue;
                param->setValue(QString::number(si));
            }else if(param->typeP==Parameter::DOUBLE)
            {
                /*int div=sizeBuffer%4;
                if(div!=0)
                {
                    for(int i=0;i<div;i++)
                    {
                        sizeBuffer+=1;
                        out>>sc;
                    }
                }*/
                out>>dd;
                dd/=param->factorValue;
                param->setValue(QString::number(dd,'g',8));
            }else if(param->typeP==Parameter::BOOL)
            {
                out>>ii;
                if(ii==1)
                    param->setValue(tr("True"));
                else
                    param->setValue(tr("False"));
            }else if(param->typeP==Parameter::BIT)
            {
                Structure *tempStruct=static_cast<Structure*>(node);
                Parameter *bitParam=param;

                if(bitParam->complexBit==false)
                {
                    unsigned int value=(tempBit>>((tempStruct->numEndBit-tempStruct->numStartBit)-(bitParam->numBit-tempStruct->numStartBit)))&0x00000001;
                    if(value!=0)
                        bitParam->setValue(tr("True"));
                    else
                        bitParam->setValue(tr("False"));
                }else
                {
                    unsigned int mask=1;
                    mask=(mask<<(bitParam->numBit-bitParam->endBit+1))-1;

                    unsigned int value=(tempBit>>
                                        ((tempStruct->numEndBit-tempStruct->numStartBit)
                                         -(bitParam->numBit-tempStruct->numStartBit)))&mask;

                    bitParam->setValue(QString::number(value));
                }
            }else if(param->typeP==Parameter::MCHAR)
            {
                QString value;
                value.clear();

                QByteArray array;
                array.clear();
                for(int i=0;i<param->lengthMCHAR;i++)
                {
                    out>>cc;
                    array.push_back(cc);
                }
                param->setValue(QString(array));
            }
        }
    }
}
