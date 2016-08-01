#include "proxyDCS.h"

#include "../globalFunc/utils_func.h"

#include <QTime>
#include <QtGlobal>
#include <QDataStream>
#include <QCoreApplication>
//! начальный базовый порт с которого начинается поиск портов
#define BASE_PORT 4910
//! базовый порт использующийся при старте приложения
#define BASE_PORT_STARTING 4901

#define TIME_INFO 3000 //3sec
#define TIME_LOST_CONNECT 6500
#define MAGIC_NUMBER 0x6871
#define SETTING_FILE "setting.xml"

//! файл с описанием входов/выходов
#define IO_FILE "io.xml"
//! файл с описанием высокоуровневых команд обрабатываемых данным модулем
#define INTERFACES_FILE "interfaces.xml"


RequestDCS::RequestDCS()
{
    stream=new QDataStream(data);
}
ProxyDCS::ProxyDCS(QObject *parent):QObject(parent)
{
    parser = new DomParser();
    //! настройка генератора
    qsrand(QTime::currentTime().msec());
    //! подключение к разделяемому порту
    bool bindShared = false;
    //! признак ожидания и только прослушивания информации от других модулей
    reciveFromShare = true;
    //! все модули начинают с состояния broadcast
    broadcast = true;
    broadcast_prev = true;
    qDebug()<<"Starting in major regime";
    //! обнуление обнаруженных модулей
    infoModules.clear();
    //! здесь нужно сформировать универсальный идентификатор
    info.uid_module = qrand();
    //! текущий идентификатор
    qDebug()<<tr("ProxyDCS:: UID_MODULE=")<<info.uid_module;
    //! порт для выдачи информации другим участникам среды
    info.portModule = 0;
    //! чтение IP из файла настройки
    info.ip     = readParamFromXMLFile(qApp->applicationDirPath()+"/"+SETTING_FILE,"Proxy","IP","127.0.0.1");
    info.name   = readParamFromXMLFile(qApp->applicationDirPath()+"/"+SETTING_FILE,"Proxy","Name","Unknown");
    //! общий порт для получения данных о загруженных модулях
    portShare = BASE_PORT_STARTING;
    bindShared = udpSockDef.bind(QHostAddress::Any,portShare,QAbstractSocket::ShareAddress|QAbstractSocket::ReuseAddressHint);

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
    //! слот для отработки события "Потеря соединения с лидером"
    connect(&timerLostConnect,SIGNAL(timeout()),this,SLOT(checkLostConnect()));
}
void ProxyDCS::setNameModule(QString name)
{
    info.name = name;
}
QString ProxyDCS::nameModule()
{
    return info.name;
}
void ProxyDCS::slotReciveFromDataPort()
{
    QByteArray datagram;
    do
    {
        datagram.resize(udpSockData.pendingDatagramSize());
        qint64 sizeData = udpSockData.readDatagram(datagram.data(),
                                               datagram.size());
        if(sizeData == -1)
            qDebug()<<tr("ProxyDCS::Can`t readDatagram from socket")<<" LINE="<<__LINE__;

    }while  (udpSockData.hasPendingDatagrams());

    //qDebug()<<"Recive from data port"<<" LINE="<<__LINE__;
    processPacket(datagram);
}

void ProxyDCS::slotReciveFromSharePort()
{
    QByteArray datagram;

    //! нужно перестать слушать, перейти в состояние передачи информации всем узлам
    reciveFromShare = false;
    do
    {
        datagram.resize(udpSockDef.pendingDatagramSize());
        qint64 sizeData = udpSockDef.readDatagram(datagram.data(),
                                               datagram.size());
        if(sizeData == -1)
            qDebug()<<tr("ProxyDCS::Can`t readDatagram from socket")<<" LINE="<<__LINE__;

    }while  (udpSockDef.hasPendingDatagrams());
    //timerInfo.start(TIME_INFO);//3сек
    timerLostConnect.start(TIME_LOST_CONNECT);
    //qDebug()<<"Recive from shared sockets"<<" LINE="<<__LINE__;;
    processPacket(datagram);
}
void ProxyDCS::parseInfo(TPacket& recivePacket)
{
    //! приведение данных к требуемому виду
    TInfo *infoAddr=(TInfo*)&recivePacket.data;
    //! сбросить информацию об обновлении для всех элементов
    for(int j=0;j<infoModules.size();j++)
    {
        infoModules[j]->refresh = false;
    }
    for(int i=0;i<infoAddr->sizeAddr;i++)
    {
        bool findModule=false;
        if(infoAddr->addr[i].uid_module == info.uid_module)
            continue;
        //! поиск уже сохраненной информации в списке и ее обновление
        //! а так же помечаем те узлы с которыми была потеряна связь
        for(int j=0;j<infoModules.size();j++)
        {

            if(infoAddr->addr[i].uid_module == infoModules[j]->uid_module)
            {
                infoModules[j]->refresh = true;
                //infoModules[j]->secLastConnect = 0.0;
                findModule = true;
                if(infoModules[j]->uid_module!=recivePacket.head.uid_module)
                    infoModules[j]->broadcast = false;
                else
                    infoModules[j]->broadcast = true;
                break; // остановить цикл поиска
            }
        }
        if(findModule == false)
        {
            //! сохраняем модуль в спсике
            DefineAddr *newAddr = new DefineAddr;
            newAddr->ip = QString(infoAddr->addr[i].ip);

            newAddr->portModule = infoAddr->addr[i].portModule;
            newAddr->uid_module = infoAddr->addr[i].uid_module;
            if(newAddr->uid_module!= recivePacket.head.uid_module)
                newAddr->broadcast = false;
            else
                newAddr->broadcast = true;
            //newAddr->broadcast = recivePacket.addr[i].broadcast;
            //newAddr->secLastConnect = 0;
            newAddr->refresh = true;

            infoModules.append(newAddr);
            qDebug()<<tr("ProxyDCS::add new Module to list, id_module=")<<newAddr->uid_module<<" LINE="<<__LINE__;;
        }
    }
}

void ProxyDCS::processPacket(QByteArray& datagram)
{
    QDataStream outHead(&datagram,QIODevice::ReadOnly);
    outHead.setVersion(QDataStream::Qt_4_2);
    outHead.readRawData((char*)&headPacket,sizeof(THeadPacket));

    if(headPacket.magic_number !=MAGIC_NUMBER)
        return;
    //! обнаружено эхо
    if(headPacket.uid_module == info.uid_module)
    {
        //qDebug()<<tr("ProxyDCS::echo detected, ignore packet")<<" LINE="<<__LINE__;;
        reciveFromShare = true;
        return;
    }

    if(reciveFromShare == false)
        broadcast = false;

    QDataStream out(&datagram,QIODevice::ReadOnly);
    //out.setVersion(QDataStream::Qt_4_2);

    if(headPacket.type == 0) // пакет с информацией об узлах
    {
          out.readRawData((char*)&infoRecive,headPacket.size);
          parseInfo(infoRecive);
    }
    reciveFromShare = true;
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
    connect(&timerInfo,SIGNAL(timeout()),this,SLOT(slotSendInfoAll()));
    //! запуск таймера
    //timerInfo.start(TIME_LOST_CONNECT);//3сек
    timerInfo.start(TIME_INFO);//3сек

    return true;
}
//! проверка есть ли потеря соединения с узлами
void ProxyDCS::checkLostConnect()
{
    //! потеря соединения переход в режим широковещания
    broadcast = true;
    qDebug()<<tr("ProxyDCS::lost connection in id_module = ")<<info.uid_module<<" LINE="<<__LINE__;
}
//! отправление информации о текущем модуле
void ProxyDCS::slotSendInfoAll()
{
    TPacket infoForAll;
    TInfo *infoAddr=(TInfo*)&infoForAll.data;
    int size = infoModules.size() + 1;
    infoForAll.head.magic_number = MAGIC_NUMBER;
    infoForAll.head.size = sizeof(THeadPacket) +  sizeof(int) + size*sizeof(TAddr);
    infoForAll.head.type = 0;
    infoForAll.head.uid_module = info.uid_module;
    infoAddr->sizeAddr = size;


    //! добавляем текущий модуль
    infoAddr->addr[0].uid_module   = info.uid_module;
    infoAddr->addr[0].broadcast    = broadcast;
    infoAddr->addr[0].portModule   = info.portModule;
    strcpy(infoAddr->addr[0].ip,(const char*)info.ip.toLocal8Bit().constData());

    for(int i=0;i<infoModules.size();i++)
    {
        infoAddr->addr[i+1].uid_module = infoModules[i]->uid_module;
        infoAddr->addr[i+1].portModule = infoModules[i]->portModule;
        infoAddr->addr[i+1].broadcast  = infoModules[i]->broadcast;
        strcpy(infoAddr->addr[i+1].ip,(const char*)infoModules[i]->ip.toLocal8Bit().constData());
    }

    qint64 sizeData = -1;
    if(broadcast == true)
    {
#if defined(Q_OS_LINUX)
        sizeData=udpSockDef.writeDatagram((char*)&infoForAll, infoForAll.head.size,
                                               QHostAddress("192.168.10.255"),
                                               portShare);
#else
        sizeData=udpSockDef.writeDatagram((char*)&infoForAll, infoForAll.head.size,
                                               QHostAddress::Broadcast,
                                               portShare);
#endif
        if(sizeData == -1)
            qDebug()<<tr("ProxyDCS::Can`t send broadcast")<<" LINE="<<__LINE__;
    }


    if(broadcast == true && broadcast_prev == false)
        qDebug()<<"Switch to major regime";

    if(broadcast == false && broadcast_prev == true)
        qDebug()<<"Switch to minor regime";


    broadcast_prev = broadcast;
    //qDebug()<<"Send only me";
    slotSendInfoOwn();
}

void ProxyDCS::sendDataToHost(TPacket &packet,QString ip, int portModule)
{
    qint64 sizeData=0;

    sizeData=udpSockData.writeDatagram((char*)&packet, packet.head.size,
                                           QHostAddress(ip),
                                           portModule);
    if(sizeData == -1)
        qDebug()<<tr("ProxyDCS::Can`t send datainfo")<<" LINE="<<__LINE__;
}

//! отправление информации о текущем модуле
void ProxyDCS::slotSendInfoOwn()
{
    TInfo *infoAddr=(TInfo*)&infoPacket.data;

    infoAddr->sizeAddr = 1;

    infoPacket.head.magic_number = MAGIC_NUMBER;
    infoPacket.head.uid_module = info.uid_module;
    infoPacket.head.type = 0;
    infoPacket.head.size =  sizeof(THeadPacket) +  sizeof(int) + infoAddr->sizeAddr*sizeof(TAddr);

    infoAddr->addr[0].uid_module = info.uid_module;
    infoAddr->addr[0].portModule = info.portModule;
    infoAddr->addr[0].broadcast = false;
    strcpy(infoAddr->addr[0].ip,(const char*)info.ip.toLocal8Bit().constData());

    for(int i=0;i<infoModules.size();i++)
    {
        if(infoModules[i]->broadcast!= false)
        {
            sendDataToHost(infoPacket,
                           infoModules[i]->ip,
                           infoModules[i]->portModule);

            return;
        }
    }
}
DefineAddr* ProxyDCS::findAddrByIdModule(QString name)
{
    for(int i=0;i<infoModules.size();i++)
    {
        if(infoModules[i]->name == name)
        {
            return infoModules[i];
        }
    }
    return 0;
}

//! отправление запроса
void ProxyDCS::sendRequest(RequestDCS& req)
{
    NodeBlock *block = parser->findBlockNode(req.uid_block);
    if(block!=0)
    {
        TPacket packet;
        //! !!!!! НУЖНО ПРАВИЛЬНО ЗАПОЛНИТЬ PACKET
        //! ВЫБРАТЬ ПРАВИЛЬНЫЙ ТИП ПАКЕТА
        //!

        DefineAddr *addr = findAddrByIdModule(block->nameModule);
        if(addr != 0)
        {
            //! здесь нужно подготовить пакет для отправки в требуемый модуль
            sendDataToHost(packet,addr->ip,addr->portModule);
        }
    }

}
