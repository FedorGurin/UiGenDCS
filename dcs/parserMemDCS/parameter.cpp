/*
 * Parameter.cpp
 *
 *  Created on: 27.08.2008
 *      Author: Fedor
 */

#include "parameter.h"
#include "../globalFunc/math_func.h"
#include <QByteArray>
#include <QDataStream>
char Parameter::alignArray[8]={0,0,0,0,0,0,0,0};

Parameter::Parameter(const QDomElement& element,Node *parent):Node()
{
    //! значение неопределено
    value           = "?";
    valuePred       = "?";
    messure         = "";
    /////////////////////////////
    complexBit      = false;
    numBit          = 0;
    endBit          = 0;
    ////////////////////////////    
    bin             = 0;
    fiLamda         = false;
    recFindEnumParam(element);

    hasEnum=testHaveEnumParam();

    restriction=true;
    factorValue=1.0;
    isFactor=false;

    typeP=DOUBLE;

    modifyValueLastStep=false;

    displayName=element.attribute("displayName","no displayName");

    idName=element.attribute("idName","");
    if(idName=="")
        idName=displayName;

    comment=element.attribute("comment","");
    //isDisplay=((element.attribute("isDisplay")).toInt());

    messure=element.attribute("messure","");
    if(messure=="")
        messure=element.attribute("messure","");

    acc=(element.attribute("acc")).toInt();
    fiLamda=(element.attribute("fiLambda","0")).toInt();
    //! длина строки если массив элементов char
    lengthMCHAR=(element.attribute("lengthMCHAR","0")).toInt();
    //! имя по протоколу информационного обмена
    picName=element.attribute("picName","");
    //! условие по которому меняется данный параметр
    condition=element.attribute("condition","");
    readOnly=element.attribute("readOnly","0").toInt();
    //! множитель
    factor=element.attribute("factor","1");
    bool ok=false;
    factorValue=factor.toFloat(&ok);
    if(factor=="0" || ok==false) isFactor=false;
    else isFactor=true;

    QString str=element.attribute("type");
    typeStr=str;

    QString defLimMin="0",defLimMax="0";
    if(str=="double")       {typeP=DOUBLE;  bytes=sizeof(double);   defLimMin="-99999999.9";    defLimMax="99999999.9";}
    else if(str=="int")     {typeP=INT;     bytes=sizeof(int);      defLimMin="-99999999";      defLimMax="99999999";}
    else if(str=="float")   {typeP=FLOAT;   bytes=sizeof(float);    defLimMin="-99999999.9";    defLimMax="99999999.9";}
    else if(str=="bool")    {typeP=BOOL;    bytes=sizeof(bool);}
    else if(str=="bit")     {typeP=BIT;     bytes=0;}
    else if(str=="uchar")   {typeP=UCHAR;   bytes=sizeof(char);}
    else if(str=="char")    {typeP=CHAR;    bytes=sizeof(char);}
    else if(str=="int16")   {typeP=INT16;   bytes=sizeof(short int);}
    else if(str=="uint")    {typeP=UINT;    bytes=sizeof(unsigned); defLimMin="0";              defLimMax="99999999";}
    else if(str=="mchar")   {typeP=MCHAR;   bytes=lengthMCHAR*sizeof(char);}
    else if(str=="ldouble") {typeP=LDOUBLE; bytes=sizeof(long double);   defLimMin="-99999999.9";    defLimMax="99999999.9";}
    //else if(str=="enum")    {typeP=ENUM;}

    ///////////////////////////////////////////////////////////////////
    if(typeP==BIT)
    {
        QString tempNumBit=(element.attribute("numBit"));

        if(tempNumBit.contains("-")==false) numBit=(tempNumBit.toInt());
        else
        {
            complexBit=true;
            value="?";
            QStringList tempList = tempNumBit.split("-", QString::SkipEmptyParts);
            numBit=tempList[0].toInt();
            endBit=tempList[1].toInt();

            predValueMin=0;
            predValueMax=(1<<((numBit-endBit)+1))-1;
        }
    }
    ////////////////////////////////////////////////////////////////////

    if(typeP!=BIT)
    {
        predValueMin=element.attribute("limitMin",defLimMin);
        predValueMax=element.attribute("limitMax",defLimMax);
    }

    str=element.attribute("indicate","default");

//    if(str=="default")          modeIndication=Parameter::DEFAULT_IND;
//    else if(str=="dial")        modeIndication=Parameter::DIAL;
//    else if(str=="hslider")     modeIndication=Parameter::SLIDER_H;
//    else if(str=="vslider")     modeIndication=Parameter::SLIDER_V;
//    else if(str=="grad_min_sec")modeIndication=Parameter::GRAD_MINUTE_SEC;
//    else if(str=="check_box")   modeIndication=Parameter::CHECK_BOX;

//    if(modeIndication==Parameter::GRAD_MINUTE_SEC)
//    {
//        //! значение не определено для
//        value=QString("000°00'00.000000\"");
//    }


    parent->addChild(this);
    addParent(parent);

    //! определим смещение
    if(leftParam()!=0)
    {
        offset=leftParam()->offset+leftParam()->bytes;
    }else
        offset=parent->offset;

    //! подсчет байт для выравнивания
    alignBytes=checkAlign_8byte();

    //! добавим смещение для выравнивания
    offset += alignBytes;

    //! добавляем указанное кол-во байт
    parent->addBytes(bytes+alignBytes);

//    if(isDisplay==true)
//        parent->addVisionChild(this);

    child.clear();
    //! кол-во элементов(если массив)
    howElements=(element.attribute("howElements")).toInt();
    startIndex=(element.attribute("startIndex","0")).toInt();
    //! добавить массив параметров
    addMassiveParam();

}
//! проверка на выравнивание
uint Parameter::checkAlign_4byte()
{
    uint aB=0;
    if(typeP != CHAR && typeP != UCHAR && typeP != INT16 && typeP != BOOL)
    {
        if(offset<sizeof(int) && offset!=0)
            aB=sizeof(int)-offset;
        else
            aB=offset%sizeof(int);
    }
    return aB;
}
//! проверка на выравнивание
uint Parameter::checkAlign_8byte()
{
    uint aB=0;
    if(typeP != CHAR && typeP != UCHAR && typeP != INT16 && typeP != BOOL)
    {
        int div = offset/sizeof(double);
        int mul = div*sizeof(double);
        if(offset>mul && offset!=0)
            aB=sizeof(double)-(offset-mul);
//        else
//            aB=offset%sizeof(double);
    }
    return aB;
}
bool Parameter::testHaveEnumParam(void)
{
    if(listEnum.size()!=0)
        return true;
    return false;
}
void Parameter::recFindEnumParam(const QDomElement& el)
{
    QDomNodeList list=el.elementsByTagName("enum");

    for(int i=0;i<list.size();i++)
    {
        QString nameEnum=(list.at(i).toElement()).attribute("name","none");
        QString valueEnum=(list.at(i).toElement()).attribute("value","0");

        ParamEnum st;
        st.name=nameEnum;
        st.value=valueEnum;

        listEnum.push_back(st);
    }
}
Parameter::Parameter(const Parameter* param, Node *glParent /*глобальный предок*/):Node()
{
    child.clear();//потомков нет

    //! добавить элемент в общее дерево
    if(glParent!=0)
    {
        glParent->addChild(this);
        addParent(glParent);
    }

    offset      = 0;
    bin         = 0;
    value       = "?";
    valuePred   = "?";

    modifyValueLastStep=false;

    restriction     = true;
    valueVariant    = 0;

//    modeEdit=       param->modeEdit;
//    modeIndication= param->modeIndication;

    acc=            param->acc;
    typeP=          param->typeP;

    fiLamda=        param->fiLamda;

    messure=        param->messure;
    comment=        param->comment;

    factor=         param->factor;
    factorValue=    param->factorValue;

    displayName=    param->displayName;
    idName=         param->idName;
    picName=        param->picName;
    condition=      param->condition;

    lengthMCHAR=    param->lengthMCHAR;

    pathName=       param->pathName;

    predValueMin=   param->predValueMin;
    predValueMax=   param->predValueMax;

    listEnum=       param->listEnum;

    complexBit=     param->complexBit;
    numBit=         param->numBit;
    endBit=         param->endBit;

    bytes=          param->bytes;
    typeStr=        param->typeStr;
    readOnly=       param->readOnly;
    startIndex=     param->startIndex;

    //alignBytes=     param->alignBytes;

    //! определим смещение
    if(leftParam()!=0)
    {
        offset=leftParam()->offset+leftParam()->bytes;
    }else if(parent==0)
        offset=0;
    else
        offset=parent->offset;

    //! подсчет байт для выравнивания
    alignBytes=checkAlign_4byte();//внимание <Выключено Выравнивание> 27.03.2014г

    //! добавим смещение для выравнивания
    offset += alignBytes;

    //Node *tempParent=static_cast<Node* > (parent);
    parent->addBytes(bytes+alignBytes);
}
void Parameter::refreshValues(void)
{
    //! обновить значение
    value=*valueVariant;
}
void Parameter::addMassiveParam(void)
{
    if(howElements>1)
    {
        Parameter *newParam=0;

        for(int i=1;i<howElements;i++)
        {
            newParam=new Parameter(this,this->parent);

            newParam->displayName+="["+QString::number(i+1+startIndex)+"]";
            newParam->idName+="["+QString::number(i+1+startIndex)+"]";
            //listForCompleter<<newParam->displayName;

            parent->addChild(newParam);
//            if(this->isDisplay==true)
//            {
//                ((GenericNode*)(this->parent))->addVisionChild(newParam);
//            }
            //newParam->offset= newParam->leftParam()->offset+newParam->leftParam()->bytes;
        }
        displayName+="["+QString::number(startIndex+1)+"]";
        idName+="["+QString::number(startIndex+1)+"]";
    }
}
uint Parameter::alignData(QDataStream &out,Parameter* node)
{
    //! дополнение до int32
    int div=node->bytes%8;
    quint8 value1=0;
    for(int i=0;i<div;i++)
    {
        out>>value1;
    }
    return div;
}

void Parameter::setBinData(char* fromData, Parameter* node)
{
    binData(node);
    memcpy(node->bin,(void*)fromData,node->bytes);

    QByteArray datagram(node->bin,node->bytes);
    QDataStream out(&datagram, QIODevice::ReadOnly);
    out.setByteOrder(QDataStream::LittleEndian);

    switch(node->typeP)
    {
    case LDOUBLE:
    {
        //long double value=0.0;
        //out>>value;
        //node->setValue(QString::number(value));
        break;
    }
    case DOUBLE:
    {
        double value=0.0;
        out>>value;
        node->setValue(QString::number(value));
        break;
    }
    case INT:
    {
        int value=0;
        out>>value;
        node->setValue(QString::number(value));
        break;
    }
    case FLOAT:
    {
        float value=0;
        out>>value;
        node->setValue(QString::number(value));
        break;
    }
    case BOOL:
    {
        bool value=0;
        out>>value;
        node->setValue(QString::number(value));
        break;
    }
    case BIT:
    {
        break;
    }
    case UCHAR:
    {
        quint8 value=0;
        out>>value;
        node->setValue(QString::number(value));
        break;
    }
    case CHAR:
    {
        qint8 value=0;
        out>>value;
        node->setValue(QString::number(value));
        break;
    }
    case INT16:
    {
        quint16 value=0;
        out>>value;
        node->setValue(QString::number(value));
        break;
    }
    case UINT:
    {
        quint16 value=0;
        out>>value;
        node->setValue(QString::number(value));
        break;
    }
    case MCHAR:
    {
//        unsigned p=value.toUInt();
//        memcpy(bin,&p,bytes);
//        break;

//        memcpy(bin,value.toAscii().data(),bytes);
//        break;
    }
    };
}

char* Parameter::binData(Parameter* node)
{
    if(node->bin==0)
        node->bin=new char[node->bytes];

    switch(node->typeP)
    {
    case LDOUBLE:
    {
        long double p=node->value.toDouble()*node->factorValue;
        memcpy(node->bin,&p,node->bytes);
        break;
    }
    case DOUBLE:
    {
        double p=node->value.toDouble()*node->factorValue;
        memcpy(node->bin,&p,node->bytes);
        break;
    }
    case INT:
    {
        int p=node->value.toInt()*node->factorValue;
        memcpy(node->bin,&p,node->bytes);
        break;
    }
    case FLOAT:
    {
        float p=node->value.toFloat()*node->factorValue;
        memcpy(node->bin,&p,node->bytes);
        break;
    }
    case BOOL:
    {
        quint8 p=node->value.toInt();
        memcpy(node->bin,&p,node->bytes);
        break;
    }
    case BIT:
    {

        break;
    }
    case UCHAR:
    {
        quint8 p=node->value.toUInt()*((uint)node->factorValue);
        memcpy(node->bin,&p,node->bytes);
        break;
    }
    case CHAR:
    {
        qint8 p=node->value.toInt()*((int)node->factorValue);
        memcpy(node->bin,&p,node->bytes);
        break;
    }
    case INT16:
    {
        quint16 p=node->value.toInt()*node->factorValue;
        memcpy(node->bin,&p,node->bytes);
        break;
    }
    case UINT:
    {
        unsigned p=node->value.toUInt()*node->factorValue;
        memcpy(node->bin,&p,node->bytes);
        break;
    }
    case MCHAR:
    {
        memcpy(node->bin,node->value.toLatin1().data(),node->bytes);
        break;
    }
    };

    return node->bin;
}

Parameter::~Parameter()
{
    // TODO Auto-generated destructor stub
}
