#include "EngineDataUI.h"

EngineDataUI::EngineDataUI(GenericData* data_,QObject *parent):IEngineData(parent)
{
    data=data_;
}
uint EngineDataUI::getValue(QString idName,QString& value,TYPE_REQUEST type)
{
    Q_UNUSED(type);
    QStringList tempList = idName.split(tr("."), QString::SkipEmptyParts);

    //! проверка формата команды
    if(tempList.size()<2)
        return 0;
    if(tempList[0]!=tr("UI"))
        return 0;

    uint uid=qrand();

    if(tempList.size()>2)
    {
        int indexTarget=-1;
        if(tempList[1]=="target[0]")
            indexTarget=0;
        else if(tempList[1]=="target[1]")
            indexTarget=1;
        else if(tempList[1]=="target[2]")
            indexTarget=2;
        else if(tempList[1]=="target[3]")
            indexTarget=3;
        else if(tempList[1]=="target[4]")
            indexTarget=4;
        else if(tempList[1]=="target[5]")
            indexTarget=5;
        else if(tempList[1]=="target[6]")
            indexTarget=6;
        else if(tempList[1]=="target[7]")
            indexTarget=7;
        else if(tempList[1]=="target[8]")
            indexTarget=8;
        else if(tempList[1]=="target[9]")
            indexTarget=9;
        else if(tempList[1]=="target[10]")
            indexTarget=10;
        else if(tempList[1]=="target[11]")
            indexTarget=11;
        else if(tempList[1]=="target[12]")
            indexTarget=12;
        else if(tempList[1]=="target[13]")
            indexTarget=13;
        else if(tempList[1]=="target[14]")
            indexTarget=14;
        else if(tempList[1]=="target[15]")
            indexTarget=15;
        else
            indexTarget=-1;

        if(indexTarget!=-1)
        {
            if(tempList[2]==tr("xg"))
            {
                value=QString::number(data->xTarget(indexTarget));
            }else if(tempList[2]==tr("yg"))
            {
                value=QString::number(data->yTarget(indexTarget));
            }else if(tempList[2]==tr("zg"))
            {
                value=QString::number(data->zTarget(indexTarget));
            }else if(tempList[2]==tr("gamma"))
            {
                value=QString::number(data->targetGama(indexTarget));
            }else if(tempList[2]==tr("psi"))
            {
                value=QString::number(data->targetPsi(indexTarget));
            }else if(tempList[2]==tr("tan"))
            {
                value=QString::number(data->targetTeta(indexTarget));
            }else if(tempList[2]==tr("code"))
            {
                //value=QString::number(data->targetCode(indexTarget));
            }else
            {
                 uid=0;
            }
        }else
        {
             uid=0;
        }
    }else
    {
    if(tempList[1]==tr("alfac"))
    {
        value=QString::number(data->alfac());
    }else if(tempList[1]==tr("betac"))
    {
        value=QString::number(data->betac());
    }else if(tempList[1]==tr("gamma"))
    {
        value=QString::number(data->gamac());
    }else if(tempList[1]==tr("psi"))
    {
        value=QString::number(data->psic());
    }else if(tempList[1]==tr("teta"))
    {
        value=QString::number(data->tetac());
    }else if(tempList[1]==tr("untc"))
    {
        value=QString::number(data->untc());
    }else if(tempList[1]==tr("omega_xc"))
    {
        value=QString::number(data->omega_xc());
    }else if(tempList[1]==tr("omega_yc"))
    {
        value=QString::number(data->omega_yc());
    }else if(tempList[1]==tr("omega_zc"))
    {
        value=QString::number(data->omega_zc());
    }else if(tempList[1]==tr("xc"))
    {
        value=QString::number(data->xc());
    }else if(tempList[1]==tr("yc"))
    {
        value=QString::number(data->yc());
    }else if(tempList[1]==tr("zc"))
    {
        value=QString::number(data->zc());
    }else if(tempList[1]==tr("vc"))
    {
        value=QString::number(data->vc());
    }else if(tempList[1]==tr("v_xc"))
    {
        value=QString::number(data->v_xc());
    }else if(tempList[1]==tr("v_yc"))
    {
        value=QString::number(data->v_yc());
    }else if(tempList[1]==tr("v_zc"))
    {
        value=QString::number(data->v_zc());
    }else if(tempList[1]==tr("n_xc"))
    {
        value=QString::number(data->n_xc());
    }else if(tempList[1]==tr("n_yc"))
    {
        value=QString::number(data->n_yc());
    }else if(tempList[1]==tr("n_zc"))
    {
        value=QString::number(data->n_zc());
    }else if(tempList[1]==tr("maxac"))
    {
        value=QString::number(data->maxac());
    }else if(tempList[1]==tr("mc"))
    {
        value=QString::number(data->mc());
    }else if(tempList[1]==tr("latc"))
    {
        value=QString::number(data->latc());
    }else if(tempList[1]==tr("lonc"))
    {
        value=QString::number(data->lonc());
    }else if(tempList[1]==tr("wind_xc"))
    {
        value=QString::number(data->wind_xc());
    }else if(tempList[1]==tr("wind_zc"))
    {
        value=QString::number(data->wind_zc());
    }else if(tempList[1]==tr("Kupr"))
    {
        value=QString::number(data->getKupr());
    }else if(tempList[1]==tr("Regim12"))
    {
        value=QString::number(data->getRegim12());
    }else if(tempList[1]==("LockWrite"))
    {
        value=QString::number(data->getLockWrite());
    }else if(tempList[1]==tr("VPult"))
    {
        value=QString::number(data->getVirtualPult());
    }
    else if(tempList[1]==tr("size_targets"))
    {
        value=QString::number(data->targetNumbers());
    }else if(tempList[1]==tr("regime"))
    {
        value=QString::number(data->regime());
    }
    else
    {
        uid=0;
    }
    }
    return uid;

}
uint EngineDataUI::setValue(QString idName,QString value,TYPE_REQUEST type)
{
    return 0;
    /*Q_UNUSED(type);
    QStringList tempList = idName.split(tr("."), QString::SkipEmptyParts);
    //! проверка формата команды
    if(tempList.size()!=2) return 0;
    if(tempList[0]!=tr("UI")) return 0;

    TRequestEvent rEvent;
    rEvent.module=tr("UI");
    uint uid=qrand();

    rEvent.result=true;
    if(tempList[1]==tr("alfac"))
    {
        data->setAlfac(value.toDouble());
    }else if(tempList[1]==tr("betac"))
    {
        data->setBetac(value.toDouble());
    }else if(tempList[1]==tr("gamac"))
    {
        data->setGamac(value.toDouble());
    }else if(tempList[1]==tr("psic"))
    {
        data->setPsic(value.toDouble());
    }else if(tempList[1]==tr("tetac"))
    {
        data->setTetac(value.toDouble());
    }else if(tempList[1]==tr("untc"))
    {
        data->setUntc(value.toDouble());
    }else if(tempList[1]==tr("omega_xc"))
    {
        data->setOmega_xc(value.toDouble());
    }else if(tempList[1]==tr("omega_yc"))
    {
        data->setOmega_yc(value.toDouble());
    }else if(tempList[1]==tr("omega_zc"))
    {
        data->setOmega_zc(value.toDouble());
    }else if(tempList[1]==tr("vc"))
    {
        data->setVc(value.toDouble());
    }else if(tempList[1]==tr("n_xc"))
    {
        data->setN_xc(value.toDouble());
    }else if(tempList[1]==tr("n_yc"))
    {
        data->setN_yc(value.toDouble());
    }else if(tempList[1]==tr("n_zc"))
    {
        data->setN_zc(value.toDouble());
    }else if(tempList[1]==tr("maxac"))
    {
        data->setMaxac(value.toDouble());
    }else if(tempList[1]==tr("wind_xc"))
    {
        data->setWind_xc(value.toDouble());
    }else if(tempList[1]==tr("wind_zc"))
    {
        data->setWind_zc(value.toDouble());
    }else if(tempList[1]==tr("ComUst"))
    {
        data->setComUst(value.toInt());
    }else if(tempList[1]==tr("NVar"))
    {
        qDebug("NVar=%d\n",value.toInt());
        data->setNumVariant(value.toInt());
        data->setPrNewVariant(true);
    }else if(tempList[1]==tr("Isx"))
    {
        data->setPrNewVariant(value.toInt());
    }else if(tempList[1]==tr("useMap"))
    {
        //data->setUseMap(value.toInt());
    }else if(tempList[1]==tr("yc"))
    {
        data->setYc(value.toDouble());
    }else if(tempList[1]==tr("Cabine"))
    {
        if(value.toInt()==1) data->setControlRegime(KABINA_SAU);

    }else if(tempList[1]==tr("Deter_circle"))
    {
        if(value.toInt()==1) data->setControlRegime(DETERM_CIRCLE);

    }else if(tempList[1]==tr("Deter"))
    {
        if(value.toInt()==1) data->setControlRegime(DETERM);
    }else if(tempList[1]==tr("Cabine_circle"))
    {
        if(value.toInt()==1) data->setControlRegime(KABINA_CIRCLE);
    }else if(tempList[1]==tr("Test_uvod"))
    {
        if(value.toInt()==1) data->setControlRegime(TEST_UVOD);
    }else if(tempList[1]==tr("FDR"))
    {
        if(value.toInt()==1) data->setControlRegime(FDR);
    }else if(tempList[1]==tr("RUD"))
    {
        if(value.toInt()==1) data->setAvtoTiaga(0);
    }else if(tempList[1]==tr("AUT"))
    {
        if(value.toInt()==1) data->setAvtoTiaga(1);
    }else if(tempList[1]==tr("Aerod1"))
    {
        if(value.toInt()==1) data->setDetAerod1(0);
    }else if(tempList[1]==tr("Aerod1Det"))
    {
        if(value.toInt()==1) data->setDetAerod1(1);
    }else if(tempList[1]==tr("Aerod1OFF"))
    {
        if(value.toInt()==1) data->setDetAerod1(2);
    }else if(tempList[1]==tr("ForwardFlight"))
    {
        if(value.toInt()==1) data->setSerpent(true);
    }else if(tempList[1]==tr("SnakeFlight"))
    {
        if(value.toInt()==1) data->setSerpent(false);
    }else if(tempList[1]==tr("WindX"))
    {
        data->setWind_xc(value.toDouble());
    }else if(tempList[1]==tr("WindZ"))
    {
        data->setWind_zc(value.toDouble());
    }else if(tempList[1]==tr("Hrv0"))
    {
        data->setHrv0(value.toDouble());

    }else if(tempList[1]==tr("Hrvmin"))
    {
        data->setHrvmin(value.toDouble());
    }else if(tempList[1]==tr("Hrvmax"))
    {
        data->setHrvmax(value.toDouble());
    }else if(tempList[1]==tr("KursRv"))
    {
        data->setKursRv(value.toDouble());
    }else if(tempList[1]==tr("AlfaSM"))
    {
        data->alfaSM(value.toDouble());
    }else if(tempList[1]==tr("ManevrTarget"))
    {
        data->setManevrTarget(value.toInt());
    }else if(tempList[1]==tr("NumSubVariant"))
    {
        data->setNumVariant(value.toInt());
        data->setPrNewVariant(true);
    }else if(tempList[1]==tr("Refresh"))
    {
        emit refreshCommand();
    }
    else
    {
        uid=0;
        rEvent.result=false;
    }
    rEvent.uid=uid;
    if(uid!=0)
    {
        data->sendData();
        data->refreshData();

        emit signalEventsRequest(rEvent);
    }
    return uid;*/
}

