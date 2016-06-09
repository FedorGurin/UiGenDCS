/*
 * cl_DataForVxWorks.h
 *
 *  Created on: 13.04.2009
 *      Author: vxuser
 */

#ifndef CL_DATAFORVXWORKS_SU30SM_H_
#define CL_DATAFORVXWORKS_SU30SM_H_

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

namespace SU30SM
{
#define MAXNUMBERTHREAD     6
#define NUMBERSLAVE         3
#define NUMBER_TARGET       32
#define NUMBER_VARIANT      32
#define NUMBER_TVACP        8
#pragma pack(push,4)
typedef   struct
_Tkinematiks_aircraft
{
   float	nxt_aircraft;     //   Engine thrust g-load
   float prs_aircraft;         //   Identifier of full (loaded) aircraft
   float niy1_aircraft;        //   G-load of the first longitudinal passage
   float niy2_aircraft;        //   G-load of the second longitudinal passage
   float pniy1_aircraft;       //   Rate of change of the first longitudinal passage g-load
   float pniy2_aircraft;       //   Rate of change of the second longitudinal passage g-load
   float nz_aircraft;          //    G-load of aircraft control cross passage
   float pnz_aircraft;         //    Rate of change of the aircraft control cross passage g-load
   float omvx1_aircraft;       //    Angle speed of the first aircraft control side passage
   float  omvx2_aircraft;      //    Angle speed of the second aircraft control side passage
   float  Knx_aircraft;        //    Aerodynamic drag factor
   float  Talfa_aircraft;      //    Aerodynamic response time of attack angle
   float alfa_bal_aircraft;    //    Attack angle in straight and level flight
   float  Tbeta_aircraft;      //    Aerodynamic response time of slip angle
   float  nydop_aircraft;      //    Allowable g-load
   float  psi_aircraft;        //    Course angle
   float  teta_aircraft;       //    Flight path angle
   float  gamav_aircraft;      //    Aircraft roll in vehicle state coordinates
   float  psic_aircraft;       //    Aircraft heading
   float tetac_aircraft;       //    Aircraft pitch
   float gamac_aircraft;       //    Aircraft roll
   float alfa_aircraft;        //     Angle of attack
   float  beta_aircraft;       //     Slip angle
   float omcx_aircraft;        //     Angle speed component
   float  omcy_aircraft;       //     Angle speed component
   float  omcz_aircraft;       //      Angle speed component
   float  ncx_aircraft;        //      Component of linear g-load vector
   float  ncy_aircraft;        //      Component of linear g-load vector
   float  ncz_aircraft;        //      Component of linear g-load vector
   float  vc_aircraft;         //      Module of aircraft linear speed
   float vcx_aircraft;         //      Speed vector component
   float  vcy_aircraft;        //      Speed vector component
   float  vcz_aircraft;        //      Speed vector component
   float  M_aircraft;          //      Mach number
   double  xc_aircraft;         //      Aircraft linear coordinate along axis X
   double  yc_aircraft;          //
   double zc_aircraft;         //      Aircraft linear coordinate along axis Y
   float nypol_aircraft;       //      Aircraft linear coordinate along axis Z
   double   t_pol_aircraft;    //      Flight time
   float   G_engine;           //      Aircraft total weight
   float v_aircraft;           //      Vector of aircraft linear speed
   float alfaf_aircraft;       //      Refined angle of attack
   float nypr_aircraft;        //      G-limit of longitudinal passage
  float nzpr_aircraft;    //      G-limit of cross passage
  float nvy_aircraft;//7.12.10  check globalDEf for  cau.cpp
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
   double fiust_geography;          /*Setting geographical latitude*/
   double limdaust_geography;        /*Setting geographical longitude*/
   float Aust_geography;             /*Setting azimuth*/
   double x0_geography;               /*linear coordinate along axis X, zero*/
   double z0_geography;                /*linear coordinate along axis Z, zero*/
   float A0_geography;               /*Azimuth, zero*/
   float sa_geography;               /*Azimuth sinusoidal component */
   float ca_geography;               /*Azimuth cosine component*/
   float fi0_geography;               /*geographical latitude, zero*/
   float limda0_geography;            /*geographical longitude, zero*/
   float Rfi_1_geography;             /*Earth Geographical latitude, first*/
   float Rlimda_1_geography;          /*Earth Geographical longitude, first*/
   float R_Earth_geography;            /*Earth speed*/
   float Pr_start_geography;           /*start sign*/
   float device_externals_geography;    /*meterage*/
   double fit_geography;               /*Geographical latitude*/
   double limdat_geography;             /*Geographical longitude*/
   float Au_geography;                  /*Azimuth*/
   float v_Earth_geography;             /*Earth speed*/
   float  DeltaMSkl;                     /**/
   float  DeltaM0;                        /*Setting magnetic variation, zero */
   int    Got10G; //     Identifier of data readiness 10 Hz in LINS
   int    Pr10G;//   formation  10 Hz, sign           ! 05.01.10  признак  10 Гц  служебный признак для форм. Got10G
   int    CmGK; //    change geographical coordinates sign       ! 15.01.10  Смена Георграфических координат
   //int isMap;//use digital map
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
   float URUD;
   int  urud_left;
   int  urud_right;
   int  urud_left_in;
   int  urud_right_in;
//      int  urud_zap_in;

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
   float x_kren_rus;     //     CS displacement by roll
   float x_tan_rus;      //     CS displacement by pitch
   float x_kren_say;     //     CS displacement by roll from AFCS
   float x_tan_say;      //     CS displacement by pitch from AFCS
   float  URUD;          //     TCL values
}
TSetupRSS;//ХУФБОПЧПЮОЩЕ  ЛПОУФБОФЩ РТЙ ЙУИПДОПН

typedef   struct _TComOls
{
   int SV;           //признак визуалиаза  работа
   int ReqOls;       //запрос на обслуживание  ОЛС
   int OtvOLS;       //otvet  на запрос
   int Intersect;    //  признак перечения
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
   float  ux_aircraft;       //Wind speed component along axis X
   float  uz_aircraft;       //Wind speed componentпо along axis Z
   float  beta0_aircraft;    //Initial value of slip angle, zero
   float  Hbar_aircraft;     //Zero barometric altitude
   float  Hrvrf_C;           //Terrain zero elevation for radar-altimeter
   float  Hrvrfmin_C;        //Minimal terrain elevation for RA
   float  Hrvrfmax_C;        //Maximum terrain elevation for RA
   float  alfarvrf_C;        //Terrain slope angle for RA
   float  psirvrf_C;         //Terrain heading for RA
   float  Htargetrf_C;   //Terrain zero elevation for ground target (GT)
   float  Htargetrfmin_C;    //Minimal terrain elevation for GT
   float  Htargetrfmax_C;    //Maximum terrain elevation for GT
   float  alfatargetrf_C;    //Terrain slope angle for GT
   float  psitargetrf_C;     //Terrain heading for GT
   int    TUvod;             //Time response of maneuver "Escape"
   float   constTimeFloatProcess;//!!!  const time proc  reseting =63
   float   Hshasi;

}Tkinematiks_aircraftConst;

typedef
struct
_Tair_parametrs
{
   float H_air;      //Atmospheric height
   float Pst_air;    //Static atmosphere pressure at aircraft flight altitude
   float g_air;     //Dynamic pressure
   float v_dev_air;  //Indicated airspeed
   float advz;       /* Sound speed*/
   float M;         //Atmospheric Mach number
   float Pst_airPrev; //Static pressure of previous cycle
   float g_airPrev; //Dynamic pressure of previous cycle
   float v_dev_airPrev;//Indicated airspeed of previous cycle
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
   float vc_target;      /*Linear airspeeds of i-th target by module*/
   float ny_target;      /*Longitudinal g-load of maneuvering target*/
   float nz_target;      /*Lateral g-load of maneuvering target*/
   float vxi_target;     /*Speed of approach to i-th target along axis х*/
   float vyi_target;     /*Speed of approach to i-th target along axis у*/
   float vzi_target;     /*Speed of approach to i-th target along axis z*/
   float psi_target;         /*Course angle to i-th target*/
   float teta_target;        /*Flight path angle to i-th target*/
   float gama_target;        /*roll in vehicle state coordinates to i-th target*/
   float v_target;           /*Speed of approach to i-th target*/
   float vx_target;          /*Linear airspeeds of i-th target by axis x*/
   float vy_target;          /*Linear airspeeds of i-th target by axis y*/
   float vz_target;          /*Linear airspeeds of i-th target by axis z*/
//++++++++++
   double x_target;          /*Linear coordinates of i-th target in CA*/
   double y_target;          /*Linear coordinates of i-th target in CA*/
   double z_target;          /*Linear coordinates of i-th target in CA*/
//++++++
   float  fix_relational1;   /*Directional cosine angles of i-th target in vehicle state coordinates*/
   float  fiy_relational1;   /*Directional cosine angles of i-th target in vehicle state coordinates*/
   float  fiz_relational1;   /*Directional cosine angles of i-th target in vehicle state coordinates*/
   float  di_relational;     /*Range to i-th target*/
   float  pdi_relational;    /*Speed of i-th target*/
//++++++++++
   float fix_relational;      /*Directional cosine angles of i-th target in CA*/
   float fiy_relational;      /*Directional cosine angles of i-th target in CA*/
   float fiz_relational;      /*Directional cosine angles of i-th target in CA*/
   float l_target;            /*Length of i-th target*/
   float ki_target;              /*Roll factor. Value 0 or 1. Identifier of flight downward relative to wheel - 0, upward relative to wheel - 1*/
   int num_target;               /*Target number*/
   int N1Cstr;                   /*Number of the first target in formation*/
   int Beg_num_target;           //начальный номер цели
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
   int pr_pusk;        /*Mode "Start" identifier, "Ident_start"*/
   int pr_isxodnoe;    /*Mode "Initial" identifier, "Ident_init."*/
   int Kupr;           /*Identifier of control command from SDM CP, "C Ctrl"*/
   int FlagCountAero;  /*Identifier of count of aircraft and targets models (pr_pusk || pr_isxodnoe)*/
   int Regim12;        /*Mode "1/2"*/
   int LockWrite;      /*Identifier of control command from SDM CP*/
   int Kn_isxodnoe;    /*Values of button Initial from SDM CP*/
   int BufferReady;    /*Identifier of four-cycle buffer filling*/
   int IndexBuffer[4];        /*Indexes of current buffers */
   TDesThread DesThread;      /*Computing streams descriptor in RCDC*/
   int PrUst;                 /*Identifier of setting from PWS*/
   int UstKb;             /*Identifier of DB setting from PWS CP*/
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
   float Gasp;          //    AW total weight
}
TDSUOCOM;

/*
typedef
struct _TDRVCOM
{
   float Hg; пїЅпїЅпїЅ   пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ
   float HRV пїЅпїЅпїЅ   пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ*
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
   float mod_Vc;        //    Numerical value of aircraft speed
   float PsiC;          //    Aircraft heading; degrees
   float Hight;         //    Aircraft linear coordinate by axis Оу, m
   float TettaC;        //    Aircraft pitch; degrees
}TINITDesArcraft;

typedef
struct
_TINITDesTarget
{
   int   Global_numTarget;//Global number of aerial target
   int   TipTarget; //Target type - length
   float Speed0Target;  //   Numerical value of target speed, m/s
   float Psi0Target;    //   Target heading, degrees
   float Hight0Target;   //  Target linear coordinate by axis Оу; m
   float Tetta0Target;   //   Target pitch, degrees
   float Fi0Target;      //   Target roll, degrees
   float Dr0Target;      //   Range on the target, m
   int  Beg_num_target; //нач номер цели

}
TINITDesTarget;

/**************************************************************************/
typedef
struct
_TINITDesGRTarget
{
   int Global_numGRTarget;//Global number of ground target
   int Tip_GRTarget;    //Target type - length
   float Speed0_RGTarget;      //  Numerical value of target speed, m/s
   int SKS_GRTarget;          //   Target coordinate system type; 0-CA, 1-aircraft
   float Psi0_GRTarget;       //   Target heading, degrees
   float X0_GRTarget;         //   x coordinate, m
   float Z0_GRTarget;         //    z coordinate, m
   int  Beg_num_target; //нач номер цели
 }
TINITDesGRTarget;


typedef
struct
_TDesINITObject
{
   char comment[32]; // Коментарий к варианту.
   int numberOfTarget;            //   Number of targets
   int numberOfAirTarget;         //   Number of aerial targets
   int numberOfSTRTarget;         //   Number of target in formation
   TINITDesArcraft        INITDesArcraft;                         //  Aircraft parameters
   TINITDesTarget         INITDesTarget[NUMBER_TARGET];           //  Array of aerial targets parameters
   TINITDesGRTarget       INITDesGRTarget[NUMBER_TARGET];         //  Array of ground targets parameters
}
TDesINITObject;
/*************************************************************************/

typedef
struct
_TDesINITall
{
   int numberOfVariant;         //   Number of variants
   int Counter;                 //   Counter
   TDesINITObject       DesINITObject[NUMBER_VARIANT];       //     Arrays of objects descriptions
}TDesINITall;

typedef struct  _TInitGeoGraphy
{
   float Aust_0_geography;           //        Bearing angle of stabilized vehicle state coordinates
   double fiust_0_geography;          //        Latitude
   double limdaust_0_geography;       //        Longitude
   float  DeltaM0;                   //        Magnetic variation angle
   float x0_ust;                     //        Initial displacement by coordinate X
   float z0_ust;                     //        Initial displacement by coordinate Z
}
TInitGeoGraphy;


typedef struct
     _TCommonConst
{
   float TAlfa;      //Aerodynamic response time of attack angle
   float TBeta;      //Aerodynamic response time by slip angle
   float ADV;        //Initial sound speed
   float Tonnaj;     //Aircraft weight
   float Knx0;       //Initial value of dynamic resistance coefficient
   float ny_dop;      //G limits in longitudinal channel
   double fi_dv;      //  Engine angle of setting relative to aircraft axis x. In this example it is equal to 0.
   double Vmin_C;     //Minimal air speed of aircraft
   double Hmax_C;     //Maximum altitude of aircraft
   double Vmin_target; //Minimal target speed
   double Vmax_target; //Maximum target speed
   double Mat_min; //Minimum value M
   float  G0;  //Empty (unloaded) aircraft weight
   float  Gc;  //Aircraft weight
   float  AlfaSM;            //Hypermanoeuvrability alfa. Angle of attack at hypermanoeuvrability
   float  AlfaBalUst;        //Ballistic angle Alfa, preset by identifier CAP
}
TCommonConst;

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
    int RegimeContr;//! 0 Управ. из кабины  , реальное САУ
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
   TDesArjObject DesArjObject[4];
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
   //! признак перезапуска модели
   int restartModel;   
}TDSTRUCTVISULISATION;
#pragma pack(pop)
}
class cl_DataForVxWorks_SU30SM : public GenericData
{
public:
    cl_DataForVxWorks_SU30SM(void);

    //! буфер обновляется по требованию или в пуске
    SU30SM::TDSTRUCTVISULISATION bufferData;

    //! буфер который обновляется постоянно
    SU30SM::TDSTRUCTVISULISATION middleBufferData;


    SU30SM::TDSTRUCTVISULISATION* ptrBufData;

    virtual void newTransmitObject();

    //! сохраненное кол-во целей
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
    ///////////////////////////////////////////
    virtual void Vminair(double);
    virtual void Hmaxair(double);

    /*virtual void setChildProgram()
    {
        transmit->changePort();
        transmit->enableRecive(true);
    }*/

    //! РџСЂРёР·РЅР°Рє СѓСЃС‚Р°РЅРѕРІРєРё
    virtual void setComUst(bool f)
    {
        if(f==true)bufferData.ComUst=1;
        else bufferData.ComUst=0;

        middleBufferData.ComUst=bufferData.ComUst;
    }
    virtual int comUst(){return bufferData.ComUst;}

    virtual void refreshRegime();
    virtual void sendData();

    virtual bool prNewVariant()
    {
         return middleBufferData.FlagNewNVarIsh;
    }

    virtual void setPrNewVariant(bool f)
    {
        if(f==true)  bufferData.FlagNewNVarIsh=1;
        else bufferData.FlagNewNVarIsh=0;
    }
    virtual void setNumVariant(int var) {bufferData.NVarIsh=var;}
    virtual int  numVariant()           {return middleBufferData.NVarIsh;}

    virtual unsigned int counter();

    //! РљРѕР»-РІРѕ РІРѕР·РґСѓС€РЅС‹С… С†РµР»РµР№
    virtual int targetNumbers();

    //! кол-во воздушных целей
    virtual int targetAirNum();

    //!РЎРѕР·РґР°С‚СЊ РѕРєРЅРѕ СЃ Р°С‚РјРѕСЃС„РµСЂРЅС‹РјРё РїР°СЂР°РјРµС‚СЂР°РјРё Рё РіРµРѕРјРµС‚СЂРёРµР№
    virtual void createFormAtmGeo(void);
    virtual void refreshFormAtmGeo(void);

    //!РЎРѕР·РґР°С‚СЊ РѕРєРЅРѕ СЃ РєРёРЅРµРјР°С‚РёС‡РµСЃРєРёРјРё РїР°СЂР°РјРµС‚СЂР°РјРё
    virtual void createFormKinAircraft(void);
    virtual void refreshFormKinAircraft(void);

    //!СЃРѕР·РґР°С‚СЊ РѕРєРЅРѕ СЃ С†РµР»СЏРјРё
    virtual void createFormTargets(void);
    virtual void refreshFormTargets(void);

    //!СЃРѕР·РґР°С‚СЊ РѕРєРЅРѕ СЃ РєРѕРЅСЃС‚Р°РЅС‚Р°РјРё
    virtual void createFormConst(void);
    virtual void refreshFormConst(void);



    //! СЃРѕР·РґР°С‚ РѕРєРЅРѕ СЃ РѕР±С‰РёРјРё РєРѕРЅСЃС‚Р°РЅС‚Р°РјРё
    virtual void createFormCommonConst(void);
    virtual void refreshFormCommonConst(void);
    virtual void callSlotResived(char* ptr);

    //!РћР±РЅРѕРІРёС‚СЊ РґР°РЅРЅС‹Рµ
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
    //СѓРіРѕР» РЅР°РєР»РѕРЅР° С‚СЂР°РµРєС‚РѕСЂРёРё
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
#endif /* CL_DATAFORVXWORKS_H_ */
