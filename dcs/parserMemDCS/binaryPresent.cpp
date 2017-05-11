#include "BinaryPresent.h"
#include "Parameter.h"
#include "Structure.h"

#include <QStringList>
#include <QDataStream>

BinaryPresent* BinaryPresent::binary = 0;

BinaryPresent::BinaryPresent(QObject *parent):QObject(parent)
{

}
void BinaryPresent::getData(Node* toNode,QByteArray *fromMem)
{   
    QDataStream out(fromMem, QIODevice::ReadOnly);

    out.setVersion(QDataStream::Qt_4_2);
    out.setByteOrder(QDataStream::LittleEndian);//закомментировать только для отладки

    int bitField=0;
    recursGetData(toNode,out,bitField);
}

void BinaryPresent::setData(Node* fromNode, QByteArray *toMem)
{
    QDataStream in(toMem, QIODevice::WriteOnly);

    in.setVersion(QDataStream::Qt_4_2);
    in.setByteOrder(QDataStream::LittleEndian);//закомментировать только для отладки

    int bitField=0;
    recursSetData(fromNode,in,bitField);
}

void BinaryPresent::recursSetData(Node* node,QDataStream &in,int &bitField)
{
    for(int i=0;i<node->child.size();i++)
    {
        Node *tempNode=node->child[i];
        if(tempNode->type()==Node::STRUCT )
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
            recursSetData(static_cast<Node* >(tempNode),in,bitField);
            if(tempNode->type()==Node::STRUCT)
            {
                Structure *str=static_cast<Structure *> (tempNode);
                if(str->isFieldBits==1)
                {
                    in<<bitField;
                    //dumpForm->addValue(str->offset,QString::number(bitField,2)+tr("Битовое поле-")+str->displayName,4);
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
                }

                in.writeRawData(Parameter::binData(param),param->bytes);

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

void BinaryPresent::getAllign(QDataStream &out,int nums)
{
    quint8  cc=0;
    for(int i=0;i<nums;i++)
    {
        out>>cc;
    }
}
void BinaryPresent::recursGetData(Node* node,QDataStream &out, int &tempBit)
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
        if(tempNode->type()==Node::STRUCT)
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
            recursGetData(static_cast<Node* >(tempNode),out,tempBit_);
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
