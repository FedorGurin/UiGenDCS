/*
 * DomParser.cpp
 *
 *  Created on: 27.08.2008
 *      Author: Fedor Gurin
 */

#include "BinaryPresent.h"
#include "Parameter.h"
#include "Structure.h"
#include "SIO.h"
#include "../globalFunc/gl_func.h"
#include <QStringList>
typedef union
{
    int ii;
    char ch[4];
}TWriteCHAR;

BinaryPresent::BinaryPresent(QObject *parent):QObject(parent)
{
    transferUDP=new TransferDataUDP(this);
    //получение ответа
    connect(transferUDP,SIGNAL(callbackStatus(bool, uint)),this,SIGNAL(statusR(bool,uint)));

    dumpForm=new DumpForm;
    node=0;
}
void BinaryPresent::getData(GenericNode* node, uint uidNode)
{
    SIO *sio=static_cast<SIO* > (recursSIONode(node));
    this->node=sio;
    transferUDP->getDataRequest(sio,uidNode);
}
void BinaryPresent::getMemIndex(GenericNode* node, uint uid)
{
    SIO *sio=static_cast<SIO* > (recursSIONode(node));
    this->node=sio;
    transferUDP->getMemRequest(sio,uid);
}
void BinaryPresent::setData(GenericNode* node, uint uidNode)
{
    QByteArray datagram;
    QDataStream in(&datagram, QIODevice::WriteOnly);

    in.setVersion(QDataStream::Qt_4_2);
    in.setByteOrder(QDataStream::LittleEndian);//закомментировать только для отладки

    SIO *sio=static_cast<SIO* >(recursSIONode(node));
    this->node=sio;

    dumpForm->clear();
    int bitField=0;
    recursSetData(sio,in,bitField);

    //! имя запроса
    transferUDP->setDataRequest(sio,uidNode,datagram);
}
GenericNode* BinaryPresent::recursSIONode(GenericNode *node)
{
    if(node->type()!=Node::SIO)
    {
        GenericNode* tempNode=recursSIONode((GenericNode*)node->parent);
        if(tempNode!=0)
            return tempNode;
    }
    return node;
}
void BinaryPresent::recursSetData(GenericNode* node,QDataStream &in,int &bitField)
{
    for(int i=0;i<node->child.size();i++)
    {
        Node *tempNode=node->child[i];
        if(tempNode->type()==Node::STRUCT || tempNode->type()==Node::GROUP)
        {
            ////////// подготавливаем рекурсию
            if(tempNode->type()==Node::STRUCT)
            {
                Structure *str=static_cast<Structure *> (tempNode);
                if(str->isFieldBits==1)
                {
                    bitField=0;
                }
            }
            ////////////////////////////////
            recursSetData(static_cast<GenericNode* >(tempNode),in,bitField);
            if(tempNode->type()==Node::STRUCT)
            {
                Structure *str=static_cast<Structure *> (tempNode);
                if(str->isFieldBits==1)
                {
                    in<<bitField;
                    dumpForm->addValue(str->offset,QString::number(bitField,2)+tr("Битовое поле-")+str->displayName,4);
                }
            }
        }else if(tempNode->type()==Node::PARAM)
        {
            Parameter* param=static_cast<Parameter*> (tempNode);

            if(param->typeP!=Parameter::BIT)
            {
                if(param->alignBytes!=0)
                {
                    in.writeRawData(Parameter::alignArray,param->alignBytes);
                    dumpForm->addValue(param->offset-param->alignBytes,tr(" (")+QString::number(param->alignBytes)+tr(") байт, выравнивание"),param->alignBytes);
                }
                dumpForm->addValue(param->offset,param->value+tr(" (")+param->typeStr+tr(") байт")+param->displayName,param->bytes);
                in.writeRawData(Parameter::binData(param),param->bytes);
                qDebug("name=%s, bytes=%d, offset=%d\n",qPrintable(param->displayName),param->bytes,param->offset);
            }
            else if(param->typeP==Parameter::BIT)
            {
                int tempBit=0;

                Structure *tempStruct=static_cast<Structure*> (node);
                if(tempStruct->mkio==true)
                {
                    Parameter *bitParam=param;

                    if(bitParam->complexBit==false)
                    {
                        if(bitParam->value==tr("True")) tempBit=1;

                        tempBit=tempBit<<((tempStruct->numEndBit-tempStruct->numStartBit)-(bitParam->numBit-tempStruct->numStartBit));

                        bitField=bitField|tempBit;
                    }else
                    {
                        unsigned int tempInt=bitParam->value.toUInt();
                        tempInt=tempInt<<((tempStruct->numEndBit-tempStruct->numStartBit)-(bitParam->numBit-tempStruct->numStartBit));
                        bitField=bitField|tempInt;
                    }
                }else
                {
                    Parameter *bitParam=param;
                    if(bitParam->value==tr("True")) tempBit=1;
                    tempBit=tempBit<<(bitParam->numBit-tempStruct->numStartBit);
                    bitField=bitField|tempBit;
                }
            }
        }
    }
}
void BinaryPresent::reciveData(QDataStream &out)
{
    int bitField=0;
    dumpForm->clear();
    recursGetData(node,out,bitField);
}
GenericNode* BinaryPresent::recFindPModule(GenericNode *node,bool stop)
{
    if(stop==true)
        return node;

    GenericNode* tempNode=(GenericNode*)(node->parent);
    if(tempNode->type()==Node::PM)
    {
        stop=true;
        return tempNode;
    }else if(tempNode->type()==Node::GROUP)
        recFindPModule(tempNode,stop);
}
void BinaryPresent::setData(QVector<GenericNode* > *list, uint uidNode)
{
    transferUDP->setDataRequest(list,uidNode);
}
void BinaryPresent::getData(QVector<GenericNode* > *list, uint uidNode)
{
    //this->node=recursSIONode(node);
    transferUDP->getDataRequest(list,uidNode);
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
                    dumpForm->addValue(str->offset,QString::number(tempBit,2)+tr("Битовое поле-")+str->displayName,4);
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
            dumpForm->addValue(param->offset,param->value+tr(" (")+param->typeStr+tr(") байт")+param->displayName,param->bytes);
        }
    }
}
