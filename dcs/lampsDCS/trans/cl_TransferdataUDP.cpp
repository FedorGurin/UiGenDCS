#include <QMessageBox>
#include <QDataStream>

#include "cl_TransferdataUDP.h"
#include "Parameter.h"

#define RECIVE_PORT 4801

//! обработка принятого пакета
void TransferDataUDP::processPendingDatagrams()
{
    QByteArray datagram;
    do
    {
        datagram.resize(udpSocket.pendingDatagramSize());
        udpSocket.readDatagram(datagram.data(), datagram.size());
    }while (udpSocket.hasPendingDatagrams());

    //! зачитываем заголовок пакета
    QDataStream outHead(&datagram,QIODevice::ReadOnly);
    outHead.setVersion(QDataStream::Qt_4_2);
    outHead.readRawData((char*)&headPacket,sizeof(THead));

    //! зачитываем весь пакет
    QDataStream out(&datagram,QIODevice::ReadOnly);
    out.setVersion(QDataStream::Qt_4_2);
    out.readRawData((char*)&packet,headPacket.size);

    //! обработка пакета
    answerRequest();
}
void TransferDataUDP::answerRequest()
{

    //! создание массива
    datagram=QByteArray::fromRawData(packet.buffer,
                                                (packet.head.size - sizeof(packet.head))*sizeof(char));
    //! запрос обработан успешно
    emit reciveData(headPacket.uid,datagram);
}

TransferDataUDP::TransferDataUDP(BinaryPresent* bin)
{
    //! представление данных
    //binaryPresent=bin;

    memset((void*)&headPacket,  0,  sizeof(THead));
    memset((void*)&packet,      0,  sizeof(TPacket));

    bool result=udpSocket.bind(RECIVE_PORT);
    if(result == false)
    {
        QMessageBox::warning(0,tr("Внимание"),
                 tr("Не удалось связать сокет с портом. Вероятно порт уже открыт"));
        return;
    }

    //! настройка сокета
    udpSocket.setSocketOption(QAbstractSocket::LowDelayOption,1);
    //! прием пакетов
    connect(&udpSocket, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));
}

