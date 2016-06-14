#ifndef TRANSMIT_MODELS_H
#define TRANSMIT_MODELS_H

#include <QUdpSocket>
#include <QObject>
#include <QTimer>
#include <QHostInfo>
#include <QTimer>
#include <QDataStream>

#define SIZE_BUF_DEFAULT 1024

//! обобщенный вид структуры запроса для отправки/получения
typedef struct THeadRequest_
{
    //! идентификатор программного модуля
    unsigned long id;
    //! тип запроса
    unsigned typeRequest;
    //! размер пакета
    unsigned long size;
    //! глобальное время(в тиках)
    unsigned long tics;
    //! предполагаемая задержка(в тиках) измеренная опытным путем
    unsigned long dtTics;
}THRequest;
//! структура для передачи всего буфера данных
typedef struct TBufferRequest_
{
    //! заголовок пакета
    THRequest head;
    //! признак, что буфер сжат
    bool compressed;
    //! код ошибки
    int err;    
    //! размер структуры в буффере
    unsigned long sizeBuf;
    //! буффер с данными(размер массива указан в sizebuf)
    char buffer[SIZE_BUF_DEFAULT];
}TMRequest;
//! структура для самоопределения(списки ip адресов)
typedef struct TDefineAddr_
{
    //! заголовок пакета
    THRequest head;
    //! адреса модели ip4
    unsigned int ip4Addr[10];
    //! выделенный порт для работы
    unsigned int port;    
    //! имя программного модуля
    char name[80];
}TDefineAddr;
//! структура для самоопределения
typedef struct TSelectAddr_
{
    //! заголовок пакета
    THRequest head;
    //! адреса модели ip4
    unsigned int ip4Addr;
    //! выделенный порт для работы
    unsigned int port;
}TSelectAddr;
//! значение органов управления
typedef struct TControl_sticks_
{
    //! заголовок пакета
    THRequest head;
    //! положение ручки по каналу тангажа [-1;1]
    float x_tan;
    //! положение ручки по каналу крена [-1;1]
    float y_tan;
}TControlSticks;

//! обмен данными с другими моделями
class TransmitModels:public QObject
{
    Q_OBJECT;
public:
    TransmitModels(QObject *parent=0);
    //! инициализация модуля
    void init();
    //! прием
    void recive();
    //! отправка данных
    void send();
    //! отправка пакета с формированием структуры
    virtual void send(int request, char *ptr,int size);
    //! проверка получение пакета
    virtual void recive(int *request, char **ptr,int *size);

    //! отправить назначенный сетевой адрес
    void sendSelectAddr(TDefineAddr &defAddr);
    //! отправить запрос на выбор сетевого адреса
    void sendReqNetAddr();
    //! выбор ip, объявление о своем включении
    void sendSwitchOn();
private:
    //! массив для чтения данных
    QByteArray datagram;
    //! порт для самоидентификации 
    QUdpSocket udpSockDef;
    //! сокет приложения
    QUdpSocket udpSock;
    //! таймер для поиска уже запущенных копий
    //QTimer timerDef;   
    //! список обнаруженных компьютеров
    std::list<TDefineAddr> listModule;
    //! очередь запросов
    std::list<TMRequest> listReq;
    //! адрес программного модуля
    TDefineAddr addr;
    //! запрос заголовка
    THRequest headRequest;
    
    //! передача всего буфера
    TMRequest mRequest;
    //! поиск объекта в списке listComp
    bool findObjInList(unsigned int id);
    //! информация о хосте
    QHostInfo info;
    //! таймер
    QTimer timer;
    //! признак, что этот модуль главный
    bool isMain;
    //! номер порта
    unsigned int port;
public slots:
    //! процесс обработки пакетов для самоидентификации
    void processDef();
    //! обработка пакетов
    //void processPacket();
    //! выдача сигнала о своем включении
    void slotAmLive();
};

#endif  
