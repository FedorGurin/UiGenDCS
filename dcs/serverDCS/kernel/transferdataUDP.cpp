#include "transferdataUDP.h"
#include "../globalFunc/math_func.h"
#include "../commonDCS/sio.h"
#include "../commonDCS/parameter.h"
//#include "SettingXML.h"
//#include <QMessageBox>
#include <QDataStream>

#define COUNT_DOUBLE_PACKET 1  //штук
#define COUNT_SHOW_MSG      30 //тиков

#define DEBUG_TRANS


#define RECIVE_PORT 1
#define SEND_PORT 2
#define IP "192.168.1.200"
#ifdef DEBUG_TRANS
int count_error_selected=0;
int count_error_noconfirm=0;
#endif
void TransferDataUDP::enableRecive(bool enable)
{
    if(enable==true)
    {
        connect(&udpSocket, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));
    }
    else udpSocket.disconnect();
}



void TransferDataUDP::processPendingDatagrams()
{
    QByteArray datagram;
    do
    {
        datagram.resize(udpSocket.pendingDatagramSize());
        udpSocket.readDatagram(datagram.data(), datagram.size());
    }while (udpSocket.hasPendingDatagrams());

    QDataStream outHead(&datagram,QIODevice::ReadOnly);
    outHead.setVersion(QDataStream::Qt_4_2);
    outHead.readRawData((char*)&answerHReq,sizeof(THeadRequest));

    QDataStream out(&datagram,QIODevice::ReadOnly);
    out.setVersion(QDataStream::Qt_4_2);

    if(answerHReq.type==MODULE)
        out.readRawData((char*)&answerModuleReq,answerHReq.size);
    else if(answerHReq.type==SELECTED)
        out.readRawData((char*)&answerSReq,     answerHReq.size);
    else if(answerHReq.type==LISTPM)
        out.readRawData((char*)&answerMemReq,   answerHReq.size);

   /* if(mainProg==true)
    {
        //QUdpSocket socket;
        //! ретранслируем данные broadcast`ом
        //socket.writeDatagram((char*)&answerReq,sizeof(TRequest),QHostAddress::Broadcast,setting->recive_port_slave);
    }*/
    if(answerHReq.id == currentId)
    {
        countTics=0;
        for(int i=0;i<id_Timer.size();i++)
        {
            killTimer(id_Timer[i]);
        }
        id_Timer.clear();
        currentId++;

        //! проверка ответа
        answerRequest();
    }else
    {
        count_error_noconfirm++;
        //qDebug("No confirm id\n");
    }
}
void TransferDataUDP::answerRequest()
{
    //formWait->close();
    processRequest=false;
    if(answerHReq.type==MODULE)
    {
        if(answerModuleReq.err!=NOT_ERROR)
        {
            answerRequestError();
            return;
        }
        if(answerHReq.rwm==READ_REQUEST)
        {
            QByteArray datagram=QByteArray::fromRawData(answerModuleReq.buffer,
                                                        answerModuleReq.sizeBuf*sizeof(char));
            QDataStream in(&datagram, QIODevice::ReadOnly);
            in.setVersion(QDataStream::Qt_4_2);
            in.setByteOrder(QDataStream::LittleEndian);//закомментировать только для отладки
            binaryPresent->reciveData(in);
        }
    }
    else if(answerHReq.type==SELECTED)
    {
        if(lastListParam==0)
            return;
        if(lastListParam->size()!=answerSReq.numValues)
        {
            count_error_selected++;

            QString errorString=tr("Не совпадает количество параметров.");
            //formWait->setMessage(tr("Статус: Ошибка - ")+errorString);
            //formWait->show();

            //! обработка запроса закончена
            processRequest=false;
            //! запрос выполнен с ошибкой
            emit callbackStatus(false,answerHReq.uid);
            return;
        }
        if(answerHReq.rwm==READ_REQUEST)
        {
            for(int i=0;i<lastListParam->size();i++)
            {
                GenericNode *tempNode=(*lastListParam)[i];
                Parameter *param=static_cast<Parameter* >(tempNode);
                Parameter::setBinData(answerSReq.values[i].value,param);
            }
        }
        else if(answerHReq.rwm == WRITE_REQUEST)
        {

        }
    }
    else if(answerHReq.type==LISTPM)
    {
        lastSendNode->indexInTable=answerMemReq.index;
    }
    //! запрос обработан успешно
    emit callbackStatus(true,answerHReq.uid);
}
void TransferDataUDP::answerRequestError()
{
    QString errorString="";
    //! Выдача сообщения об ошибке
    if(answerModuleReq.err==MISMATCH_SIZE_BUFFER)   errorString= tr("Не соответствие размеров структур. Проверь описание программного модуля!");
    else if(answerModuleReq.err==SMALL_BUFFER)      errorString= tr("Буфер для передачи слишком мал.");
    else if(answerModuleReq.err==NOT_FOUND_PM)      errorString= tr("Имя программного модуля неизвестно.\nДобавь это имя в список программных модулей модели (файл-datacontrol.cpp)");
    else if(answerModuleReq.err==NULL_PTR_IN_TABLE) errorString= tr("Нулевой указатель в таблице адресов программных модулей.\n Проверь переменную указателя на программный модуль(файл-datacontrol.cpp)");
    else if(answerModuleReq.err==SIZE_TYPE_IS_ZERO) errorString= tr("Нулевой размер типа программного модуля.\n Проверь тип в таблице адресов программных модулей(файл-datacontrol.cpp)");
    else                                            errorString= tr("Неизвестная причина.\nВероятно повреждение пакета.\nПовторите запрос");

    //formWait->setMessage(QString::number(sendModuleReq.index)+tr(" - Ошибка - ")+errorString);
    //formWait->show();
    //! обработка запроса закончена
    processRequest=false;
    //! запрос выполнен с ошибкой
    emit callbackStatus(false,answerHReq.uid);
}

TransferDataUDP::TransferDataUDP(BinaryPresent* bin)
{
    countTics=0;

    //mainProg=true;
    //! обработка запроса закончена
    processRequest=false;
    //! загрузка настроек
    //setting=new SettingXML;
    //! Индикация хода выполнения процесса
    //formWait=new FormWait();
    //! представление данных
    binaryPresent=bin;

    //formWait->setWindowFlags(Qt::Popup);
    //formWait->setWindowModality(Qt::ApplicationModal);

    currentId=0;

    bool result=udpSocket.bind(RECIVE_PORT);
    udpSocket.setSocketOption(QAbstractSocket::LowDelayOption,1);


    memset((void*)&sendHReq,        0,  sizeof(THeadRequest));
    memset((void*)&answerHReq,      0,  sizeof(THeadRequest));

    memset((void*)&sendModuleReq,   0,  sizeof(TModuleRequest));
    memset((void*)&answerModuleReq, 0,  sizeof(TModuleRequest));

    memset((void*)&sendSReq,        0,  sizeof(TSelectedRequest));
    memset((void*)&answerSReq,      0,  sizeof(TSelectedRequest));

    memset((void*)&sendMemReq,      0,  sizeof(TMemRequest));
    memset((void*)&answerMemReq,    0,  sizeof(TMemRequest));

    if(result==false)
    {
//        QMessageBox::warning(0,tr("Внимание"),
//                 tr("Не удалось связать сокет с портом. Вероятно порт уже открыт"));
    }
}
void TransferDataUDP::timerEvent(QTimerEvent *)
{
    countTics++;
    //formWait->setValue(countTics);

    if(countSending<COUNT_DOUBLE_PACKET)
    {
        QUdpSocket socket;
        socket.setSocketOption(QAbstractSocket::LowDelayOption,1);

        QHostAddress addr(IP);
        int port=SEND_PORT;
        switch(sendHReq.type)
        {
            case MODULE:
            {
                socket.writeDatagram((char*)&sendModuleReq,
                                     sendModuleReq.head.size,
                                     addr,port);
                break;
            }
            case SELECTED:
            {
                socket.writeDatagram((char*)&sendSReq,
                                     sendSReq.head.size,
                                     addr,port);
                break;
            }
            case LISTPM:
            {
                socket.writeDatagram((char*)&sendMemReq,
                                     sendMemReq.head.size,
                                     addr,port);
                break;
            }
        };
        //! кол-во отправок
        countSending++;
    }

    //! открываем окно с сообщениями
    /*if(countTics>COUNT_SHOW_MSG)
        formWait->show();*/

    if(countTics==100)
    {
        QString str=tr("Тип запроса:");
        switch(sendHReq.type)
        {
        case MODULE:    {str+="MODULE;  ";     break;}
        case LISTPM:    {str+="LISTPM;  ";     break;}
        case SELECTED:  {str+="SELECTED;  ";   break;}
        };
        str+=tr("Тип операции:");
        if(sendHReq.rwm==READ_REQUEST)
            str+=tr("Чтение;");
        else if(sendHReq.rwm==WRITE_REQUEST)
            str+=tr("Запись;");
        //! выдаем сообщение с ошибкой
       // formWait->setMessage(str+tr(" Статус: Ошибка - ")+tr("Проверь соединение!"));
        for(int i=0;i<id_Timer.size();i++)
        {
            killTimer(id_Timer[i]);
        }
        id_Timer.clear();//очищаем счетчики
        //! сбрасываем счетчик тиков времени
        countTics=0;
        //! сбрасываем счетчик продублированных пакетов
        countSending=0;

        //! обработка запроса закончена
        processRequest=false;
        //! сигнализируем, что запрос не выполнен по истечению тайм-аута
        emit callbackStatus(false,sendHReq.uid);
    }
}
//! запрос на получение данных
void TransferDataUDP::getDataRequest(QVector<GenericNode *> *param, uint uid)
{
    //! если система уже обрабытывает запрос выйти из системы
    if(processRequest==true)
        return;

    lastSendNode=0;
    lastListParam=param;
    //! разрешаем прием
    enableRecive(true);
    processRequest=true;
    countSending=0;
    currentId++;

    int numParam=param->size();
    if(numParam>SIZE_VALUES)
        numParam=SIZE_VALUES;
    for(int i=0;i<numParam;i++)
    {
        Parameter *p=static_cast<Parameter* >((*param)[i]);

        sendSReq.values[i].byte=    p->bytes;
        sendSReq.values[i].offset=  p->offset;
        sendSReq.values[i].err=     0;
        sendSReq.values[i].indexInTable=(static_cast<SIO*>(binaryPresent->recursSIONode(p)))->indexInTable;
    }
    sendSReq.head.rwm=  READ_REQUEST;
    sendSReq.head.type= SELECTED;
    sendSReq.head.uid=  uid;
    sendSReq.head.id=   currentId;
    sendSReq.numValues= numParam;
    sendSReq.head.size= sizeof(THeadRequest)+
                        sizeof(sendSReq.numValues)+
                        numParam*sizeof(TValueRequest);

    sendHReq=           sendSReq.head;


    //qDebug("Selected numValues=%d\n",sendSReq.numValues);

    id_Timer.push_back(startTimer( 15 ));
}
QByteArray TransferDataUDP::memBlock(QVector<GenericNode* > *param)
{
    TSelectedRequest selReq;

    QByteArray byteArray((char*)&selReq,
                         sizeof(THeadRequest)+
                         sizeof(sendSReq.numValues)+
                         param->size()*sizeof(TValueRequest));

    for(int i=0;i<param->size();i++)
    {
        Parameter *p=static_cast<Parameter* >((*param)[i]);

        memcpy(selReq.values[i].value,Parameter::binData(p),p->bytes);
        selReq.values[i].byte=    p->bytes;
        selReq.values[i].offset=  p->offset;
        selReq.values[i].err=     0;
        selReq.values[i].indexInTable=(static_cast<SIO*>(binaryPresent->recursSIONode(p)))->indexInTable;
    }

    selReq.head.rwm=  WRITE_REQUEST;
    selReq.head.type= SELECTED;
    selReq.numValues= param->size();
    selReq.head.uid=  0;
    selReq.head.id=   0;
    selReq.head.size= sizeof(THeadRequest)+
                      sizeof(sendSReq.numValues)+
                      param->size()*sizeof(TValueRequest);

    return byteArray;
}
QByteArray TransferDataUDP::memBlock(SIO* node,QByteArray& datagram)
{
    TModuleRequest moduleReq;
    QByteArray byteArray((char*)&moduleReq,
                         sizeof(TModuleRequest));

    moduleReq.head.rwm= WRITE_REQUEST;
    moduleReq.head.type=MODULE;
    moduleReq.head.uid= 0;
    moduleReq.head.id=  0;
    moduleReq.head.size=sizeof(TModuleRequest)-(SIZE_BUFFER-node->bytes);
    qDebug("head.size=%d\n",sendModuleReq.head.size);

    //! копирование данных в буффер отправки
    char* data=datagram.data();
    for(unsigned i=0;i<node->bytes;i++)
        moduleReq.buffer[i]=data[i];

    moduleReq.sizeBuf=  node->bytes;
    moduleReq.err=      0;
    //moduleReq.offset=   0;
    moduleReq.index=    node->indexInTable;

    return byteArray;
}

void TransferDataUDP::setDataRequest(QVector<GenericNode *> *param, uint uid)
{
    //! если система уже обрабытывает запрос выйти из системы
    if(processRequest==true)
        return;

    lastSendNode=0;
    lastListParam=param;

    //! разрешаем прием
    enableRecive(true);

    processRequest=true;
    countSending=0;
    currentId++;

    int numParam=param->size();
    if(numParam>SIZE_VALUES)
        numParam=SIZE_VALUES;
    for(int i=0;i<numParam;i++)
    {
        Parameter *p=static_cast<Parameter* >((*param)[i]);

        memcpy(sendSReq.values[i].value,Parameter::binData(p),p->bytes);
        sendSReq.values[i].byte=    p->bytes;
        sendSReq.values[i].offset=  p->offset;
        sendSReq.values[i].err=     0;
        SIO *sio=static_cast<SIO*>(binaryPresent->recursSIONode(p));
        sendSReq.values[i].indexInTable=sio->indexInTable;
    }

    sendSReq.head.rwm=  WRITE_REQUEST;
    sendSReq.head.type= SELECTED;
    sendSReq.head.uid=  uid;
    sendSReq.head.id=   currentId;
    sendSReq.head.size= sizeof(THeadRequest)+
                        sizeof(sendSReq.numValues)+
                        numParam*sizeof(TValueRequest);

    sendHReq=           sendSReq.head;
    sendSReq.numValues= numParam;

    id_Timer.push_back(startTimer( 15 ));
}
//! запрос индекса или прямого адреса по указанному имени программного модуля
void TransferDataUDP::getMemRequest(SIO *node, uint uid)
{
    //! если система уже обрабытывает запрос выйти из системы
    if(processRequest==true)
        return;

    lastSendNode=node;
    lastListParam=0;

    //! разрешаем прием
    enableRecive(true);
    processRequest=true;
    countSending=0;
    currentId++;

    //! формируем заголовок
    sendMemReq.head.rwm=    READ_REQUEST;       //запрос на чтение
    sendMemReq.head.type=   LISTPM;             //выдать список
    sendMemReq.head.uid=    uid;                //уникальный идентификатор
    sendMemReq.head.id=     currentId;          //номер отправки
    sendMemReq.head.size=   sizeof(TMemRequest);//размер пакета

    sendMemReq.index=       -1;                 //индекс в таблице
    sendHReq=               sendMemReq.head;    //заголовок

    //qDebug("nameRequest=%s\n",(node->nameRequest).data()->toLatin1());
    strcpy(sendMemReq.name,node->nameRequest.toLatin1().data());//имя запроса
    id_Timer.push_back(startTimer( 15 ));
}

//! запрос на текущего состояния по указанному программному модулю
void TransferDataUDP::getDataRequest(SIO *node, uint uid)
{
    //! если система уже обрабытывает запрос выйти из системы
    if(processRequest==true)
        return;

    lastSendNode=node;
    lastListParam=0;
    //! разрешаем прием
    enableRecive(true);
    processRequest=true;
    countSending=0;
    currentId++;

    //! формируем заголовок
    sendModuleReq.head.rwm= READ_REQUEST;               //запрос на чтение
    sendModuleReq.head.type=MODULE;                     //работа с программными модулями
    sendModuleReq.head.uid= uid;                        //уникальный идентификатор
    sendModuleReq.head.id=  currentId;                  //номер отправки
    sendModuleReq.head.size=sizeof(TModuleRequest)-(SIZE_BUFFER-node->bytes);

    sendModuleReq.index=    node->indexInTable;         //индекс в таблице
    //sendModuleReq.offset=   0;//node->addr;
    sendModuleReq.sizeBuf=  0;
    sendModuleReq.err=      NOT_ERROR;
    sendHReq=               sendModuleReq.head;

    id_Timer.push_back(startTimer( 15 ));
}
//! запрос по указанному программному модулю
void TransferDataUDP::setDataRequest(SIO *node,uint uid,QByteArray& datagram)
{
    if(processRequest==true)
        return;

    lastSendNode=node;
    lastListParam=0;

    //! разрешаем прием
    enableRecive(true);
    processRequest=true;
    countSending=0;
    currentId++;

    sendModuleReq.head.rwm= WRITE_REQUEST;
    sendModuleReq.head.type=MODULE;    
    sendModuleReq.head.uid= uid;
    sendModuleReq.head.id=  currentId;
    sendModuleReq.head.size=sizeof(TModuleRequest)-(SIZE_BUFFER-node->bytes);

    qDebug("head.size=%d\n",sendModuleReq.head.size);

    //! копирование данных в буффер отправки
    char* data=datagram.data();
    for(unsigned i=0;i<node->bytes;i++)
        sendModuleReq.buffer[i]=data[i];

    sendModuleReq.sizeBuf=  node->bytes;
    //sendModuleReq.offset=   0;
    sendModuleReq.err=      0;
    sendModuleReq.index=    node->indexInTable;
    sendHReq=               sendModuleReq.head;

    qDebug("SizeBuf=%d\n",sendModuleReq.sizeBuf);
    id_Timer.push_back(startTimer( 15 ));
}

