/*
 * cl_DataForVxWorks.h
 *
 *  Created on: 13.04.2009
 *      Author: vxuser
 */

#ifndef CL_DATAFORVXWORKS_SU35_1_H_
#define CL_DATAFORVXWORKS_SU35_1_H_

//#ifdef Q_WS_WIN
/*
################################################################
#                                                              #
#    ####      ##      ##            ######      ############  #
#  ##    ##    ##      ##          ##      ##    ##            #
#  ##          ##      ##                  ##    ##            #
#    ##        ##      ##              ####      ######        #
#      ##      ##      ##  ######          ##          ##      #
#        ##    ##      ##          ##      ##          ##      #
#  ##    ##    ##      ##          ##      ##  ##      ##      #
#    ####        ######              ######      ######        #
#                                                              #
################################################################
*/



#include "GenericData.h"
#include "../globalFunc/gl_func.h"

namespace Su35_1
{
#define MAXNUMBERTHREAD  6
#define NUMBERSLAVE  3
#define NUMBER_TARGET 32  //  !!!!!!!!!!!!!!!!!!!!
//#define NUMBER_OF_PARAM_TARGER 24
#define NUMBER_VARIANT 32
#define NUMBER_TVACP   8

#define NO_GTK   1

#pragma pack(push,4)

   typedef   struct
   _Tkinematiks_aircraft
   {
      float	nxt_aircraft;
      float prs_aircraft;
      float niy1_aircraft;
      float niy2_aircraft;
      float pniy1_aircraft;
      float pniy2_aircraft;
      float nz_aircraft;
      float pnz_aircraft;
      float omvx1_aircraft;
      float  omvx2_aircraft;
      float  Knx_aircraft;
      float  Talfa_aircraft;
      float alfa_bal_aircraft;
      float  Tbeta_aircraft;
      float  nydop_aircraft;
      float  psi_aircraft;
      float  teta_aircraft;
      float  gamav_aircraft;
      float  psic_aircraft;
      float tetac_aircraft;
      float gamac_aircraft;
      float alfa_aircraft;
      float  beta_aircraft;
      float omcx_aircraft;
      float  omcy_aircraft;
      float  omcz_aircraft;
      float  ncx_aircraft;
      float  ncy_aircraft;
      float  ncz_aircraft;
      float  vc_aircraft;
      float vcx_aircraft;
      float  vcy_aircraft;
      float  vcz_aircraft;
      float  M_aircraft;
      double xc_aircraft;
      double yc_aircraft;
      double zc_aircraft;
      float nypol_aircraft;
      double   t_pol_aircraft;
      float   G_engine;
      float v_aircraft;              //пїЅпїЅпїЅпїЅпїЅпїЅ
      float alfaf_aircraft;           //пїЅпїЅпїЅпїЅпїЅпїЅ
      float nypr_aircraft;  //14.09.07
      float nzpr_aircraft;////14.09.07
 float nvy_aircraft;
   }
   Tkinematiks_aircraft;

/*
typedef
 struct
  _Tgeography_EarthCommon
{
float limdat_geography;
float Au_geography;
float DeltaMSkl;
float fit_geography;
float  DeltaM0;
float R_Earth_geography;
}
Tgeography_EarthCommon;
*/

   typedef
   struct
   _Tgeography_Earth
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
      float  DeltaMSkl;
      float  DeltaM0;
  int   Pr10G[2];    //�������  10 ��  ��������� ������� �
 int   CmGK;     //����� ��������������� ���������
   }Tgeography_Earth;








   typedef struct _TDSDU
   {
      int  pr_signal_from_sdy;
      short  int  U_tan_avt;
      short int  U_kren_avt;  //  внесено 25.01.06
   }
   TDSDU;

   typedef struct _TDRUD
   {
      float	URUD;
      int  urud_zap;
      int  urud_zap_in;
   }
   TDRUD;

   typedef struct _TDRUS
   {
      int	u_tan_zap;
      int	u_kren_zap;
      int	u_tan_zap_in;
      int	u_kren_zap_in;
      int  pr_isxodnoe_rus;
      float	x_kren_rus;
      float x_tan_rus;
      int j;
   }
   TDRUS;

   typedef struct _TDPED
   {
      int u_ped_zap_in;
      int u_ped_zap;
      float x_ped;
   }
   TDPED;


   typedef struct _TDSAU
   {
      float u_tan_avt;
      float x_tan_say;
      float x_kren_say;
   }
   TDSAU;


   typedef struct _TSetupRSS
   {
      float x_kren_rus;
      float x_tan_rus;
      float x_kren_say;
      float x_tan_say;
      float  URUD;
   }
   TSetupRSS;//ХУФБОПЧПЮОЩЕ  ЛПОУФБОФЩ � ТЙ ЙУИПДОПН

   typedef   struct _TComOls
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
   }
   TComOls;

/*
typedef   struct _TComRVVis
{
int AnsH;//отв H
float HLand;//высота ландшафта
int SV;
}
TComRVVis;  //поместить в общую  область  и сделать  указател  высотомер
*/

   typedef
   struct
   _Tkinematiks_aircraftConst
   {
      float  ux_aircraft; //? скорость  ветра по оси х
      float  uz_aircraft;//? скорость  ветра по оси z
      float  beta0_aircraft;//? Угол скольжения 0
      float  Hbar_aircraft; //? Нулевая барометрическая высота
      float  Hrvrf_C;//? Нулевая высота рельефа для радиовысотомера (� В)
      float  Hrvrfmin_C;//? Минимальная высота рельефа для � В
      float  Hrvrfmax_C;//? Максимальная высота рельефа для � В
      float  alfarvrf_C;//? Угол наклона рельефа для � В
      float  psirvrf_C;//? � урс рельефа для � В
      float  Htargetrf_C;//? Нулевая высота рельефа для наземной цели (НЦ)
      float  Htargetrfmin_C;//? Минимальная высота рельефа для НЦ
      float  Htargetrfmax_C;//? Максимальная высота рельефа для НЦ
      float  alfatargetrf_C;//? Угол наклона рельефа для НЦ
      float  psitargetrf_C;//? � урс рельефа для НЦ
      int    TUvod;  //? TУВ
      float  AlfaSM; //? признак сверхманеврнности
      float  AlfaBalUst;//8.11.07


   }Tkinematiks_aircraftConst;





   typedef
   struct
   _Tair_parametrs
   {
      float H_air; //?высота самолёта  звуковая
      float Pst_air; //?давление  статическое
      float  g_air; //?давление  дтнамическое
      float v_dev_air;//?  скорость приборная
      float advz;//? /* скорость звука*/
      float  M; //?величина маха
      float Pst_airPrev; //?давление  статическое  из пред.   такта
      float  g_airPrev; //?давление  динамическое  из пред.   такта
      float v_dev_airPrev;//?  скорость приборная из пред.   такта
      float v_dev_air_dv_dt;//производная
      float MPrev;
      float M_dm_dt;


   }Tair_parametrs;

   typedef
   struct
   _Taerodynamics1
   {
      float nro_aerodynamics1;
  double ro;
   }Taerodynamics1;


   typedef
   struct
   _TDesTarget
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
      float ki_target;    //пїЅпїЅпїЅпїЅпїЅпїЅ
      int num_target;//Masha
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
      int IndexBuffer[4];
      TDesThread DesThread;
      int PrUst; //признак  установки
      int UstKb; //признак установки � B в 1  из программы установка параметров
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
      int UstKb; //признак установки � B в 1  из программы установка параметров

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

   typedef
   struct _TDRVCOM
   {
      float Hg;/* пїЅпїЅпїЅ   пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ*/
      float HRV;/* пїЅпїЅпїЅ   пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ*/
      int VALID_HRV;
      int CheckUp;
   }
   TDRVCOM;



   typedef  struct _TDSUBRKWORD
   {
      int  rk[3][8];//  для  имитатора СУО
      int  mrk[3][8];//  for  mask СУО

      int  KRastopor; //11  разрязд  из  1СС Б� � 
      int  Out;  //признак  выдачи
   }
   TDSUBRKWORD;



   typedef enum
   {
   prIsxodnoe=0, prPusk=1, prOstanov=2
   } UniqeNamePr_Button;

   typedef enum
   {
   ledIsxodnoe=0, ledPusk=1, ledOstanov=2,ledKupr=3,
   buttonIsxodnoe=4, buttonPusk=5, buttonOstanov=6, buttonKupr=7,buttonReg1_2=8,
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
int  Beg_num_target; //��� ����� ����
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
int  Beg_num_target; //��� ����� ����

   }
   TINITDesGRTarget;

   typedef
   struct
   _TDesINITObject
   {
      char comment[32]; // ���������� � ��������.
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
      double Vmax_target; //?С� орость макс.  цели
      double Mat_min; //?
      float  G0;  //? ��� ���������  �������
      float  Gc;  //??  ���  �������
 float  AlfaSM;            //Hypermanoeuvrability alfa. Angle of attack at hypermanoeuvrability
      float  AlfaBalUst;        //Ballistic angle Alfa, preset by identifier CAP
   }
   TCommonConst;




   typedef struct  _TComD9
   {

      int  KBR;

      int  CountD9;

   }
   TComD9;




   typedef  struct _TIoKdli
   {
      int FlagSend;

      int  RecievedFlag;
   }
   TIoKdli;

   typedef  struct _TComRegimeStend
   {
      int RegimeContr;

      int  AvtTiaga;

      int SauIdelPilot;
      int DetAerod1;
      int Serpent;

     int ManevrTaget;

   }
   TComRegimeStend;

   typedef  struct
   _TDesCommonObjects
   {
      int indexNumberOfTarget;
      int  airtarget_Q;
      TDesArjObject DesArjObject[4];
      int NVarIsh;
      int FlagNewNVarIsh;
      int targetSTR_num;
      int ComUst;
      TComRegimeStend   ComRegimeStend;
   }
   TDesCommonObjects;


   typedef struct _TVirtualPULT
   {
       int slider_realPult;

       int button_start;
       int button_stop;
       int button_restart;

       int slider_Kupr;
       int slider_Regime12;
       int slider_LockWrite;

       int PrUst;
       int UstKb;

   }TVirtualPULT;




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
      int  airtarget_Q;
      int  targetSTR_num;
      int NVarIsh;
      int FlagNewNVarIsh;
      int ComUst;
      TComRegimeStend   ComRegimeStend;
      int N_BegFromPult;//
      int N_EndFromPult;//
      int TotalNumberVariants;//
      TControlPULT controlPULT;
      float dtHotn; //DSVC.dtHotn   25.08.10     from  SVC
      int   NumberRealization; //  12.11.10
      int restartModel;
   }
   TDSTRUCTVISULISATION;
   #pragma pack(pop)
}
class cl_DataForVxWorks_Su35_1 : public GenericData
{
public:

    cl_DataForVxWorks_Su35_1(void);


    Su35_1::TDSTRUCTVISULISATION bufferData;


    Su35_1::TDSTRUCTVISULISATION middleBufferData;


    Su35_1::TDSTRUCTVISULISATION* ptrBufData;

    virtual void newTransmitObject();

    int numTargets;

    virtual void pressButtonStop()
    {
        bufferData.controlPULT.pr_ostanov=1;
        bufferData.controlPULT.pr_isxodnoe=0;
        bufferData.controlPULT.pr_pusk=0;

        /*middleBufferData.controlPULT.pr_ostanov=1;
        middleBufferData.controlPULT.pr_isxodnoe=0;
        middleBufferData.controlPULT.pr_pusk=0;*/
    }
    virtual void pressButtonStart()
    {
        bufferData.controlPULT.pr_ostanov=0;
        bufferData.controlPULT.pr_isxodnoe=0;
        bufferData.controlPULT.pr_pusk=1;

        /*middleBufferData.controlPULT.pr_ostanov=0;
        middleBufferData.controlPULT.pr_isxodnoe=0;
        middleBufferData.controlPULT.pr_pusk=1;*/
    }
    virtual void pressButtonRestart()
    {
        bufferData.controlPULT.pr_ostanov=0;
        bufferData.controlPULT.pr_isxodnoe=1;
        bufferData.controlPULT.pr_pusk=0;

        /*middleBufferData.controlPULT.pr_ostanov=0;
        middleBufferData.controlPULT.pr_isxodnoe=0;
        middleBufferData.controlPULT.pr_pusk=1;*/
    }
    virtual void pressButtonRestartModel(bool value)
    {
        if(value==true)   bufferData.restartModel=1;
        else bufferData.restartModel=0;

        middleBufferData.restartModel=bufferData.restartModel;
    }
    virtual unsigned uidVar()
    {
        return 0;
    }

    virtual int getVirtualPult()
    {
        return middleBufferData.controlPULT.RealPult;
    }

    virtual void pressButtonOnVirtualPult(int r)
    {
        bufferData.controlPULT.RealPult=r;
    }
    virtual int getKupr()
    {
        return middleBufferData.controlPULT.Kupr;
    }

    virtual void pressButtonKupr(int r)
    {
        bufferData.controlPULT.Kupr=r;
    }
    virtual int getRegim12()
    {
        return middleBufferData.controlPULT.Regim12;
    }

    virtual void pressButtonRegim12(int r)
    {
        bufferData.controlPULT.Regim12=r;
    }
    virtual int getLockWrite()
    {
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
    virtual void Vminair(double);
    virtual void Hmaxair(double);

    /*virtual void setChildProgram()
    {
        transmit->changePort();
        transmit->enableRecive(true);
    }*/


    virtual void setComUst(bool f)
    {
        if(f==true)bufferData.ComUst=1;
        else bufferData.ComUst=0;

        middleBufferData.ComUst=bufferData.ComUst;
    }
    virtual int comUst()
    {
        return bufferData.ComUst;
    }

    virtual void refreshRegime();
    virtual void sendData();

    virtual void setPrNewVariant(bool f)
    {
        if(f==true) bufferData.FlagNewNVarIsh=1;
        else bufferData.FlagNewNVarIsh=0;

        qDebug("===========PrNewVariant=%d\n",bufferData.FlagNewNVarIsh);
        middleBufferData.FlagNewNVarIsh=bufferData.FlagNewNVarIsh;
    }
    virtual bool prNewVariant()
    {
        return middleBufferData.FlagNewNVarIsh;
    }

    /*virtual void setPrNewVariant(bool f)
    {
        if(f==true)  bufferData.FlagNewNVarIsh=1;
        else bufferData.FlagNewNVarIsh=0;
    }*/
    virtual void setNumVariant(int var)
    {
        bufferData.NVarIsh=var;
        middleBufferData.NVarIsh=var;
    } 
    virtual int  numVariant()           {return middleBufferData.NVarIsh;}

    virtual unsigned int counter();


    virtual int targetNumbers();
    //! ���-�� ��������� �����
    virtual int targetAirNum();

    virtual void createFormAtmGeo(void);
    virtual void refreshFormAtmGeo(void);


    virtual void createFormKinAircraft(void);
    virtual void refreshFormKinAircraft(void);


    virtual void createFormTargets(void);
    virtual void refreshFormTargets(void);


    virtual void createFormConst(void);
    virtual void refreshFormConst(void);


    virtual void createFormCommonConst(void);
    virtual void refreshFormCommonConst(void);
    virtual void callSlotResived(char* ptr);

    virtual void refreshData();
    virtual void setData(char*);

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
        middleBufferData.DesArjObject.Kinematiks_aircraft.gamac_aircraft=value;
        bufferData.DesArjObject.Kinematiks_aircraft.gamac_aircraft=value;
    }
    virtual void setPsic(double value)
    {
        middleBufferData.DesArjObject.Kinematiks_aircraft.psic_aircraft=value;
        bufferData.DesArjObject.Kinematiks_aircraft.psic_aircraft=value;
    }
    virtual void setTetac(double value)
    {
        middleBufferData.DesArjObject.Kinematiks_aircraft.tetac_aircraft=value;
        bufferData.DesArjObject.Kinematiks_aircraft.tetac_aircraft=value;
    }
    virtual void setUntc(double value)
    {
        middleBufferData.DesArjObject.Kinematiks_aircraft.teta_aircraft=value;
        bufferData.DesArjObject.Kinematiks_aircraft.teta_aircraft=value;
    }
    virtual void setAlfac(double value)
    {
        middleBufferData.DesArjObject.Kinematiks_aircraft.alfa_aircraft=value;
        bufferData.DesArjObject.Kinematiks_aircraft.alfa_aircraft=value;
    }
    virtual void setBetac(double value)
    {
        middleBufferData.DesArjObject.Kinematiks_aircraft.beta_aircraft=value;
        bufferData.DesArjObject.Kinematiks_aircraft.beta_aircraft=value;
    }
    virtual void setOmega_xc(double value)
    {
        middleBufferData.DesArjObject.Kinematiks_aircraft.omcx_aircraft=value;
        bufferData.DesArjObject.Kinematiks_aircraft.omcx_aircraft=value;
    }
    virtual void setOmega_yc(double value)
    {
        middleBufferData.DesArjObject.Kinematiks_aircraft.omcy_aircraft=value;
        bufferData.DesArjObject.Kinematiks_aircraft.omcy_aircraft=value;
    }
    virtual void setOmega_zc(double value)
    {
        middleBufferData.DesArjObject.Kinematiks_aircraft.omcz_aircraft=value;
        bufferData.DesArjObject.Kinematiks_aircraft.omcz_aircraft=value;
    }
    virtual double vc()
    {
        return middleBufferData.DesArjObject.Kinematiks_aircraft.vc_aircraft;
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
        middleBufferData.DesArjObject.Kinematiks_aircraft.vc_aircraft=value;
        bufferData.DesArjObject.Kinematiks_aircraft.vc_aircraft=value;
    }
    virtual void setN_xc(double value)
    {
        middleBufferData.DesArjObject.Kinematiks_aircraft.ncx_aircraft=value;
        bufferData.DesArjObject.Kinematiks_aircraft.ncx_aircraft=value;
    }
    virtual void setN_yc(double value)
    {
        middleBufferData.DesArjObject.Kinematiks_aircraft.ncy_aircraft=value;
        bufferData.DesArjObject.Kinematiks_aircraft.ncy_aircraft=value;
    }
    virtual void setN_zc(double value)
    {
        middleBufferData.DesArjObject.Kinematiks_aircraft.ncz_aircraft=value;
        bufferData.DesArjObject.Kinematiks_aircraft.ncz_aircraft=value;
    }
    virtual void setMaxac(double value)
    {
        middleBufferData.DesArjObject.Kinematiks_aircraft.M_aircraft=value;
        bufferData.DesArjObject.Kinematiks_aircraft.M_aircraft=value;
    }
    virtual void setWind_xc(double value)
    {
        middleBufferData.Kinematiks_aircraftConst.ux_aircraft=value;
        bufferData.Kinematiks_aircraftConst.ux_aircraft=value;
    }
    virtual void setWind_zc(double value)
    {
        middleBufferData.Kinematiks_aircraftConst.uz_aircraft=value;
        bufferData.Kinematiks_aircraftConst.uz_aircraft=value;
    }
    virtual void setYc(double value)
    {
        middleBufferData.DesArjObject.Kinematiks_aircraft.yc_aircraft=value;
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
//#endif
#endif /* CL_DATAFORVXWORKS_SU35_H_ */
