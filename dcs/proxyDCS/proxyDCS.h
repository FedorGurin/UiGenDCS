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
private:
    //! попытка поиска свободного порта(true - порт найден)
    bool tryFindFreePort();

    //! список разделяемой памяти входных параметров
    QVector<QSharedMemory* > sharedMemInput;
    //! разделяемая память для выходных параметров
    QSharedMemory sharedMemOutput;
    //! информация о хосте
    QHostInfo info;
    //! порт с выдачей информации об самом себе(выдача каждые 3 сек.)
    int portInfo;
    //! собственный IP адрес
    QString ip_own;
    //! порт для самоидентификации
    QUdpSocket udpSockDef;
    //! таймер для периодического сообщения о работе модуля(каждые 3 сек.)
    QTimer timerInfo;
};

#endif // PROXYDCS_H
