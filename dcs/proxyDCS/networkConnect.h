#ifndef NETWORK_CONNECT_H
#define NETWORK_CONNECT_H

#include "ICalculateElement.h"
#include "transmit_models.h"
#include "INet.h"

//! обертка для передачи данных через сеть
class NetworkConnect:public INet
{
public:
    //! конструктор
    NetworkConnect(QString idName);
    
    //! отправка пакета с формированием структуры
    void send(TypeRequest request, char *ptr,int size);

    //! расчет задачи
    virtual void calculate();
private:
    //! получение пакета
    void recive();

    //! класс для передачи данных
    TransmitModels *transModels;
};
#endif // NETWORK_CONNECT
