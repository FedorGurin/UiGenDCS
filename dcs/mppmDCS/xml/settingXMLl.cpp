#include "SettingXML.h"
#include "../globalFunc/gl_func.h"

//! ip-адреса по умолчанию
#define IP "192.168.58.5"
#define IP_MAIN_PROG "192.168.58.10"
//! порты по умолчанию
#define SEND_PORT 4800
#define RECIVE_PORT 4801
//! порт приема от подчиненной копии программы
#define RECIVE_PORT_SLAVE 4802
#define SEND_PORT_SLAVE 4803
//! имя файла по умолчанию
#define DATA_FILE "data.xml"

//! инициализация статического объекта
SettingXML* SettingXML::setting=0;

SettingXML* SettingXML::getInstance()
{
    if(setting==0)
        setting=new SettingXML();
    return setting;
}

SettingXML::SettingXML()
{
    main_always=false;
    sizeFont=-1;
    allign=0;

    ip=readParamFromXMLFile(nameMainFile,"MPPM","IP_TARGET");
    if(ip.size()==0) ip=IP;

    ip_main_prog=readParamFromXMLFile(nameMainFile,"MPPM","IP_MAIN_PROG");
    if(ip.size()==0) ip=IP_MAIN_PROG;

    fileData=readParamFromXMLFile(nameMainFile,"MPPM","DATA_FILE");
    if(fileData.size()==0) fileData=DATA_FILE;

    send_port=readParamFromXMLFile(nameMainFile,"MPPM","SEND_PORT").toInt();
    if(send_port==0) send_port=SEND_PORT;

    recive_port=readParamFromXMLFile(nameMainFile,"MPPM","RECIVE_PORT").toInt();
    if(recive_port==0) recive_port=RECIVE_PORT;

    send_port_slave=readParamFromXMLFile(nameMainFile,"MPPM","SEND_PORT_SLAVE").toInt();
    if(send_port_slave==0) send_port_slave=SEND_PORT_SLAVE;

    recive_port_slave=readParamFromXMLFile(nameMainFile,"MPPM","RECIVE_PORT_SLAVE").toInt();
    if(recive_port_slave==0) recive_port_slave=RECIVE_PORT_SLAVE;

    sizeFont=readParamFromXMLFile(nameMainFile,"MPPM","SIZE_FONT").toInt();
    if(sizeFont==0) sizeFont=0;
}
