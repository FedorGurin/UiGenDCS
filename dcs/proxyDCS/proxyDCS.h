#ifndef PROXYDCS_H
#define PROXYDCS_H

#include <QObject>
#include <QByteArray>
// Библиотека обеспечивает взаимодействие модулей между собой
// у модуля есть два конфигурационных файла io.xml, interfaces.xml

//! класс запроса
class RequestDCS
{
    QString id_name;//уникальное имя запроса
    //! массив данных, которые пользователь сам разбирает в требуемом порядке(или QDataStream?)
    QByteArray array;
};

class ProxyDCS:public QObject
{
public:
    ProxyDCS(QObject* parent = 0);
signals:
    //! получение запроса
    void signalReciveRequest(RequestDCS* req);
public slots:
    //! отправление запроса
    void slotSendRequest(RequestDCS* req);
};

#endif // PROXYDCS_H
