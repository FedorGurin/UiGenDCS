/*
 * GenericData.h
 *
 *  Created on: 13.04.2009
 *      Author: vxuser
 */

#ifndef GENERICDATA_H_
#define GENERICDATA_H_


#include <QObject>
#include "cl_transmit.h"
#include "cl_TableFormSocket.h"
#include "cl_TargetsForm.h"
#include <QVector>
#define PRE 12
#define FORM 'f'

//Класс - интерфейс для отображения вращения самолета
class I3DRoteted
{
public:
    virtual double t()=0;

    virtual double gamac()=0;
    virtual double psic()=0;
    virtual double tetac()=0;

    virtual double untc()=0;//угол наклона траектории

    virtual double alfac()=0;
    virtual double betac()=0;

    virtual double omega_xc()=0;
    virtual double omega_yc()=0;
    virtual double omega_zc()=0;
    /////////////////////////////////////////////////

    virtual void setGamac(double)=0;
    virtual void setPsic(double)=0;
    virtual void setTetac(double)=0;

    virtual void setUntc(double)=0;//угол наклона траектории

    virtual void setAlfac(double)=0;
    virtual void setBetac(double)=0;

    virtual void setOmega_xc(double)=0;
    virtual void setOmega_yc(double)=0;
    virtual void setOmega_zc(double)=0;

};
//Класс - интерфейс для отображения сцены с самолетом и целями
class I3DScene
{
public:
    virtual double xc()=0;
    virtual void setYc(double)=0;
    virtual double yc()=0;
    virtual double zc()=0;

    virtual double vc()=0;
    virtual void setVc(double)=0;

    virtual double v_xc()=0;
    virtual double v_yc()=0;
    virtual double v_zc()=0;

    virtual double n_xc()=0;
    virtual void setN_xc(double)=0;
    virtual double n_yc()=0;
    virtual void setN_yc(double)=0;
    virtual double n_zc()=0;
    virtual void setN_zc(double)=0;

    virtual double maxac()=0;
    virtual void setMaxac(double)=0;
    virtual double mc()=0;
    virtual double latc()=0;
    virtual double lonc()=0;


    virtual double wind_xc()=0;
    virtual void setWind_xc(double)=0;
    virtual double wind_zc()=0;
    virtual void setWind_zc(double)=0;

    /*virtual double gammac()=0;
    virtual double tetac()=0;
    virtual double psic()=0;*/

    virtual double xTarget(int)=0;
    virtual double yTarget(int)=0;
    virtual double zTarget(int)=0;

    virtual double targetGama(int)=0;
    virtual double targetTeta(int)=0;
    virtual double targetPsi(int)=0;

};
enum Regime
{
    START=0,
    ISXODNOE=1,
    STOP=2,
    COMUST=5,
    NO_REGIME=3
};
enum ControlReg
{
    KABINA_SAU,
    DETERM,
    DETERM_CIRCLE,
    KABINA_CIRCLE,
    TEST_UVOD,
    FDR,
    NO_CONTROL_REG
};

class GenericData:  public QObject, public I3DRoteted, public I3DScene
{
    Q_OBJECT;
public:
    GenericData()
    {
        _regime=NO_REGIME;
        _controlReg=NO_CONTROL_REG;
         blockSend=true;
    }
    //! установка объекта приема/передачи данных
    void setTransmitObject(Transmit *transmit_)
    {
        qDebug("setTransmitObject\n");
        transmit=transmit_;
        newTransmitObject();
    }

    //! создать объект для передачи
    virtual void newTransmitObject()=0;

    //! объект для передачи/приема данных
    Transmit *transmit;

    void setTableForm(QVector <cl_TableFormSocket*> table)
    {
        tableForms=table;
    }
    void setTargetsForm(cl_TargetsForm *tar)
    {
        targetsForm=tar;
    }
    //! формы с таблицами параметров самолета
    QVector <cl_TableFormSocket*> tableForms;
    //! формы с таблицами параметров целей
    cl_TargetsForm *targetsForm;

    //объект для передачи/приема данных
    Regime _regime;         //пуск/останов/исходное
    ControlReg _controlReg; //режим управления (из кабины/детерминированный/движение по кругам)

    //! блокирвока отправки
    bool blockSend;
    //! блокировка отправки данных
    void blockSending(bool value){blockSend=value;}

    //! Функции для работы с виртуальным пультом
    virtual void pressButtonStop()=0;
    virtual void pressButtonStart()=0;
    virtual void pressButtonRestart()=0;
    virtual void pressButtonRestartModel(bool value)=0;
    virtual int  getVirtualPult()=0;
    virtual void pressButtonOnVirtualPult(int)=0;
    virtual int  getKupr()=0;
    virtual void pressButtonKupr(int)=0;
    virtual int  getRegim12()=0;
    virtual void pressButtonRegim12(int)=0;
    virtual int  getLockWrite()=0;
    virtual void pressButtonLockWrite(int)=0;

    ////////////////////////////////////////////
    virtual void setHrv0(double)=0;     // нулевая высота радиовысотомера
    virtual void setHrvmin(double)=0;   // минимальная высота радиовысотомера
    virtual void setHrvmax(double)=0;   // максимальная высота радиовысотомера
    virtual void setKursRv(double)=0;   // курс рельефа
    virtual void alfaSM(double)=0;      // угол сверхманевренности
    ///////////////////////////////////////////
    virtual void Vminair(double)=0;
    virtual void Hmaxair(double)=0;
    //! уникальный идентификатор варианта
    virtual unsigned uidVar()=0;
    //! установить текущее значение режима
    void setRegime(Regime r){_regime=r;}
    //! текущее значение режима
    Regime regime(){return _regime;}

    //! обновить поле режима ПУСК/ОСТАНОВ/ИСХОДНОЕ
    virtual void refreshRegime()=0;
    //! установить управление Из Кабины/Детерминированный
    virtual void setControlRegime(ControlReg)=0;
    //! текушее управление
    ControlReg controlRegime(){return _controlReg;}

    //! установить/ узнать режим Автотяги или РУД
    virtual void setAvtoTiaga(bool)=0;
    virtual bool avtoTiaga()=0;

    virtual void setSauIdelPilot(int)=0;
    virtual int  sauIdelPilot()=0;

    virtual void setDetAerod1(int)=0;
    virtual int  detAerod1()=0;

    virtual void setSerpent(bool)=0;
    virtual bool serpent()=0;

    virtual void setManevrTarget(bool)=0;
    virtual bool manevrTarget()=0;
    ///////////////////////////////////////

    //! признак установки
    virtual void setComUst(bool)=0;
    virtual int comUst()=0;
    //! счетчик
    virtual unsigned int counter()=0;
    //! кол-во всех целей полученных из пакета
    virtual int targetNumbers()=0;
    //! кол-во воздушных целей
    virtual int targetAirNum()=0;
    //! установить "признак нового варианта"
    virtual void setPrNewVariant(bool)=0;
    //! текщий значение "признака нового варианта"
    virtual bool prNewVariant()=0;
    //! задать номер варианта
    virtual void setNumVariant(int)=0;
    //! текущий номер варианта
    virtual int numVariant()=0;

    virtual void sendData()=0;      //! отправить данные
    virtual void setData(char*)=0;  //! установить новые данные для передачи(посылки)

    //! создать окно с атмосферными параметрами и геометрией
    virtual void createFormAtmGeo(void)=0;
    virtual void refreshFormAtmGeo(void)=0;

    //! создать окно с кинематическими параметрами
    virtual void createFormKinAircraft(void)=0;
    virtual void refreshFormKinAircraft(void)=0;

    //! создать окно с целями
    virtual void createFormTargets(void)=0;
    virtual void refreshFormTargets(void)=0;

    //! создать окно с константами
    virtual void createFormConst(void)=0;
    virtual void refreshFormConst(void)=0;

    //! создат окно с общими константами
    virtual void createFormCommonConst(void)=0;
    virtual void refreshFormCommonConst(void)=0;

    //! функция посылает сигнал о том что данные приняты
    //! необходима специально для того чтобы уйти от виртуального слота
    virtual void callSlotResived(char*)=0;

    //! установочный угол поворота модельной СК
    virtual float Aust()=0;
    //! обновить визулизационные данные
    virtual void refreshData()=0;
public slots:
    void slotResived(char *ptr){callSlotResived(ptr);}
signals:
    void ReciveData();//получить данные
};

#endif /* GENERICDATA_H_ */
