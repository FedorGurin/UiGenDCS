#include "proxyDCS.h"

#include <QDataStream>
//! начальный базовый порт с которого начинается поиск портов
#define BASE_PORT 4910
//! базовый порт использующийся при старте приложения
#define BASE_PORT_STARTING 4901


ProxyDCS::ProxyDCS(QObject *parent):QObject(parent)
{
    //! подключение к разделяемому порту
    bool bindShared = false;
    //! здесь нужно сформировать универсальный идентификатор

    //! порт для выдачи информации другим участникам среды
    portInfo = 0;
    //! общий(разделяемый) порт
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
    int recivePort=0;
    while (udpSockDef.hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSockDef.pendingDatagramSize());
        //QHostAddress sender;
        //quint16 senderPort;

        QDataStream in(datagram);
        in>>recivePort;
        /*udpSocket.readDatagram(datagram.data(), datagram.size(),
        &sender, &senderPort);

        processTheDatagram(datagram);*/
    }
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
        portInfo=BASE_PORT+i;
        isBind=udpSockData.bind(QHostAddress::LocalHost,portInfo);//,QUdpSocket::DefaultForPlatform);
        i++;
    }while(isBind == false);

    if(isBind == false)
    {
        qDebug()<<tr("ProxyDCS::Can`t find port for binding");
        return false;
    }

    qDebug()<<tr("ProxyDCS::Find port for information PortInfo=")<<portInfo;

    //! сохраняем текущую информацию о хосте
    info=QHostInfo::fromName(QHostInfo::localHostName());
    QList<QHostAddress> list = info.addresses();
    ip_own = list[0].toString();
    //! подключение функции обработки таймера
    connect(&timerInfo,SIGNAL(timeout()),this,SLOT(slotSendInfo()));
    //! запуск таймера
    timerInfo.start(3000);//3сек

    return true;
}
void ProxyDCS::slotSendInfo()
{
    QByteArray array;
    QDataStream out(array);
    out<<portInfo;
    qDebug()<<"3 sec left";
    bool result=udpSockDef.writeDatagram(array,QHostAddress::LocalHost,portShare);
}

void ProxyDCS::slotSendRequest(RequestDCS* req)
{

}
