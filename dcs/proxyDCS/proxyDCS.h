#ifndef PROXYDCS_H
#define PROXYDCS_H

#include <QObject>
// Библиотека обеспечивает взаимодействие модулей между собой
// у модуля есть два конфигурационных файла io.xml, interfaces.xml

class RequestDCS
{

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
private:

};

#endif // PROXYDCS_H
