#include "EngineVPult.h"
#include <QStringList>

EngineVPult::EngineVPult(QObject *parent):IEngineData(parent)
{
    setSenderName(tr("VPult"));
}

//! получить данные
TRequestEvent EngineVPult::setValue(TCommonRequest request, TYPE_REQUEST type)
{
    TRequestEvent answer;
   /* Q_UNUSED(type);
    QStringList tempList = idName.split(tr("."), QString::SkipEmptyParts);
    if(tempList.size()!=2) return 0;
    if(tempList[0]!=tr("VPult")) return 0;

    TRequestEvent rEvent;
    rEvent.module=tr("UI");
    rEvent.result=true;
    uint uid=qrand();
    qDebug("uid=%d\n",uid);


    if(tempList[1]==tr("Start"))
    {
        qDebug("Start\n");
        if(value.toInt()==1) emit pushStart();
        emit releasedStart();

    }else if(tempList[1]==tr("Stop"))
    {
        if(value.toInt()==1) emit pushStop();
        emit releasedStop();
    }
    else if(tempList[1]==tr("Restart"))
    {
        if(value.toInt()==1) emit pushRestart();
        emit releasedRestart();
    }else if(tempList[1]==tr("On"))
    {
        emit pushOn(value.toInt());
    }else if(tempList[1]==tr("Off"))
    {
        emit pushOn(value.toInt());
    }else if(tempList[1]==tr("Kupr"))
    {
        emit pushSlideKupr(value.toInt());
    }else if(tempList[1]==tr("Regime12"))
    {
        emit pushSlideRegime12(value.toInt());
    }else if(tempList[1]==tr("LockWrite"))
    {
        emit pushSlideLockWrite(value.toInt());
    }else
    {
        uid=0;
        rEvent.result=false;
    }


    rEvent.uid=uid;
    if(uid!=0)
    {
        qDebug("uid!=0\n");
        emit signalEventsRequest(rEvent);
    }
    return uid;*/

    return answer;
}


