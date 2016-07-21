#include "proxyDCS.h"

#include <QTime>
#include <QtGlobal>
#include <QDataStream>
//! начальный базовый порт с которого начинается поиск портов
#define BASE_PORT 4910
//! базовый порт использующийся при старте приложения
#define BASE_PORT_STARTING 4901


ProxyDCS::ProxyDCS(QObject *parent):QObject(parent)
{
    //! настройка генератора
    qsrand(QTime::currentTime().msec());
    //! подключение к разделяемому порту
    bool bindShared = false;
    //! обнуление обнаруженных модулей
    infoModules.clear();
    //! здесь нужно сформировать универсальный идентификатор
    info.uid_module = qrand();
    qDebug()<<tr("ProxyDCS:: UID_MODULE=")<<info.uid_module;
    //! порт для выдачи информации другим участникам среды
    info.portModule = 0;
    //! общий порт для получения данных о загруженных модулях
    portShare = BASE_PORT_STARTING;
    bindShared = udpSockDef.bind(QHostAddress::LocalHost,portShare,QUdpSocket::ReuseAddressHint);
    if(bindShared == false)
    {
        qDebug()<<tr("ProxyDCS::Can`t bind to BASE_PORT_SHARED=")<<BASE_PORT_STARTING;
        qDebug()<<tr("Closing application");
        return;
    }

    //! поиск свободного порта
    tryFindFreePort();

    //! получение идентификационных данных от других модулей
    connect(&udpSockDef,SIGNAL(readyRead()),this,SLOT(slotReciveInfo()));

}
void ProxyDCS::slotReciveInfo()
{
    QByteArray datagram;
    do
    {
        datagram.resize(udpSockDef.pendingDatagramSize());
        quint64 size = udpSockDef.readDatagram(datagram.data(),
                                               datagram.size());
        if(size == -1)
            qDebug()<<tr("ProxyDCS::Can`t readDatagram from socket");

    }while  (udpSockDef.hasPendingDatagrams());

    QDataStream outHead(&datagram,QIODevice::ReadOnly);
    outHead.setVersion(QDataStream::Qt_4_2);
    outHead.readRawData((char*)&headPacket,sizeof(THeadPacket));

    //! обнаружено эхо
    if(headPacket.uid == info.uid_module)
    {
        qDebug()<<tr("ProxyDCS::echo detected");
        return;
    }

    QDataStream out(&datagram,QIODevice::ReadOnly);
    out.setVersion(QDataStream::Qt_4_2);

    out.readRawData((char*)&infoRecive,headPacket.size);
    processInfoRecive(infoRecive);
}
void ProxyDCS::processInfoRecive(TInfoPacket& recivePacket)
{
    //! поиск уже сохраненной информации в списке
    for(int i=0;i<infoModules.size();i++)
    {
        if(recivePacket.head.uid == infoModules[i]->uid_module)
            return;
    }

    //! сохраняем модуль в спсике
    DefineAddr *newAddr = new DefineAddr;
    newAddr->ip = QString(recivePacket.ip);
    newAddr->portModule = recivePacket.portModule;
    newAddr->uid_module = recivePacket.head.uid;

    qDebug()<<tr("ProxyDCS::add new Module to list");
}

//! отправляю свои идентификационные данные
/*void ProxyDCS::sendToActors()
{
  udpSockDef.writeDatagram(,info,portShare);
}*/

bool ProxyDCS::tryFindFreePort()
{
    //! настройка сокетов(поиск свободного порта)
    bool isBind=false;
    int i=1;
    do
    {
        info.portModule = BASE_PORT+i;
        isBind=udpSockData.bind(QHostAddress::LocalHost,info.portModule);//,QUdpSocket::DefaultForPlatform);
        i++;
    }while(isBind == false);

    if(isBind == false)
    {
        qDebug()<<tr("ProxyDCS::Can`t find port for binding");
        return false;
    }

    qDebug()<<tr("ProxyDCS::Find port for information portModule=")<<info.portModule;

    //! сохраняем текущую информацию о хосте
    info.info=QHostInfo::fromName(QHostInfo::localHostName());
    QList<QHostAddress> list = info.info.addresses();
    info.ip = list[0].toString();
    //! подключение функции обработки таймера
    connect(&timerInfo,SIGNAL(timeout()),this,SLOT(slotSendInfo()));
    //! запуск таймера
    timerInfo.start(3000);//3сек

    return true;
}
//! отправление информации о текущем модуле
void ProxyDCS::slotSendInfo()
{
    infoPacket.head.uid = info.uid_module;
    infoPacket.head.type = 0;
    infoPacket.head.size = sizeof(TInfoPacket);

    infoPacket.portModule = info.portModule;
    strcpy(infoPacket.ip,(const char*)info.ip.toLocal8Bit().constData());


    qDebug()<<"3 sec left";
    quint64 size=udpSockDef.writeDatagram((char*)&infoPacket, infoPacket.head.size,
                                           QHostAddress::LocalHost,
                                           portShare);

    if(size == -1)
        qDebug()<<tr("ProxyDCS::Can`t send datainfo");
}

void ProxyDCS::slotSendRequest(RequestDCS* req)
{

}
