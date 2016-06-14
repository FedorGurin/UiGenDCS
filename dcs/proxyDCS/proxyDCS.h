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
    //! отправка запроса для обработки другим модулем
    bool sendRequest(RequestDCS* request);
    //void eEvent(RequestEvent*);
signals:
    //сигнал посылаемый в случае прихода событий от других приложений
    void signalReciveRequest();

};

#endif // PROXYDCS_H
