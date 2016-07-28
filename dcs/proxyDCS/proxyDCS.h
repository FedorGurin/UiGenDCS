#ifndef PROXYDCS_H
#define PROXYDCS_H

#include <QObject>
#include <QByteArray>
//#include <QSharedMemory>
#include <QHostInfo>
#include <QUdpSocket>
#include <QTimer>
#include <stdint.h>
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
    //! имя программного модуля
    void setNameModule(QString name);
    QString nameModule();
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
    //! проверка есть ли потеря соединения с узлами
    void checkLostConnect();
private:
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
};

#endif // PROXYDCS_H
