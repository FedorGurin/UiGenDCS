#ifndef CL_DATAFORWORKST50BINS_H
#define CL_DATAFORWORKST50BINS_H


#include "GenericData.h"
#include "../globalFunc/gl_func.h"

namespace T50BINS
{
#define MAXNUMBERTHREAD     6
#define NUMBERSLAVE         3
#define NUMBER_TARGET       32
#define NUMBER_VARIANT      32
#define NUMBER_TVACP        8

#define  NUMBERBUFFERMODEL  6   //  раньше  было 4



//#include "kdli_func_glf.h"

#pragma pack(push,4)

typedef struct _Tkinematiks_aircraft
{
    float nxt_aircraft;
    float prs_aircraft;
    float niy1_aircraft;
    float niy2_aircraft;
    float pniy1_aircraft;
    float pniy2_aircraft;
    float nz_aircraft;
    float pnz_aircraft;
    float omvx1_aircraft;
    float omvx2_aircraft;
    float Knx_aircraft;
    float Talfa_aircraft;
    float alfa_bal_aircraft;
    float Tbeta_aircraft;
    float nydop_aircraft;
    float psi_aircraft;
    float teta_aircraft;
    float gamav_aircraft;
    float psic_aircraft;
    float tetac_aircraft;
    float gamac_aircraft;
    float alfa_aircraft;
    float beta_aircraft;
    float omcx_aircraft;
    float omcy_aircraft;
    float omcz_aircraft;
    float ncx_aircraft;
    float ncy_aircraft;
    float ncz_aircraft;
    float vc_aircraft;
    float vcx_aircraft;
    float vcy_aircraft;
    float vcz_aircraft;
    float M_aircraft;
    double xc_aircraft;
    double yc_aircraft;
    double zc_aircraft;
    float nypol_aircraft;
    double t_pol_aircraft;
    float  G_engine;
    float v_aircraft;
    float alfaf_aircraft;
    float nypr_aircraft;
    float nzpr_aircraft;
    float nvy_aircraft;
}Tkinematiks_aircraft;

typedef struct _Tgeography_Earth
{
    float fiust_geography;
    float limdaust_geography;
    float Aust_geography;
    double x0_geography;
    double z0_geography;
    float A0_geography;
    float sa_geography;
    float ca_geography;
    float fi0_geography;
    float limda0_geography;
    float Rfi_1_geography;
    float Rlimda_1_geography;
    float R_Earth_geography;
    float Pr_start_geography;
    float device_externals_geography;
    float fit_geography;
    float limdat_geography;
    float Au_geography;
    float v_Earth_geography;
    float DeltaMSkl;
    float DeltaM0;
    int   Pr10G[2];    //признак  10 Гц  служебный признак для форм. Got10G
    int   CmGK;     //Смена Георграфических координат
    float Au_geographyPrev;
    float limdat_geographyPrev;
    float fit_geographyPrev;

    int CountPrlg; //счётчик пролонгации

    int Prlg; //признак  пролонгации

    float dtFit;//

    float dtLamdat;//

}Tgeography_Earth;


typedef struct _TDSDU
{
    int  avtSU;
    int countSAU;
    short  int  U_tan_avt;
    short int  U_kren_avt;
}TDSDU;

typedef struct _TDRUD
{
    float   URUD;
    int  urud_left;
    int  urud_right;
    int  urud_left_in;
    int  urud_right_in;
    //int  urud_zap_in;
}TDRUD;

typedef struct _TDRUS
{
    int u_tan_zap;
    int u_kren_zap;
    int u_tan_zap_in;
    int u_kren_zap_in;
    int pr_isxodnoe_rus;
    float x_kren_rus;
    float x_tan_rus;
    int j;
    int useRUS;
    int u_rus_tan;
    int u_rus_kren;
}TDRUS;


typedef struct _TDPED
{
    int u_ped_zap_in;
    int u_ped_zap;
    float x_ped;
    int u_ar;
}TDPED;


typedef struct _TDSAU
{
    float u_tan_avt;
    float x_tan_say;
    float x_kren_say;
}TDSAU;

typedef struct _TSetupRSS
{
    float x_kren_rus;
    float x_tan_rus;
    float x_kren_say;
    float x_tan_say;
    float  URUD;
}TSetupRSS;

typedef struct _TComOls
{
    int SV;//признак визуалиаза  работа
    int ReqOls;//запрос на обслуживание  ОЛС
    int OtvOLS;//otvet  на запрос
    int Intersect;//  признак перечения
    float EpsVert;
    float EpsHor;
    double x;
    double z;
    double y;
    double  Dal;
}TComOls;

typedef struct _Tkinematiks_aircraftConst
{
    float  ux_aircraft;         //! скорость  ветра по оси х
    float  uz_aircraft;         //! скорость  ветра по оси z
    float  beta0_aircraft;      //! Угол скольжения 0
    float  Hbar_aircraft;       //! Нулевая барометрическая высота
    float  Hrvrf_C;             //! Нулевая высота рельефа для радиовысотомера (РВ)
    float  Hrvrfmin_C;          //! Минимальная высота рельефа для РВ
    float  Hrvrfmax_C;          //! Максимальная высота рельефа для РВ
    float  alfarvrf_C;          //! Угол наклона рельефа для РВ
    float  psirvrf_C;           //! Курс рельефа для РВ
    float  Htargetrf_C;         //! Нулевая высота рельефа для наземной цели (НЦ)
    float  Htargetrfmin_C;      //! Минимальная высота рельефа для НЦ
    float  Htargetrfmax_C;      //! Максимальная высота рельефа для НЦ
    float  alfatargetrf_C;      //! Угол наклона рельефа для НЦ
    float  psitargetrf_C;       //! Курс рельефа для НЦ
    int    TUvod;               //! TУВ
    float  constTimeFloatProcess;//!!!  const time proc  reseting =63
    float  Hshasi;
}Tkinematiks_aircraftConst;

typedef struct _Tair_parametrs
{
    float H_air;        //! высота самолёта  звуковая
    float Pst_air;      //! давление  статическое
    float g_air;        //! давление  дтнамическое
    float v_dev_air;    //! скорость приборная
    float advz;         //! скорость звука
    float M;            //! величина маха
    float Pst_airPrev;  //! давление  статическое  из пред.   такта
    float g_airPrev;    //! давление  динамическое  из пред.   такта
    float v_dev_airPrev;//! скорость приборная из пред.   такта
//для  ИПОСА  из  кинематики цели
    float AxVi;         //!06.04.2012


}Tair_parametrs;

typedef  struct _Taerodynamics1
{
    float nro_aerodynamics1;
    double ro;
}Taerodynamics1;

typedef struct _TDesTarget
{
    float vc_target;
    float ny_target;
    float nz_target;
    float vxi_target;
    float vyi_target;
    float vzi_target;
    float psi_target;
    float teta_target;
    float gama_target;
    float v_target;
    float vx_target;
    float vy_target;
    float vz_target;
    //++++++++++
    double x_target;
    double y_target;
    double z_target;
    //++++++
    float  fix_relational1;
    float  fiy_relational1;
    float  fiz_relational1;
    float  di_relational;
    float  pdi_relational;
    //++++++++++
    float fix_relational;
    float fiy_relational;
    float fiz_relational;
    float l_target;
    float ki_target;
    int num_target;
    int N1Cstr;
    int Beg_num_target;
}TDesTarget;


   typedef
   struct
   _Trelational_coord
   {
      float  fix_relational;
      float  fiy_relational;
      float  fiz_relational;
      float  di_relational;
      float  pdi_relational;
   }Trelational_coord;




   typedef
   struct
   _Trelational_anglecoord
   {
      float fix_relational1;
      float fiy_relational1;
      float fiz_relational1;
   }Trelational_anglecoord;



   typedef
   struct _Tthread
   {
      unsigned Counter[MAXNUMBERTHREAD];  //cx
      unsigned DownCounter[MAXNUMBERTHREAD];

      unsigned ReadyProc[NUMBERSLAVE];
      unsigned StartProc[NUMBERSLAVE];
      unsigned ArCounter[NUMBERSLAVE][MAXNUMBERTHREAD];
      unsigned ArDownCounter[NUMBERSLAVE][MAXNUMBERTHREAD];
   }TDesThread;

   typedef struct _TCOCSCOM
   {
      float        PEREGRUZ_MAX;
      float        PEREGRUZ_MIN;
   }
   TCOCSCOM;

      typedef struct _TDSTRCOM
   {
      float ToplivoTek;
      float alfa_rud;
   }
   TDSTRCOM;


   typedef struct _TINACPIZD72
   {
      float        UFI1;      /*                     */
      float        UFI2;      /*                     */
   }
   TINACPIZD72;  /* пїЅпїЅпїЅпїЅ пїЅ пїЅпїЅ2 пїЅ 3 пїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅ пїЅ пїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ 3 пїЅ */


   typedef
   struct _TControlP
   {
      int pr_pusk;
      int pr_isxodnoe;
      int Kupr;
      int FlagCountAero;  //   pr_pusk  || pr_isxodnoe
      int Regim12;
      int LockWrite;
      int Kn_isxodnoe;
      int BufferReady;
      int IndexBuffer[NUMBERBUFFERMODEL];
      TDesThread DesThread;
      int PrUst; //признак  установки
      int UstKb; //признак установки КB в 1  из программы установка параметров
   }
   TControlP;

   typedef struct _TControlPULT
   {
       int RealPult;
      int pr_pusk;
      int pr_isxodnoe;
      int pr_ostanov;
      int Kupr;
      int FlagCountAero;  //   pr_pusk  || pr_isxodnoe
      int Regim12;
      int LockWrite;
      int Kn_isxodnoe;
      int PrUst; //признак  установки
      int UstKb; //признак установки КB в 1  из программы установка параметров

   }TControlPULT;

   typedef
   struct
   _TDesArjObject
   {
      Tkinematiks_aircraft       Kinematiks_aircraft;
      TDesTarget         DesTarget[NUMBER_TARGET];
   }TDesArjObject;


   typedef struct _TDSUOCOM
   {
      float Gasp;
   }
   TDSUOCOM;

  /* typedef
   struct _TDRVCOM
   {
      float Hg;
      float HRV;
      int VALID_HRV;
      int CheckUp;
   }
   TDRVCOM;

*/

   typedef  struct _TDSUBRKWORD
   {
      int  rk[3][8];//  для  имитатора СУО
      int  mrk[3][8];//  for  mask СУО

      int  KRastopor; //11  разрязд  из  1СС БРК
      int  Out;  //признак  выдачи
   }
   TDSUBRKWORD;



   typedef enum
   {
   prIsxodnoe=0, prPusk=1, prOstanov=2
   } UniqeNamePr_Button;

   typedef enum
   {
        ledIsxodnoe=0,
        ledPusk=1,
        ledOstanov=2,
        ledKupr=3,
        buttonIsxodnoe=4,
        buttonPusk=5,
        buttonOstanov=6,
        buttonKupr=7,
        buttonReg1_2=8,
   buttonLockWrite=9
   } UniqeNamePk_Led;


/******************************************/
   typedef
   struct
   _TINITDesArcraft
   {
      float mod_Vc;
      float PsiC;
      float Hight;
      float TettaC;
   }TINITDesArcraft;

   typedef
   struct
   _TINITDesTarget
   {
      int   Global_numTarget;//Masha
      int   TipTarget; //1-пїЅпїЅпїЅпїЅ пїЅпїЅ, 0- пїЅпїЅпїЅпїЅ пїЅпїЅ
      float Speed0Target;
      float Psi0Target;
      float Hight0Target;
      float Tetta0Target;
      float Fi0Target;
      float Dr0Target;
      int  Beg_num_target; //нач номер цели

   }
   TINITDesTarget;

 /**************************************************************************/
   typedef
   struct
   _TINITDesGRTarget
   {
      int Global_numGRTarget;//Masha
      int Tip_GRTarget;
      float Speed0_RGTarget;
      int SKS_GRTarget;
      float Psi0_GRTarget;
      float X0_GRTarget;
      float Z0_GRTarget;
      int  Beg_num_target; //нач номер цели

   }
   TINITDesGRTarget;

   typedef
   struct
   _TDesINITObject
   {
      char comment[32]; // Коментарий к варианту.
      int numberOfTarget;
      int numberOfAirTarget;
      int numberOfSTRTarget;
      TINITDesArcraft        INITDesArcraft;
      TINITDesTarget         INITDesTarget[NUMBER_TARGET];
      TINITDesGRTarget       INITDesGRTarget[NUMBER_TARGET];
   }
   TDesINITObject;
 /*************************************************************************/

   typedef
   struct
   _TDesINITall
   {
      int numberOfVariant;
      int Counter;
      TDesINITObject       DesINITObject[NUMBER_VARIANT];
   }TDesINITall;

   typedef struct  _TInitGeoGraphy
   {
      float Aust_0_geography;
      double fiust_0_geography;
      double limdaust_0_geography;
      float  DeltaM0;
      float x0_ust;
      float z0_ust;
   }
   TInitGeoGraphy;


   typedef struct
        _TCommonConst
   {
      float TAlfa;//? постоянная времени  по углу атаки нач.  исходная
      float TBeta;//? постоянная времени по углу скольжения нач.  исходная
      float ADV;//? скорость зхвука  нач.  исходная
      float Tonnaj;  //? вес
      float Knx0;  //? коф-т перегрузки
      float ny_dop;  //? перегрузка
      double fi_dv;    //
      double Vmin_C;  //? скорость минимальная самолёта
      double Hmax_C;   //? высота максимальная самолёта
      double Vmin_target; //? Скорость мин.  цели
      double Vmax_target; //?СКорость макс.  цели
      double Mat_min; //?
      float  G0;  //Empty (unloaded) aircraft weight
      float  Gc;  //Aircraft weight
      float  AlfaSM;            //Hypermanoeuvrability alfa. Angle of attack at hypermanoeuvrability
      float  AlfaBalUst;        //Ballistic angle Alfa, preset by identifier CAP
   }
   TCommonConst;




   /*typedef struct  _TComD9
   {

      int  KBR; //КБР

      int  CountD9; //счётчик

   }
   TComD9;*/




   typedef  struct _TIoKdli
   {
      int FlagSend;//стаывиттся в  1  программой  КДЛИ по выдачи
              //в сервер  после выдачи идёт обнуление

      int  RecievedFlag;  //данные приняты в буфер приёма ставится
    //  и обнуляется  программой  приёма КДЛИ
   }
   TIoKdli;

   typedef  struct _TComRegimeStend
   {
      int RegimeContr;
                       //! 0 Управ. из кабины  , реальное САУ
                       //! 1 Детерминированное
                       //! 2 Детерминированное по кругам
                       //! 3 Управ. из кабины по кругам
                       //! 4 Тестовые манёвры при уводе
      int  AvtTiaga; //!  0 РУД
                     //1   Автомат тяги

      int SauIdelPilot;//!Продольный канал ид.  пилота
                       //! САУ ид.  пилота +  Автопилот
                       //!   Отключено

      int DetAerod1;//! 0 Аэродинамика 1
                    //  1 Детерминмрованная
                    //  2 Отключено

      int Serpent;//! 0  Прямолинейное
                  //! 1  Змейкой

     int ManevrTaget; //!  1  признак манёвра  целей

   }
   TComRegimeStend;

   typedef  struct
   _TDesCommonObjects
   {
      int indexNumberOfTarget;
      int  airtarget_Q;        // пїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅ
      TDesArjObject DesArjObject[NUMBERBUFFERMODEL];
      int NVarIsh;  //  номер  исходного  варианта  кинематики
      int FlagNewNVarIsh; //флаг  нового  исходного  номера  варианта
      int targetSTR_num;//Masha
      int ComUst;  //команда установки
      TComRegimeStend   ComRegimeStend;
   }
   TDesCommonObjects;



//Для  визуализации   на ПК


   typedef struct
   _TDSTRUCTVISULISATION
   {
      TCommonConst  CommonConst;
      int Flag;    /*  0 */
      unsigned int Counter;
      int      NumberTarget;
      TDesArjObject     DesArjObject;
      Tgeography_Earth    Geography_Earth;
      Tkinematiks_aircraftConst    Kinematiks_aircraftConst;
      Tair_parametrs  Air_parametrs;
      TCOCSCOM  COCSCOM;
      TDSUOCOM  DSUOCOM;
      int  airtarget_Q;       //!кол-во  воздушных  целей
      int  targetSTR_num; //!номер строя
      int NVarIsh;  //!  номер  исходного  варианта  кинематики
      int FlagNewNVarIsh; //!флаг  нового  исходного  номера  варианта
      int ComUst; //!команда   установки     с программы  взмд 1  с пульта Программы ВЗМД;
      TComRegimeStend   ComRegimeStend;
      int N_BegFromPult;//
      int N_EndFromPult;//
      int TotalNumberVariants;//
      TControlPULT controlPULT;
      float dtHotn; //DSVC.dtHotn   25.08.10     from  SVC
      int   NumberRealization; //  12.11.10
      int restartModel;//команда перезапуска модели
}TDSTRUCTVISULISATION;
#pragma pack(pop)
}
class cl_DataForVxWorksT50Bins : public GenericData
{
public:
    cl_DataForVxWorksT50Bins(void);

    //! основной массив для хранения данных(программа всегда берет данные отсюда)
    T50BINS::TDSTRUCTVISULISATION bufferData;

    //! промежуточный массив для хранения принятых данных()
    T50BINS::TDSTRUCTVISULISATION middleBufferData;

    //! Указатель на буффер
    //T50BINS::TDSTRUCTVISULISATION* ptrBufData;

    //! создать новый объект передачи
    virtual void newTransmitObject();

    //! кол-во целей
    int numTargets;

    //! нажатие на кнопку СТОП
    virtual void pressButtonStop()
    {
        bufferData.controlPULT.pr_ostanov=1;
        bufferData.controlPULT.pr_isxodnoe=0;
        bufferData.controlPULT.pr_pusk=0;

        /*middleBufferData.controlPULT.pr_ostanov=1;
        middleBufferData.controlPULT.pr_isxodnoe=0;
        middleBufferData.controlPULT.pr_pusk=0;*/
    }
    //! нажатие на кнопку СТАРТ
    virtual void pressButtonStart()
    {
        bufferData.controlPULT.pr_ostanov=0;
        bufferData.controlPULT.pr_isxodnoe=0;
        bufferData.controlPULT.pr_pusk=1;

        /*middleBufferData.controlPULT.pr_ostanov=0;
        middleBufferData.controlPULT.pr_isxodnoe=0;
        middleBufferData.controlPULT.pr_pusk=1;*/
    }
    //! нажатие на кнопку ИСХОДНОЕ
    virtual void pressButtonRestart()
    {
        bufferData.controlPULT.pr_ostanov=0;
        bufferData.controlPULT.pr_isxodnoe=1;
        bufferData.controlPULT.pr_pusk=0;

        /*middleBufferData.controlPULT.pr_ostanov=0;
        middleBufferData.controlPULT.pr_isxodnoe=0;
        middleBufferData.controlPULT.pr_pusk=1;*/
    }
    //! нажатие на кнопку "Перезапуск модели"
    virtual void pressButtonRestartModel(bool value)
    {
        if(value==true)
            bufferData.restartModel=1;
        else
            bufferData.restartModel=0;

       // middleBufferData.restartModel=bufferData.restartModel;

    }
    //! получить идентфикатор варианта
    virtual unsigned uidVar()
    {
        return 0;
    }
    //! признак "Включения вирт. пульта"
    virtual int getVirtualPult()
    {
        bufferData.controlPULT.RealPult=middleBufferData.controlPULT.RealPult;
        return bufferData.controlPULT.RealPult;
    }

    virtual void pressButtonOnVirtualPult(int r)
    {
        bufferData.controlPULT.RealPult=r;
    }
    virtual int getKupr()
    {
        bufferData.controlPULT.Kupr=middleBufferData.controlPULT.Kupr;
        return bufferData.controlPULT.Kupr;
    }

    virtual void pressButtonKupr(int r)
    {
        bufferData.controlPULT.Kupr=r;
    }
    virtual int getRegim12()
    {
        bufferData.controlPULT.Regim12=middleBufferData.controlPULT.Regim12;
        return middleBufferData.controlPULT.Regim12;
    }

    virtual void pressButtonRegim12(int r)
    {
        bufferData.controlPULT.Regim12=r;
    }
    virtual int getLockWrite()
    {
        bufferData.controlPULT.LockWrite=middleBufferData.controlPULT.LockWrite;
        return middleBufferData.controlPULT.LockWrite;
    }

    virtual void pressButtonLockWrite(int r)
    {
        bufferData.controlPULT.LockWrite=r;
    }

    virtual void setControlRegime(ControlReg);

    virtual void setAvtoTiaga(bool);
    virtual bool avtoTiaga();

    virtual void setSauIdelPilot(int);
    virtual int sauIdelPilot();

    virtual void setDetAerod1(int);
    virtual int detAerod1();

    virtual void setSerpent(bool);
    virtual bool serpent();

    virtual void setManevrTarget(bool);
    virtual bool manevrTarget();

    virtual void setHrv0(double);
    virtual void setHrvmin(double);
    virtual void setHrvmax(double);
    virtual void setKursRv(double);
    virtual void alfaSM(double);
    ///////////////////////////////////////////
    virtual void Vminair(double);
    virtual void Hmaxair(double);

    /*virtual void setChildProgram()
    {
        transmit->changePort();
        transmit->enableRecive(true);
    }*/

    //! Признак установки
    virtual void setComUst(bool f)
    {
        if(f==true)
            bufferData.ComUst=1;
        else
            bufferData.ComUst=0;

        //middleBufferData.ComUst=bufferData.ComUst;
    }
    virtual int comUst()
    {
        bufferData.ComUst=middleBufferData.ComUst;
        return bufferData.ComUst;
    }
    //! обновление режима
    virtual void refreshRegime();
    //! отправка данных
    virtual void sendData();
    //! нажатие признака "Новый вариант"
    virtual void setPrNewVariant(bool f)
    {
        if(f==true) bufferData.FlagNewNVarIsh=1;
        else bufferData.FlagNewNVarIsh=0;

        //qDebug("===========PrNewVariant=%d\n",bufferData.FlagNewNVarIsh);
        //middleBufferData.FlagNewNVarIsh=bufferData.FlagNewNVarIsh;
    }
    virtual bool prNewVariant()
    {
        bufferData.FlagNewNVarIsh=middleBufferData.FlagNewNVarIsh;
        return bufferData.FlagNewNVarIsh;
    }

    /*virtual void setPrNewVariant(bool f)
    {
        if(f==true)  bufferData.FlagNewNVarIsh=1;
        else bufferData.FlagNewNVarIsh=0;
    }*/
    virtual void setNumVariant(int var)
    {
       bufferData.NVarIsh=var;
       // middleBufferData.NVarIsh=var;
    } 
    virtual int  numVariant()
    {
        bufferData.NVarIsh=middleBufferData.NVarIsh;
        return bufferData.NVarIsh;
    }

    virtual unsigned int counter();

    //! кол-во целей
    virtual int targetNumbers();
    //! кол-во возжушных целей
    virtual int targetAirNum();

    //!Создать окно с атмосферными параметрами и геометрией
    virtual void createFormAtmGeo(void);
    virtual void refreshFormAtmGeo(void);

    //!Создать окно с кинематическими параметрами
    virtual void createFormKinAircraft(void);
    virtual void refreshFormKinAircraft(void);

    //!создать окно с целями
    virtual void createFormTargets(void);
    virtual void refreshFormTargets(void);

    //!создать окно с константами
    virtual void createFormConst(void);
    virtual void refreshFormConst(void);



    //! создат окно с общими константами
    virtual void createFormCommonConst(void);
    virtual void refreshFormCommonConst(void);
    virtual void callSlotResived(char* ptr);

    //!Обновить данные
    virtual void refreshData();
    virtual void setData(char*);

    //! для визуализации
    virtual double t()
    {
        return middleBufferData.DesArjObject.Kinematiks_aircraft.t_pol_aircraft;
    }
    virtual double gamac()
    {
        return middleBufferData.DesArjObject.Kinematiks_aircraft.gamac_aircraft;
    }
    virtual double psic()
    {
        return middleBufferData.DesArjObject.Kinematiks_aircraft.psic_aircraft;
    }
    virtual double tetac()
    {
        return middleBufferData.DesArjObject.Kinematiks_aircraft.tetac_aircraft;
    }
    //угол наклона траектории
    virtual double untc()
    {
        return middleBufferData.DesArjObject.Kinematiks_aircraft.tetac_aircraft;
    }
    virtual float Aust()
    {
        return middleBufferData.Geography_Earth.Au_geography;
    }
    virtual double alfac()
    {
        return middleBufferData.DesArjObject.Kinematiks_aircraft.alfa_aircraft;
    }
    virtual double betac()
    {
        return middleBufferData.DesArjObject.Kinematiks_aircraft.beta_aircraft;
    }
    virtual double omega_xc()
    {
        return middleBufferData.DesArjObject.Kinematiks_aircraft.omcx_aircraft;
    }
    virtual double omega_yc()
    {
        return middleBufferData.DesArjObject.Kinematiks_aircraft.omcy_aircraft;
    }
    virtual double omega_zc()
    {
        return middleBufferData.DesArjObject.Kinematiks_aircraft.omcz_aircraft;
    }

    virtual void setGamac(double value)
    {
        //middleBufferData.DesArjObject.Kinematiks_aircraft.gamac_aircraft=value;
        bufferData.DesArjObject.Kinematiks_aircraft.gamac_aircraft=value;
    }
    virtual void setPsic(double value)
    {
        //middleBufferData.DesArjObject.Kinematiks_aircraft.psic_aircraft=value;
        bufferData.DesArjObject.Kinematiks_aircraft.psic_aircraft=value;
    }
    virtual void setTetac(double value)
    {
        //middleBufferData.DesArjObject.Kinematiks_aircraft.tetac_aircraft=value;
        bufferData.DesArjObject.Kinematiks_aircraft.tetac_aircraft=value;
    }
    virtual void setUntc(double value)
    {
        //middleBufferData.DesArjObject.Kinematiks_aircraft.teta_aircraft=value;
        bufferData.DesArjObject.Kinematiks_aircraft.teta_aircraft=value;
    }
    virtual void setAlfac(double value)
    {
        //middleBufferData.DesArjObject.Kinematiks_aircraft.alfa_aircraft=value;
        bufferData.DesArjObject.Kinematiks_aircraft.alfa_aircraft=value;
    }
    virtual void setBetac(double value)
    {
        //middleBufferData.DesArjObject.Kinematiks_aircraft.beta_aircraft=value;
        bufferData.DesArjObject.Kinematiks_aircraft.beta_aircraft=value;
    }
    virtual void setOmega_xc(double value)
    {
        //middleBufferData.DesArjObject.Kinematiks_aircraft.omcx_aircraft=value;
        bufferData.DesArjObject.Kinematiks_aircraft.omcx_aircraft=value;
    }
    virtual void setOmega_yc(double value)
    {
        //middleBufferData.DesArjObject.Kinematiks_aircraft.omcy_aircraft=value;
        bufferData.DesArjObject.Kinematiks_aircraft.omcy_aircraft=value;
    }
    virtual void setOmega_zc(double value)
    {
        //middleBufferData.DesArjObject.Kinematiks_aircraft.omcz_aircraft=value;
        bufferData.DesArjObject.Kinematiks_aircraft.omcz_aircraft=value;
    }
    virtual double vc()
    {
        return middleBufferData.DesArjObject.Kinematiks_aircraft.vc_aircraft;       
    }
    virtual double v_xc()
    {
        return middleBufferData.DesArjObject.Kinematiks_aircraft.vcx_aircraft;
    }
    virtual double v_yc()
    {
        return middleBufferData.DesArjObject.Kinematiks_aircraft.vcy_aircraft;
    }
    virtual double v_zc()
    {
        return middleBufferData.DesArjObject.Kinematiks_aircraft.vcz_aircraft;
    }
    virtual double n_xc()
    {
        return middleBufferData.DesArjObject.Kinematiks_aircraft.ncx_aircraft;
    }
    virtual double n_yc()
    {
        return middleBufferData.DesArjObject.Kinematiks_aircraft.ncy_aircraft;
    }
    virtual double n_zc()
    {
        return middleBufferData.DesArjObject.Kinematiks_aircraft.ncz_aircraft;
    }
    virtual double maxac()
    {
        return middleBufferData.DesArjObject.Kinematiks_aircraft.M_aircraft;
    }
    virtual double mc()
    {
        //return middleBufferData.DesArjObject.Kinematiks_aircraft.;
        return -1;
    }
    virtual double latc()
    {
        return middleBufferData.Geography_Earth.fit_geography;

    }
    virtual double lonc()
    {
        return middleBufferData.Geography_Earth.limdat_geography;
    }
    virtual double wind_xc()
    {
        return middleBufferData.Kinematiks_aircraftConst.ux_aircraft;
    }
    virtual double wind_zc()
    {
        return middleBufferData.Kinematiks_aircraftConst.uz_aircraft;
    }
    virtual void setVc(double value)
    {
        //middleBufferData.DesArjObject.Kinematiks_aircraft.vc_aircraft=value;
        bufferData.DesArjObject.Kinematiks_aircraft.vc_aircraft=value;
    }
    virtual void setN_xc(double value)
    {
        //middleBufferData.DesArjObject.Kinematiks_aircraft.ncx_aircraft=value;
        bufferData.DesArjObject.Kinematiks_aircraft.ncx_aircraft=value;
    }
    virtual void setN_yc(double value)
    {
        //middleBufferData.DesArjObject.Kinematiks_aircraft.ncy_aircraft=value;
        bufferData.DesArjObject.Kinematiks_aircraft.ncy_aircraft=value;
    }
    virtual void setN_zc(double value)
    {
        //middleBufferData.DesArjObject.Kinematiks_aircraft.ncz_aircraft=value;
        bufferData.DesArjObject.Kinematiks_aircraft.ncz_aircraft=value;
    }
    virtual void setMaxac(double value)
    {
        //middleBufferData.DesArjObject.Kinematiks_aircraft.M_aircraft=value;
        bufferData.DesArjObject.Kinematiks_aircraft.M_aircraft=value;
    }
    virtual void setWind_xc(double value)
    {
        //middleBufferData.Kinematiks_aircraftConst.ux_aircraft=value;
        bufferData.Kinematiks_aircraftConst.ux_aircraft=value;
    }
    virtual void setWind_zc(double value)
    {
        //middleBufferData.Kinematiks_aircraftConst.uz_aircraft=value;
        bufferData.Kinematiks_aircraftConst.uz_aircraft=value;
    }
    virtual void setYc(double value)
    {
        //middleBufferData.DesArjObject.Kinematiks_aircraft.yc_aircraft=value;
        bufferData.DesArjObject.Kinematiks_aircraft.yc_aircraft=value;
    }

    virtual double xc(){return middleBufferData.DesArjObject.Kinematiks_aircraft.xc_aircraft;}
    virtual double yc(){return middleBufferData.DesArjObject.Kinematiks_aircraft.yc_aircraft;}
    virtual double zc(){return middleBufferData.DesArjObject.Kinematiks_aircraft.zc_aircraft;}

    virtual double xTarget(int iTarget){return middleBufferData.DesArjObject.DesTarget[iTarget].x_target;}
    virtual double yTarget(int iTarget){return middleBufferData.DesArjObject.DesTarget[iTarget].y_target;}
    virtual double zTarget(int iTarget){return middleBufferData.DesArjObject.DesTarget[iTarget].z_target;}

    virtual double targetGama(int iTarget){return middleBufferData.DesArjObject.DesTarget[iTarget].gama_target;}
    virtual double targetTeta(int iTarget){return middleBufferData.DesArjObject.DesTarget[iTarget].teta_target;}
    virtual double targetPsi(int iTarget){return middleBufferData.DesArjObject.DesTarget[iTarget].psi_target;}
};


#endif // CL_DATAFORWORKST50BINS_H
