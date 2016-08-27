#ifndef PROXYDCS_H
#define PROXYDCS_H

#include <QObject>
#include <QByteArray>
//#include <QSharedMemory>
#include <QHostInfo>
#include <QUdpSocket>
#include <QTimer>
#include <stdint.h>

#include "domParserProtocol.h"
// Библиотека обеспечивает взаимодействие модулей между собой
// у модуля есть два конфигурационных файла io.xml, interfaces.xml

#define MAX_ADDR_IN_PACKET 16
#define LENGTH_IP_STRING 64
#define BUF_SIZE 2048
//! класс с информацией об модуле
struct DefineAddr
{
    //! глобальный уникальный идентификатор модуля
    uint32_t uid_module;
    //! порт с выдачей информации об самом себе
    int portModule;
    //! собственный IP адрес
    QString ip;
    //! имя модуля
    QString name;
    //! информация о хосте
    QHostInfo info;
    //! признак широковещания
    bool broadcast;
    //! кол-во секунд после предыдущего обнавления
    //unsigned secLastConnect;
    //! признак обновления данных
    bool refresh;
};
//! заголовок запроса
typedef struct THeadPacket_
{
    //! распознование своих пакетов
    uint32_t magic_number;
    //! глобальный уникальный идентификатор модуля отправителя
    uint32_t uid_module;
    //! Тип сообщения
    uint8_t type; // 0 - пакет с информацией об узле
    //! размер пакета
    uint32_t size;
    //! контрольная сумма
    //uint32_t contrSum;
}THeadPacket;

typedef struct TAddr_
{
    //! идентификатор модуля
    uint32_t uid_module;
    //! порт для работы с модулем
    uint16_t portModule;
    //! признак широковещания
    uint8_t broadcast;
    //! ip - адрес приложения
    char ip[LENGTH_IP_STRING];
}TAddr;

//! Запрос с информацией об модуле
typedef struct TPacket_
{
    //! заголовок пакета
    THeadPacket head;
    //! обобщенные данные
    char data[BUF_SIZE];
}TPacket;
typedef struct TCommand_
{
    //! идентификатор команды(идентификатор блока)
    uint32_t uid_command;
    //! идентификатор модуля который запрашивал обработку команды
    uint32_t uid_answer;
    //! признак того, что передаются аргументы
    uint8_t args;
    //! кол-во аргументов/результатов
    uint8_t size;
    //! список параметров с аргументами или результатами
    char *data;

}TCommand;

typedef struct TInfo_
{
    //! кол-во адресов в списке
    uint16_t sizeAddr;
    //! список адресов
    TAddr addr[MAX_ADDR_IN_PACKET];
}TInfo;
typedef struct TService_
{

}TService;

//! статус запроса(в случае невозможности выполнения возвращает ошибку)
class StatusRequest
{

};
//! класс запроса
class RequestDCS
{
public:
    RequestDCS();

    //! идентификатор блока команды(указан в protocol.xml)
    uint32_t uid_block;

    //! циклический запрос или одиночный запрос()
    bool cyclic;

    //! функция подготовки запроса
    virtual void prepare()
    {

    }

    //! массив данных, которые пользователь сам разбирает в требуемом порядке(или QDataStream?)
    QByteArray data;
};
//! запрос на выполнение команды
class CommandRequestDCS:public RequestDCS
{
public:
    CommandRequestDCS(QString nameId):RequestDCS()
    {

    }

    //! добавить аргумент в команду(здесь тоже нужно обратиься в описание)
    bool append(QString arg)
    {
        listArg<<arg;
    }
    //! вернуть результат по порядку(здесь нужно обратиться в описание)
    QString get(int num)
    {
        return listRes[num];
    }

    QList<QString> listArg;//список аргументов
    QList<QString> listRes;//список результатов
};

//! Класс подключения к распределенной среде
class ProxyDCS:public QObject
{
    Q_OBJECT;
public:
    ProxyDCS(QObject* parent = 0);
    //! имя программного модуля
    void setNameModule(QString name);
    QString nameModule();
signals:
    //! получение запроса
    void signalReciveRequest(RequestDCS* req);
public slots:
    //! отправление запроса
    void sendRequest(RequestDCS& req);
private slots:
    //! отправление информации об текущем элементе
    void slotSendInfoOwn();
    //! отправить информации всем участникам среды
    void slotSendInfoAll();
    //! получение данных от других источников
    void slotReciveFromSharePort();
    void slotReciveFromDataPort();
    //! проверка есть ли потеря соединения с узлами
    void checkLostConnect();
private:
    DefineAddr* findAddrByIdModule(QString name);
    //! отправить данные указаному хосту
    void sendDataToHost(TPacket &packet,QString ip, int portModule);
    //! попытка поиска свободных портов для отправки и получения(true - порт найден)
    bool tryFindFreePort();
    //! разбор полученного пакета
    void processPacket(QByteArray& datagram);
    //! разбор пакета с информацией
    void parseInfo(TPacket& recivePacket);
    //! список обнаруженных модулей
    QVector<DefineAddr * > infoModules;
    //! список разделяемой памяти входных параметров
    //QVector<QSharedMemory* > sharedMemInput;
    //! разделяемая память для выходных параметров
    //QSharedMemory sharedMemOutput;
    //! информация о текущем модуле
    DefineAddr info;
    //! общий порт для всех приложений передаем информацию о приложении(выдача каждые 3 сек.)
    int portShare;
    //! признак ожидания и только прослушивания информации от других модулей
    bool reciveFromShare;
    //! признак широковещания на предыдущем шаге
    bool broadcast_prev;
    //! режим широковещания
    bool broadcast;
    //! порт для широковещательной передачи
    QUdpSocket udpSockDef;
    //! порт точечной передачи
    QUdpSocket udpSockData;
    //! таймер для периодического сообщения о работе модуля(каждые 3 сек.)
    QTimer timerInfo;
    //! таймер попытки подключения к порту portInfo
    QTimer timerLostConnect;
    //! структуры для сетевого обмена
    TPacket infoPacket;
    TPacket infoRecive;
    THeadPacket headPacket;
    //! xml парсер
    DomParser *parser;
};

#endif // PROXYDCS_H
