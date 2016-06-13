#ifndef CL_TRANSFERDATAUDP_H
#define CL_TRANSFERDATAUDP_H

#include <QUdpSocket>
#include <QByteArray>
#include <QString>
#include <QObject>
//#include <QProgressBar>

//#include "formwait.h"
#include "BinaryPresent.h"
#include "sio.h"

//! класс представления данных
class BinaryPresent;
//! Размер буффера для передачи/получения
#define SIZE_BUFFER 2048
//! Длина массива с именем программного модуля
#define SIZE_NAME 80
//! кол-во параметров в одном пакете TSelectedRequest_
#define SIZE_VALUES 64
//! перечень ошибок
enum{
    NOT_ERROR=0,            /*Ошибок нет*/
    MISMATCH_SIZE_BUFFER=1, /*Не соотвествие размеров буферов между передающими и принимающими программами */
    SMALL_BUFFER=2,         /*Маленький размер буферов*/
    NOT_FOUND_PM=3,         /*Имя программных модулей не совпадает*/
    NULL_PTR_IN_TABLE=4,    /*Нулевой указатель в таблице программных модулей*/
    SIZE_TYPE_IS_ZERO=5,    /*Нулевой размер типа в таблице программных модулей*/
    INDEX_IS_NEG=6,         /*Индекс имеет орицательное значение*/
    INDEX_TOO_MACH=7,       /*Значение индекса превышает размер таблицы запросов*/
    OFFSET_TOO_MACH=8       /*смещение слишком большое*/
};
enum {
    NO_REQUEST=-1,          //! запрос отсутствует
    READ_REQUEST=0,         //! запрос на запись
    WRITE_REQUEST=1         //! запрос на чтение
};

enum {
    MODULE=0,
    SELECTED=1,
    LISTPM=2
};
//#pragma pack(push,1)
//! Структура запроса для отправки/получения
typedef struct THeadRequest_
{
    //! идентификатор пакета (для идентификации одинакоых пакетов)
    unsigned long id;

    //! идентификатор пакета (для обработки запроса)
    unsigned int uid;
    //! Назначение сообщения:
    //              0 - чтение,
    //              1 - запись,
    //              2 - маска
    char rwm;
    //! Тип сообщения
    //              0 - запрос адреса ПМ
    //              1 - запрос для работы со всей структурой
    //              2 - запрос с выбранными параметрами(из разных структур)
    char type;
    //! размер пакета
    unsigned long size;
}THeadRequest;
//! структура для работы сразу со всем модулем
typedef struct TModuleRequest_
{
    //! заголовок
    THeadRequest head;
    //! код ошибки
    char err;
    //! идентификатор запроса(элемент массива в таблице запроса)
    int index;
    //! размер структуры в буфере(если sizeBuf и sizeAllBuf не совпадают, то имеем дело с фрагментом)
    unsigned long sizeBuf;
    //! смещение в буфере( на случай фрагментированного пакета)
    //unsigned long offset;
    //! размер всего буфера( на случай фрагментрированного пакета)
    //unsigned sizeAllBuf;
    //! буффер с данными
    char buffer[SIZE_BUFFER];

}TModuleRequest;
//! структура для запроса адреса по строковому идентификатору
typedef struct TMemRequest_
{
    THeadRequest head;
    char name[SIZE_NAME];
    //! возвращаемое значение
    unsigned addr;  //прямой адрес в памяти структуры
    unsigned size;  //размер структуры
    unsigned index; //индекс в таблице
}TMemRequest;

//! Для работы с ограниченным набором параметров параметров
typedef struct TValueRequest_
{
    char err;               //! код ошибки
    char byte;              //! кол-во байт значения
    unsigned indexInTable;   //! индекс в таблице с начальным адресом
    unsigned offset;         //! смещение
    //unsigned addr;          //! прямой адрес в памяти

    char value[8];          //! значение(размер занимаемой памяти зависит от byte)
}TValueRequest;

typedef struct TSelectedRequest_
{
    THeadRequest head;
    //! кол-во параметров
    unsigned numValues;
    //! значения
    TValueRequest values[SIZE_VALUES];
}TSelectedRequest;
//#pragma pack(pop)
typedef struct
{

}RequestFrag;
//! Класс обмена с целевой машиной для чтения/записи параметров программных модулей через сокеты
class TransferDataUDP:public QObject
{
    Q_OBJECT;
public:
    TransferDataUDP(BinaryPresent* bin);

    enum {
    NO_REQUEST=-1,  //! запрос отсутствует
    READ_REQUEST=0, //! запрос на запись
    WRITE_REQUEST=1 //! запрос на чтение
    };

    enum{
    MODULE=0,
    SELECTED=1,
    LISTPM=2
    };

    //! запрос на получение данных
    virtual void getDataRequest(SIO *node,uint uid);
    virtual void getDataRequest(QVector<GenericNode* > *param, uint uid);
    virtual void getMemRequest(SIO *node, uint uid);

    //! запрос на установку данных
    virtual void setDataRequest(SIO *node,uint uid,QByteArray& datagram);
    virtual void setDataRequest(QVector<GenericNode *> *param, uint uid);

    //! возврат участка памяти при различных типов запросов
    QByteArray memBlock(QVector<GenericNode* > *list);
    QByteArray memBlock(SIO *node,QByteArray& datagram);

    //! класс представления данных
    BinaryPresent *binaryPresent;

    //! задать признак главной программы
    void setMainProg(bool f);

    //! признак главной программы
    bool mainProg;
    
    //! признак того, что идет обработка запроса
    bool processRequest;
    //! закрыть окно "Ожидание данных"
    void closeWindowWait(){formWait->close();}
private:
    //! прогресс операции
    QProgressBar *progressBar;
    //! форма с отображением информации при ожидании данных
    FormWait *formWait;
    //! запретить/разрешить прием данных по UDP
    void enableRecive(bool enable);
    //! функция обработки ответного запроса
    void answerRequest();
    //! функция обработки ответного запроса в случае ошибки
    void answerRequestError();
    //! сокет приема данных от подчиненной версии программы
    QUdpSocket udpSocketSlave;
    //! сокет
    QUdpSocket udpSocket;

    //! запрос на отсылку
    THeadRequest sendHReq;
    //! запрос на прием
    THeadRequest answerHReq;

    TModuleRequest sendModuleReq;
    TModuleRequest answerModuleReq;

    TSelectedRequest sendSReq;
    TSelectedRequest answerSReq;

    TMemRequest sendMemReq;
    TMemRequest answerMemReq;

    //! подсчет времени
    unsigned countTics;
    //! идентификаторы таймеров
    QVector<int> id_Timer;
    //! обработчик таймера
    virtual void timerEvent( QTimerEvent *e );
    //! текущий идентификатор для пакета
    unsigned long currentId;
    //! кол-во отправок
    long countSending;
    //! последний из отправленных элементов
    SIO *lastSendNode;
    //! последний из отправленных списоков
    QVector<GenericNode *> *lastListParam;
signals:
    //! обратный вызов статуса обработки запроса
    void callbackStatus(bool status,uint uid);
public slots:
    //! слот на прием пакетов
    void processPendingDatagrams();
    //! слот на прием пакетов от подчиненной версии программы
    void processPendingDatagramsSlave();
};
#endif
