//! Класс для приема/отправки данных
//!
#ifndef CL_TRANSMIT_H
#define CL_TRANSMIT_H

#include <QUdpSocket>
#include <QDataStream>

#include "../NetworkCommunication/cl_NetworkCommunication.h"
#include "SettingUI.h"

class Transmit:public QObject
{
    Q_OBJECT
public:
    Transmit(NetworkCommunication *networkCommunication=0);

    //! задать размер принимаемых данных
    void setSizeBytes(long size);

    //! сокет
    QUdpSocket udpSocket;

    //! разрешение приема пакетов от УЦВС
    void enableRecive(bool);

    //! буфер для приема данных
    char* dataToSend;

    //! структура с настройками модуля
    SettingUI *setting;

    //! размерность массива для передачи данных
    long sizeDataToSend;

    //! смена портов
    void changePort();

    //!порт отправки
    int portSend;

    //!порт приема
    int portRecive;

    //! объект для соединения
    NetworkCommunication *glNetworkCommunication;

    //! отправить пакет
    void sendDatagram(char*);
    //! признак 1ого приема данных
    bool firstRecive(){return firstRecive_;}
protected:
    //! таймер для обновления данных
    void timerEvent(QTimerEvent *event);
public slots:
    //! обработка полученных пакетов
    void processPendingDatagrams();
    //! слот на готовность соединения
    void slotReadyNetworkCommunication();
signals:
    //! сигнал с полученными данными
    void ReciveData(char*);
private:
    //! признак первого приема данных
    bool firstRecive_;

};
#endif
