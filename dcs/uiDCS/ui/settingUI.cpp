#include "SettingUI.h"
#include "../globalFunc/gl_func.h"


//#ifdef Q_WS_X11
//#include <arpa/inet.h>
//#define IP "193.232.173.252"
//#define SEND_PORT 4335
//#define RECIVE_PORT 4334
//#endif


#define IP "192.168.58.6"
#define SEND_PORT 4701
#define RECIVE_PORT 4700
#define PORT 4910


SettingUI::SettingUI()
{
    ip=readParamFromXMLFile(nameMainFile,"UI","IP_TARGET");
    if(ip.size()==0) ip=IP;
    send_port=readParamFromXMLFile(nameMainFile,"UI","SEND_PORT").toInt();
    if(send_port==0) send_port=SEND_PORT;
    recive_port=readParamFromXMLFile(nameMainFile,"UI","RECIVE_PORT").toInt();
    if(recive_port==0) recive_port=RECIVE_PORT;
    port=readParamFromXMLFile(nameMainFile,"UI","PORT").toInt();
    if(port==0) port=PORT;

}
