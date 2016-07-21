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
};
//! заголовок запроса
typedef struct THeadPacket_
{
    //! глобальный уникальный идентификатор модуля
    quint64 uid;
    //! Тип сообщения
    char type;
    //! размер пакета
    unsigned long size;
}THeadPacket;

//! Запрос с информацией об модуле
typedef struct TInfoPacket_
{
    //! заголовок пакета
    THeadPacket head;
    //! порт для работы с модулем
    int portModule;
    //! ip - адрес приложения
    char ip[64];
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
    void slotSendInfo();
    void slotReciveInfo();
    //! попытка сообщить о себе другим участикам
    //void slotTryToSpeak();
private:
    //! попытка поиска свободного порта(true - порт найден)
    bool tryFindFreePort();
    //! разбор полученного пакета
    void processInfoRecive(TInfoPacket& recivePacket);
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
