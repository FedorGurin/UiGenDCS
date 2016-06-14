#include "transmit_models.h"
#include <math.h>

//! начальный базовый порт
#define BASE_PORT 4900
//! временный порт для упрощения задачи
#define SIMPLE_PORT 4999
#define SIMPLE_PORT_REC 4998

#define ONLY_SIMPLE_VER
TransmitModels::TransmitModels(QObject *parent):QObject(parent)
{
    //! признак того, что модуль не главный
    isMain=false;  
    
    //! настройка сокетов(поиск свободного порта)
    bool isBind=false;
    int i=1;
    do
    {        
        port=BASE_PORT+i;
        //isBind=udpSock.bind(port,QUdpSocket::DefaultForPlatform);        
        i++;
    }while(isBind==true);      
    qDebug()<<tr("Use port=")<<port;

    //! связываем сокет с базовым портом
    isBind=udpSockDef.bind(BASE_PORT);
    if(isBind==false)
    {
        qDebug()<<tr("Error bind to port=\n")<<BASE_PORT;
    }
    //! сохраняем текущую информацию о хосте
    info=QHostInfo::fromName(QHostInfo::localHostName());
    //connect(&timer,SIGNAL(timeout()),this,SLOT(slotAmLive()));
    //! запуск таймера 
    //timer.start(100);
    udpSock.bind(SIMPLE_PORT_REC);
    datagram.resize(sizeof(TMRequest));
}
//! функция отправки данных
void TransmitModels::send()
{
   
}
//! отправка пакета с формированием структуры
void TransmitModels::send(int request, char *ptr,int size)
{
    mRequest.head.typeRequest=request;
    mRequest.head.tics=0;
    mRequest.head.dtTics=0;
    mRequest.head.id=0;    
    mRequest.head.size=sizeof(TMRequest)-(SIZE_BUF_DEFAULT-size);

    mRequest.compressed=0;
    mRequest.sizeBuf=size;
    mRequest.err=0;
    memcpy((void*)mRequest.buffer,(void*)ptr,size);
    
    udpSock.writeDatagram((char*)&mRequest,
                            mRequest.head.size,
                            QHostAddress::LocalHost,SIMPLE_PORT);
    /*udpSock.writeDatagram((char*)&mRequest,
     *                             mRequest.head.size,
     *                             QHostAddress("192.168.1.139"),SIMPLE_PORT);*/
}
//! обработка пакета пришедшего из сети
void TransmitModels::recive(int *request, char **ptr,int *size)
{
    *request=-1;
    while(udpSock.hasPendingDatagrams())
    {
        int size_data=udpSock.pendingDatagramSize();
        udpSock.readDatagram(datagram.data(), size_data);
        //! чтение заголовка
        QDataStream outHead(&datagram,QIODevice::ReadOnly);
        outHead.setVersion(QDataStream::Qt_4_6);
        outHead.readRawData((char*)&headRequest,sizeof(THRequest));
        QDataStream out(&datagram,QIODevice::ReadOnly);
        out.setVersion(QDataStream::Qt_4_6);

        //! чтение заголовка
        out.readRawData((char*)&mRequest,headRequest.size);
        //! тип запроса
        *request=headRequest.typeRequest;
        //! указатель на буфер
        *ptr=(char*)mRequest.buffer;
        //! размер структуры
        *size=headRequest.size;
    }
}
//! обработка запроса на самоопределение
void TransmitModels::processDef()
{
    TDefineAddr defAddr;
    QByteArray datagram;
    do
    {
        datagram.resize(udpSockDef.pendingDatagramSize());
        udpSockDef.readDatagram(datagram.data(), datagram.size());
    }while (udpSockDef.hasPendingDatagrams());

    //!
    QDataStream outDefAddr(&datagram,QIODevice::ReadOnly);
    outDefAddr.setVersion(QDataStream::Qt_4_2);
    outDefAddr.readRawData((char*)&defAddr,sizeof(TDefineAddr));

    //! поиск, возможно компьютер уже запомнен
    if(findObjInList(defAddr.head.id)==false)
    {
        //если нет, то добавляем
        listModule.push_back(defAddr);
        sendSelectAddr(defAddr);
    }
}
//! поиск объекта в списке listComp
bool TransmitModels::findObjInList(unsigned int id)
{
    for(int i=0;i<listModule.size();i++)
    {
        if(listModule[i].head.id==id)
            return true;
    }
    return false;
}
//! отправить назначенный сетевой адрес
void TransmitModels::sendSelectAddr(TDefineAddr &defAddr)
{
    //! список адресов
    std::list<QHostAddress> listAddr=info.addresses();
    //! индекс ip адреса
    int index=-1;
    int div=0;
    int save=0xFFFFFFFF;
    //! выбрать адрес максимально совпадающий с текущим адресом    
    for(int i=0;i<listAddr.size();i++)
    {
        for(int j=0;j<10;j++)
        {
            if(listAddr[i].toIPv4Address()==defAddr.ip4Addr[j])
                continue;
            
            int value1=listAddr[i].toIPv4Address();
            int value2=defAddr.ip4Addr[j];
            div=abs(value1-value2); 
            if(div<save)
            {
                save=div;
                index=j;
            }
        }        
    }
    if(index==-1)
        qDebug()<<tr("no find address");
}
//! выдача сигнала о своем включении
void TransmitModels::slotAmLive()
{
    sendSwitchOn();
}
//! выбор ip, объявление о своем включении
void TransmitModels::sendSwitchOn()
{
    //! список адресов
    std::list<QHostAddress> listAddr=info.addresses();

    addr.head.id=0;
    addr.head.typeRequest=0;
    addr.head.size=0;

    for(int i=0;((i<listAddr.size())&&(i<10));i++)
    {
        addr.ip4Addr[i]=listAddr[i].toIPv4Address();
    }    
    udpSockDef.writeDatagram((char*)&addr,
                            addr.head.size,
                            QHostAddress::Broadcast,BASE_PORT);
}
