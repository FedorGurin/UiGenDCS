#include "proxyDCS.h"

#include "../globalFunc/utils_func.h"

#include <QTime>
#include <QtGlobal>
#include <QDataStream>
//! начальный базовый порт с которого начинается поиск портов
#define BASE_PORT 4910
//! базовый порт использующийся при старте приложения
#define BASE_PORT_STARTING 4901

#define TIME_INFO 3000 //3sec
#define TIME_LOST_CONNECT 6500
ProxyDCS::ProxyDCS(QObject *parent):QObject(parent)
{
    //! настройка генератора
    qsrand(QTime::currentTime().msec());
    //! подключение к разделяемому порту
    bool bindShared = false;
    //! признак ожидания и только прослушивания информации от других модулей
    listeningInfo = true;
    //! обнуление обнаруженных модулей
    infoModules.clear();
    //! здесь нужно сформировать универсальный идентификатор
    info.uid_module = qrand();
    //! текущий идентификатор
    qDebug()<<tr("ProxyDCS:: UID_MODULE=")<<info.uid_module;
    //! порт для выдачи информации другим участникам среды
    info.portModule = 0;
    //! чтение IP из файла настройки
    info.ip = readParamFromXMLFile(".\\setting.xml","Proxy","IP","127.0.0.1");
    //! общий порт для получения данных о загруженных модулях
    portShare = BASE_PORT_STARTING;
    bindShared = udpSockDef.bind(QHostAddress::Any,portShare,QUdpSocket::ReuseAddressHint);

    if(bindShared == false)
    {
        qDebug()<<tr("ProxyDCS::Can`t bind to BASE_PORT_SHARED=")<<BASE_PORT_STARTING;
        qDebug()<<tr("ProxyDCS::Error = ")<<udpSockDef.errorString()<<" Line = "<<__LINE__;
        qDebug()<<tr("ProxyDCS::Paused");
        return;
    }

    //! поиск свободного порта
    bool result = tryFindFreePort();

    if(result == true)
        connect(&udpSockData,SIGNAL(readyRead()),this,SLOT(slotReciveFromDataPort()));
    //! получение идентификационных данных от других модулей
    connect(&udpSockDef,SIGNAL(readyRead()),this,SLOT(slotReciveFromSharePort()));

    //! Только для проверки
    connect(&udpSockDef,SIGNAL(connected()),this,SLOT(checkSLOT()));

}
void ProxyDCS::checkSLOT()
{
    qDebug()<<"SLOT";

}

void ProxyDCS::slotReciveFromDataPort()
{
    QByteArray datagram;
    do
    {
        datagram.resize(udpSockData.pendingDatagramSize());
        quint64 size = udpSockData.readDatagram(datagram.data(),
                                               datagram.size());
        if(size == -1)
            qDebug()<<tr("ProxyDCS::Can`t readDatagram from socket")<<" LINE="<<__LINE__;

    }while  (udpSockData.hasPendingDatagrams());

    //qDebug()<<"Recive from data port"<<" LINE="<<__LINE__;
    processPacket(datagram);
}

void ProxyDCS::slotReciveFromSharePort()
{
    QByteArray datagram;

    //! нужно перестать слушать, перейти в состояние передачи информации всем узлам
    listeningInfo = false;
    do
    {
        datagram.resize(udpSockDef.pendingDatagramSize());
        quint64 size = udpSockDef.readDatagram(datagram.data(),
                                               datagram.size());
        if(size == -1)
            qDebug()<<tr("ProxyDCS::Can`t readDatagram from socket")<<" LINE="<<__LINE__;

    }while  (udpSockDef.hasPendingDatagrams());
    //qDebug()<<"Recive from shared sockets"<<" LINE="<<__LINE__;;
    processPacket(datagram);
}
void ProxyDCS::parseInfo(TInfoPacket& recivePacket)
{
    for(int i=0;i<recivePacket.sizeAddr;i++)
    {
        bool findModule=false;
        if(recivePacket.addr[i].uid_module == info.uid_module)
            continue;
        //! поиск уже сохраненной информации в списке
        for(int j=0;j<infoModules.size();j++)
        {
            if(recivePacket.addr[i].uid_module == infoModules[j]->uid_module)
            {
                infoModules[j]->lostConnect = false;
                infoModules[j]->secLastConnect = 0.0;
                findModule = true;
            }
        }
        if(findModule == false)
        {
            //! сохраняем модуль в спсике
            DefineAddr *newAddr = new DefineAddr;
            newAddr->ip = QString(recivePacket.addr[i].ip);

            newAddr->portModule = recivePacket.addr[i].portModule;
            newAddr->uid_module = recivePacket.addr[i].uid_module;
            newAddr->secLastConnect = 0;
            newAddr->lostConnect = false;

            infoModules.append(newAddr);
            qDebug()<<tr("ProxyDCS::add new Module to list, id_module=")<<newAddr->uid_module<<" LINE="<<__LINE__;;
        }
    }
    //if(listeningInfo == false)
    //    slotSendInfoAll();
}

void ProxyDCS::processPacket(QByteArray& datagram)
{
    QDataStream outHead(&datagram,QIODevice::ReadOnly);
    outHead.setVersion(QDataStream::Qt_4_2);
    outHead.readRawData((char*)&headPacket,sizeof(THeadPacket));

    //! обнаружено эхо
    if(headPacket.uid_module == info.uid_module)
    {
        //qDebug()<<tr("ProxyDCS::echo detected, ignore packet")<<" LINE="<<__LINE__;;
        return;
    }

    QDataStream out(&datagram,QIODevice::ReadOnly);
    //out.setVersion(QDataStream::Qt_4_2);

    if(headPacket.type == 0)
    {
          out.readRawData((char*)&infoRecive,headPacket.size);
          parseInfo(infoRecive);
    }
}
bool ProxyDCS::tryFindFreePort()
{
    //! настройка сокетов(поиск свободного порта)
    bool isBind=false;
    int i=1;
    do
    {
        info.portModule = BASE_PORT+i;
        isBind=udpSockData.bind(QHostAddress(info.ip),info.portModule);//,QUdpSocket::DefaultForPlatform);
        i++;
    }while(isBind == false);

    if(isBind == false)
    {
        qDebug()<<tr("ProxyDCS::Can`t find port for binding")<<" LINE="<<__LINE__;;
        return false;
    }

    qDebug()<<tr("ProxyDCS::Find port for information portModule=")<<info.portModule<<" LINE="<<__LINE__;;

    //! сохраняем текущую информацию о хосте
    info.info=QHostInfo::fromName(QHostInfo::localHostName());
    //QList<QHostAddress> list = info.info.addresses();
    //info.ip = list[0].toString();
    //! подключение функции обработки таймера
    connect(&timerInfo,SIGNAL(timeout()),this,SLOT(slotSendInfoOwn()));
    //! запуск таймера
    timerInfo.start(TIME_INFO);//3сек

    return true;
}
//! проверка есть ли потеря соединения с узлами
void ProxyDCS::checkLostConnect()
{
    //! поиск уже сохраненной информации в списке
    for(int i=0;i<infoModules.size();i++)
    {
        infoModules[i]->secLastConnect += TIME_INFO;
        if(infoModules[i]->lostConnect == true)
            continue;
        if(infoModules[i]->secLastConnect>TIME_LOST_CONNECT)
        {
            infoModules[i]->lostConnect = true;
            qDebug()<<tr("ProxyDCS::lost connection with id_module = ")<<infoModules[i]->uid_module<<" LINE="<<__LINE__;;
        }
    }
}
//! отправление информации о текущем модуле
void ProxyDCS::slotSendInfoAll()
{
    TInfoPacket infoForAll;
    int size = infoModules.size() + 1;
    infoForAll.head.size = sizeof(THeadPacket) +  sizeof(int) + size*sizeof(TAddr);
    infoForAll.head.type = 0;
    infoForAll.head.uid_module = info.uid_module;
    infoForAll.sizeAddr = size;

    //! добавляем текущий модуль
    infoForAll.addr[0].uid_module = info.uid_module;
    infoForAll.addr[0].portModule = info.portModule;
    strcpy(infoPacket.addr[0].ip,(const char*)info.ip.toLocal8Bit().constData());

    for(int i=0;i<infoModules.size();i++)
    {
        infoForAll.addr[i+1].uid_module = infoModules[i]->uid_module;
        infoForAll.addr[i+1].portModule = infoModules[i]->portModule;
        strcpy(infoForAll.addr[i+1].ip,(const char*)infoModules[i]->ip.toLocal8Bit().constData());
    }

    for(int i=0;i<infoModules.size();i++)
    {
        if(infoModules[i]->uid_module != info.uid_module && infoModules[i]->lostConnect == false)
        {
            //! отправляем данные
            quint64 size=udpSockData.writeDatagram((char*)&infoForAll, infoForAll.head.size,
                                                   QHostAddress(infoModules[i]->ip),
                                                   infoModules[i]->portModule);

            if(size == -1)
                qDebug()<<tr("ProxyDCS::Can`t send datainfo")<<" LINE="<<__LINE__;;
        }
    }
}

//! отправление информации о текущем модуле
void ProxyDCS::slotSendInfoOwn()
{
    checkLostConnect();

    infoPacket.sizeAddr = 1;

    infoPacket.head.uid_module = info.uid_module;
    infoPacket.head.type = 0;
    infoPacket.head.size =  sizeof(THeadPacket) +  sizeof(int) + infoPacket.sizeAddr*sizeof(TAddr);

    infoPacket.addr[0].uid_module = info.uid_module;
    infoPacket.addr[0].portModule = info.portModule;
    strcpy(infoPacket.addr[0].ip,(const char*)info.ip.toLocal8Bit().constData());


    //int status = udpSockDef.state();
    //qDebug()<<tr("ProxyDCS::sendInfo(3 sec left)");
    quint64 size=udpSockDef.writeDatagram((char*)&infoPacket, infoPacket.head.size,
                                           QHostAddress::Broadcast,
                                           portShare);

    if(size == -1)
        qDebug()<<tr("ProxyDCS::Can`t send datainfo")<<" LINE="<<__LINE__;;
}

void ProxyDCS::slotSendRequest(RequestDCS* req)
{

}
