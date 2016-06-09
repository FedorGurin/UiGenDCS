#include "cl_transmit.h"
#include <QUdpSocket>
#include <QtGlobal>

#define NUM_ITER 2

Transmit::Transmit(NetworkCommunication *networkCommunication)
{
    //! указатель на буфер-приемник
    dataToSend=0;
    //! признак получения первого пакета
    firstRecive_=false;
    //! размер буфера dataToSend
    sizeDataToSend=0;
    //! настройки приложения
    setting=new SettingUI;
    //! объект для взаимодействия по сети
    glNetworkCommunication=networkCommunication;
    //! запрет любого приема данных
    enableRecive(false);
    //! соединение по сети
    connect(networkCommunication,SIGNAL(ready()),this,SLOT(slotReadyNetworkCommunication()));
    //! порт приема пакетов
    portRecive=setting->recive_port;
}
void Transmit::setSizeBytes(long size_)
{
    if(dataToSend!=0)
        delete dataToSend;

    if(size_ == 0)
        qDebug("Error in constructor of Transmit class\n");
    else
        dataToSend=new char[size_];

    if(dataToSend == 0)
        qDebug("Error in constructor Transmit object.Memory not allocate\n");

    sizeDataToSend = size_;
}
void Transmit::slotReadyNetworkCommunication()
{
    if(glNetworkCommunication->mainProgram == false)
    {
        changePort();
        enableRecive(true);
    }
}

void Transmit::sendDatagram(char* v)
{
    QUdpSocket socket;
    QByteArray datagram;
    QDataStream in(&datagram, QIODevice::WriteOnly);

    in.setVersion(QDataStream::Qt_4_6);
    in.setFloatingPointPrecision(QDataStream::DoublePrecision);
    //in.setByteOrder(QDataStream::LittleEndian);

    in.writeRawData(v,sizeDataToSend);

    socket.writeDatagram(datagram,QHostAddress(setting->ip),setting->send_port);
}
void Transmit::processPendingDatagrams()
{
    static int count=0;
    QByteArray datagram;
    do
    {
        datagram.resize(udpSocket.pendingDatagramSize());
        udpSocket.readDatagram(datagram.data(), datagram.size());
    }while (udpSocket.hasPendingDatagrams());

    //увеличиваем счетчик принятых пакетов
    count++;

    if(count == NUM_ITER)
    {
        firstRecive_ = true;
        count=0;

        QDataStream out(&datagram,QIODevice::ReadOnly);
        out.setVersion(QDataStream::Qt_4_6);
        out.setFloatingPointPrecision(QDataStream::DoublePrecision);
        out.readRawData(dataToSend,sizeDataToSend);

        //если программа главная, и в xml-указано, что этот ранг не может быть изменен, то есть копия программы всегда главная
        if(glNetworkCommunication->alwaysMain() == false &&
           glNetworkCommunication->mainProgram == true) glNetworkCommunication->sendBroadcastDatagram(dataToSend,
                                                                                                      sizeDataToSend,
                                                                                                      setting->port);
        //! высылаем сигнал с полученными данными
        emit ReciveData(dataToSend);
        //!
        glNetworkCommunication->recivedDataUI();
    }
}
void Transmit::timerEvent(QTimerEvent *event)
{

}
//! изменение номера порта
void Transmit::changePort()
{
    //! порт по приему
    udpSocket.abort();
    portRecive=setting->port;
}
//! разрешение на прием данных
void Transmit::enableRecive(bool enable)
{
    if(enable == true)
    {
        qDebug("void Transmit::enableRecive(true)\n");
        udpSocket.abort();
        udpSocket.bind(portRecive);
        connect(&udpSocket, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));
    }else
    {
        qDebug("void Transmit::enableRecive(false)\n");
        disconnect(&udpSocket, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));
        udpSocket.close();
    }
}
