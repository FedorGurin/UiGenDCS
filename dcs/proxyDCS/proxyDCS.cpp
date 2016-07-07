#include "proxyDCS.h"

//! начальный базовый порт с которого начинается поиск портов
#define BASE_PORT 4900

ProxyDCS::ProxyDCS(QObject *parent):QObject(parent)
{
    //! порт для выдачи информации другим участникам РС
    portInfo = 0;
    //! поиск порта
    tryFindFreePort();
}
bool ProxyDCS::tryFindFreePort()
{
    //! настройка сокетов(поиск свободного порта)
    bool isBind=false;
    int i=1;
    do
    {
        portInfo=BASE_PORT+i;
        isBind=udpSockDef.bind(QHostAddress::LocalHost,portInfo);//,QUdpSocket::DefaultForPlatform);
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
    ip_own = list[2].toString();
    //! подключение функции обработки таймера
    connect(&timerInfo,SIGNAL(timeout()),this,SLOT(slotSendInfo()));
    //! запуск таймера
    timerInfo.start(3000);//3сек

    return true;
}
void ProxyDCS::slotSendInfo()
{
    qDebug()<<"3 sec left";

}

void ProxyDCS::slotSendRequest(RequestDCS* req)
{

}
