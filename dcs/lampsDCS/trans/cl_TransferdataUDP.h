#ifndef CL_TRANSFERDATAUDP_H
#define CL_TRANSFERDATAUDP_H

#include <QUdpSocket>
#include <QByteArray>
#include <QString>
#include <QObject>

#include "BinaryPresent.h"

//! класс представления данных
class BinaryPresent;
//! Размер буффера для передачи/получения
#define SIZE_BUFFER 2048

//! cтруктура запроса для отправки/получения
typedef struct THead_
{
    //! уникальный идентификатор
    unsigned long uid;
    //! размер пакета
    unsigned long size;
}THead;

//! структура с заголовком и пакетом данных
typedef struct TPacket_
{
    //! стандартный заголовок
    THead head;
    //! буффер с данными
    char buffer[SIZE_BUFFER];
}TPacket;

//! прием данных
class TransferDataUDP:public QObject
{
    Q_OBJECT;
public:
    TransferDataUDP(BinaryPresent* bin);

private:
    //! функция обработки ответного запроса
    void answerRequest();
    //! сокет
    QUdpSocket udpSocket;
    //! полный пакет данных
    TPacket packet;
    //! только заголовок
    THead headPacket;
    //! сообщение
    QByteArray datagram;

signals:
    //! обратный вызов статуса обработки запроса
    void reciveData(uint uid,QByteArray& datagram);
public slots:
    //! слот на прием пакетов
    void processPendingDatagrams();

};
#endif
