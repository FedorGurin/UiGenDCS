#include "networkConnect.h"
#include "globalData.h"
#include "IEvent.h"
NetworkConnect::NetworkConnect(QString idName):INet(idName)
{
    setFrec(ICalculateElement::Hz100);
    //! запуск модели
    setStart();
    //! передача данных из модели
    transModels=new TransmitModels;
}
//! отправка пакета с формированием структуры
void NetworkConnect::send(TypeRequest request, char *ptr,int size)
{
    transModels->send((int)request,ptr,size);
}
void NetworkConnect::recive()
{
    //! тип запроса
    int type=-1;
    char *ptr=0;
    int size=0;

    //! обработка пакета
    transModels->recive(&type,&ptr,&size);
    TypeRequest typePacket=(TypeRequest)type;
    if(typePacket == CONTROL_STICK)
    {
        //! приведение типов к ручке управления самолетом
        TControlStick *stick=(TControlStick *) (ptr);
        ////// надо сформировать событие //////////

        TEventControlStick e;
        e.x_rus=stick->gamma_rus;
        e.y_rus=stick->tan_rus;
        e.idObj=stick->idObj;
        e.rootSender=this;
        ///////////////////////////////////////////
        ICalculateElement::eEvent(&e);
    }
    else if(typePacket == CREATE_OBJ)
    {

    }
}
 
void NetworkConnect::calculate()
{
    recive();
}
