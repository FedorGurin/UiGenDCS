#ifndef PROXYDCS_H
#define PROXYDCS_H

#include <QObject>
#include <QByteArray>
#include <QSharedMemory>
#include <QHostInfo>
#include <QUdpSocket>
#include <QTimer>

// Библиотека обеспечивает взаимодействие модулей между собой
// у модуля есть два конфигурационных файла io.xml, interfaces.xml

#define MAX_ADDR_IN_PACKET 16
#define LENGTH_IP_STRING 64
//! класс с информацией об модуле
struct DefineAddr
{
    //! глобальный уникальный идентификатор модуля
    quint64 uid_module;
    //! порт с выдачей информации об самом себе
    int portModule;
    //! собственный IP адрес
    QString ip;
    //! информация о хосте
    QHostInfo info;
    //! признак широковещания
    bool broadcast;
    //! кол-во секунд после предыдущего обнавления
    unsigned secLastConnect;
    //! признак потери соединения с узлом
    bool lostConnect;
};
//! заголовок запроса
typedef struct THeadPacket_
{
    //! глобальный уникальный идентификатор модуля отправителя
    quint64 uid_module;
    //! Тип сообщения
    char type; // 0 - пакет с информацией об узле
    //! размер пакета
    unsigned long size;
}THeadPacket;

typedef struct TAddr_
{
    //! идентификатор модуля
    quint64 uid_module;
    //! порт для работы с модулем
    int portModule;
    //! признак широковещания
    bool broadcast;
    //! ip - адрес приложения
    char ip[LENGTH_IP_STRING];
}TAddr;

//! Запрос с информацией об модуле
typedef struct TInfoPacket_
{
    //! заголовок пакета
    THeadPacket head;
    //! кол-во адресов в спсике
    int sizeAddr;
    //! список адресов
    TAddr addr[MAX_ADDR_IN_PACKET];
}TInfoPacket;

//! статус запроса(в случае невозможности выполнения возвращает ошибку)
class StatusRequest
{

};
//! класс запроса
class RequestDCS
{
    //! идентификатор группы (описание в input.xml)
    QString name_group_id;

    //! циклический запрос или одиночный запрос
    bool cyclic;

    //! массив данных, которые пользователь сам разбирает в требуемом порядке(или QDataStream?)
    QByteArray data;

    //! вернуть указатель на параметры

};
//! Класс подключения к распределенной среде
class ProxyDCS:public QObject
{
    Q_OBJECT;
public:
    ProxyDCS(QObject* parent = 0);
signals:
    //! получение запроса
    void signalReciveRequest(RequestDCS* req);
public slots:
    //! отправление запроса
    void slotSendRequest(RequestDCS* req);
private slots:
    //! отправление информации об текущем элементе
    void slotSendInfoOwn();
    //! отправить информации всем участникам среды
    void slotSendInfoAll();
    //! получение данных от других источников
    void slotReciveFromSharePort();
    void slotReciveFromDataPort();
    //! попытка сообщить о себе другим участикам
    //void slotTryToSpeak();

    void checkSLOT();
private:
    //! попытка поиска свободных портов для отправки и получения(true - порт найден)
    bool tryFindFreePort();
    //! проверка есть ли потеря соединения с узлами
    void checkLostConnect();

    //! разбор полученного пакета
    void processPacket(QByteArray& datagram);
    //! разбор пакета с информацией
    void parseInfo(TInfoPacket& recivePacket);
    //! список обнаруженных модулей
    QVector<DefineAddr * > infoModules;
    //! глобальный уникальный идентификатор модуля
    //quint64 uid_module;
    //! список разделяемой памяти входных параметров
    QVector<QSharedMemory* > sharedMemInput;
    //! разделяемая память для выходных параметров
    QSharedMemory sharedMemOutput;
    //! информация о текущем модуле
    DefineAddr info;
    //! общий порт для всех приложений передаем информацию о приложении(выдача каждые 3 сек.)
    int portShare;
    //! признак ожидания и только прослушивания информации от других модулей
    bool listeningInfo;
    bool broadcast;
    //! в секундах последнее обновление информации по разделяемому порту
    int secLastConnectShared;
    //! потеря соединения
    bool lostConnectWithShared;
    //! порт для самоидентификации
    QUdpSocket udpSockDef;
    QUdpSocket udpSockData;
    //! таймер для периодического сообщения о работе модуля(каждые 3 сек.)
    QTimer timerInfo;
    //! таймер попытки подключения к порту portInfo
    QTimer timerStarting;
    //! структуры для сетевого обмена
    TInfoPacket infoPacket;
    TInfoPacket infoRecive;
    THeadPacket headPacket;
};

#endif // PROXYDCS_H
