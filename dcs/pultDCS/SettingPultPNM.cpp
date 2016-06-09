#include "SettingPultPNM.h"
#include "../globalFunc/gl_func.h"

SettingPultPNM::SettingPultPNM()
{
    QString temp=(readParamFromXMLFile(nameMainFile,"VirtualPult","Show"));
    if(temp=="") defaultVirtPult=0;
    else defaultVirtPult=temp.toInt();

    temp=(readParamFromXMLFile(nameMainFile,"VirtualPult","StartPage"));
    if(temp=="") defaultNumPage=1;
    else defaultNumPage=temp.toInt();

}
