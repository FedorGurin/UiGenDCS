#ifndef GL_FUNC_H
#define GL_FUNC_H

#define GLM_PRECISION_HIGHP_FLOAT
#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include "ibuffer.h"
#include <limits.h>
#include "matrix3D_D.h"
///////////////////////////////////////////////////////////////////


#ifndef	EPS
    #define	EPS	0.000000000000001
#endif

#ifndef	M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef GravA
#define GravA 9.81
#endif

#define RadToGrad 180.0/M_PI
#define GradToRad M_PI/180
//////////////////////////////////////////////////////////////////



//! общие константы
const double gradToRad =   M_PI/180.0;
const double radToGrad =   180.0/M_PI;
const double sqrt2 =       sqrt(2.0)/2.0;
const double pi2 =         M_PI/2.0;

class TTable2D
{
public:
    TTable2D(double *m_=0,unsigned sizeCol_=0,unsigned sizeRow_=0)
    {
        m=m_;
        sizeCol=sizeCol_;
        sizeRow=sizeRow_;
    }
    double *m;
    unsigned sizeCol;
    unsigned sizeRow;
};
class TTable1D
{
public:
    TTable1D(double *m_=0,unsigned sizeCol_=0,unsigned sizeRow_=0)
    {
        m=m_;
        sizeCol=sizeCol_;
        sizeRow=sizeRow_;
    }
    double *m;
    int sizeCol;
    int sizeRow;
};
class TGeo
{
public:
    TGeo(double lat_fi=0.0,double lon_lam=0.0,double h_=0.0)
    {
        lat=lat_fi;lon=lon_lam;h=h_;
//        fi=lat_fi; lam=lon_lam;

        lat0=lat;lon0=lon;h0=h;
//        fi0=lat; lam0=lon;

    }
    double lat;//! широта, рад
    double lon;//! долгота, рад
    double h;  //! высота географич, метры

//    double fi;//! широта, рад
//    double lam;//! долгота, рад


    double lat0;//! широта, рад
    double lon0;//! долгота, рад
    double h0;  //! высота географич, метры

//    double fi0;//! широта, рад
//    double lam0;//! долгота, рад

    glm::vec3 c_g;//! линейные координаты относительно земной СК(начало которой lat0,lon0,h0)
};

//! углы относительно строительной оси
class TAngle
{
public:
    TAngle(double tau_=0.0,double sigma_=0.0):tau(tau_),sigma(sigma_){}
    TAngle(TAngle* angle)
    {
        this->sigma=angle->sigma;
        this->tau=angle->tau;
    }
    void set(double tau_,double sigma_){tau=tau_;sigma=sigma_;}

    //! смещение по вертикали (положительное направление - вверх)
    double tau;
    //! смещение по горизонтали (положительное направление - влево)
    double sigma;

    double distance()
    {
        return tau*tau+sigma*sigma;
    }
    const TAngle operator + (const TAngle &angle)const
    {
        TAngle a;
        a.sigma=this->sigma+angle.sigma;
        a.tau=this->tau+angle.tau;
        return a;
    }
    const TAngle operator - (const TAngle &angle)const
    {
        TAngle a;
        a.sigma=this->sigma-angle.sigma;
        a.tau=this->tau-angle.tau;
        return a;
    }

    void operator = (const TAngle& angle)
    {
        this->sigma=angle.sigma;
        this->tau=angle.tau;
    }

    void clear()
    {
        tau=0.0;
        sigma=0.0;
    }
};
//! определение двух углов направления вектора заданного в земной горизонтированной системе координат
void earthTo2Angles(glm::vec3 inVec,TAngle *anglesVec);

//! расчет общей матрицы поворта на два угла
glm::mat3 calcTAngleMatrix(TAngle);

//! преобразование вектора скорости из траекторной СК в земную СК
void calcVFromTracToEarth(const double tetta_,const double fi_,const double vg_,double &vxg_,double &vyg_,double &vzg_);


//! пересечение прямой и плоскости
void  intersectPlaneAndLine(glm::vec3 &inVec,glm::vec3 dVec,double &hPlane,glm::vec3 &intersectDot);

//! преобразование точки(в земной системе координат) в координаты (два угла относительно строительной оси)
void earthToSGF(const glm::vec3 &inCoord,           /*координаты которые нужно преобразовать*/
                const glm::vec3 &inAircraft,        /*координаты самолета*/
                const glm::mat3 &inMatrixAircraft,  /*матрица поворота самолета*/
                TAngle *outAngleSGF);               /*углы относительно СГФ*/

void earthToSGF(const Vector3D_D &inCoord,const Vector3D_D &inAircraft, const Matrix3D_D &inMatrixAircraft,  TAngle *outAngleSGF);



//! преобразование двух углов(относительно СГФ) в координаты точки в земной системе координат и пересечение с высотой dH
void sgfToEarth(const TAngle &inAngleSGF,
                const glm::vec3 &inAircraft,
                const glm::mat3 &inMatrixAircraft,
                const double &dH,
                glm::vec3 *outCoord);

//! определение направляющего вектора()
void sgfToEarthDirectionVec(TAngle inAngleSGF,
                            glm::vec3 inAircraft,
                            glm::mat3 &inMatrixAircraft,
                            glm::vec3 *outDirectionVec);

//! преобразование из земной СК в горизонтированную самолетную СК
void convertEarthToGorizontAircraft(glm::vec3 inAircraft,
                                    glm::mat3 matrixPsi,
                                    glm::vec3 inPoint,
                                    glm::vec3 &outPointGor);

//! преобразование из горизонтированной самолетной СК в земную СК
void convertGorizontAircraftToEarth(glm::vec3 inPointGor,
                                    glm::vec3 inAircraft,
                                    glm::mat3 matrixPsi,
                                    glm::vec3 &outPointEarth);

//! преобразование координат из горизонтированной СК в земную СК
void convertGorizontAircraftToEarth(glm::vec3 inPointGor,
                                    glm::mat3 matrixPsi,
                                    glm::vec3 &outPointEarth);

//! проверка для горизонтального угла
void checkSigma(double &sigma,
                double D0x1,
                double D0z1);

//! расчет углов поворота головы на цель отностиельно земли
void calcAngleRotateHeadEarth(glm::vec3 &vecAircraft,   /*вектор на центр самолета относительно земли*/
                              glm::vec3 &vecDevice,     /*вектор на центр устройства(контейнера) относит. самолета*/
                              glm::vec3 &vecOnHead,     /*вектор на головку относительно центра контейнера*/
                              glm::vec3 &vecTarget,     /*вектор на цель(точка привязки) относительно земли*/
                              glm::mat3 &matrixAircraft,/*матрица поворота самолета относительно земли*/
                              TAngle &angle             /*углы поворота головы контейнера на цель*/
                              );

//! расчет углов поворота головы на цель относительно связанной СК самолета
void calcAgnleRotateHead(glm::vec3 &vecAircraft,   /*вектор на центр самолета относительно земли*/
                         glm::vec3 &vecDevice,     /*вектор на центр устройства(контейнера) относит. самолета*/
                         glm::vec3 &vecOnHead,     /*вектор на головку относительно центра контейнера*/
                         glm::vec3 &vecTarget,     /*вектор на цель(точка привязки) относительно земли*/
                         glm::mat3 &matrixAircraft,/*матрица поворота самолета относительно земли*/
                         glm::mat3 &matrixDevice,  /*матрица поворота устройства относ. самолета*/
                         TAngle &angle,            /* углы поворота головы контейнера на цель tau=(-90;90) sigma=(-180;180)*/
                         TAngle &angleNeg          /* углы поворота головы контейнера на цель tau=(-180;180) sigma=(-90;90)*/
                         );

double linearInterpY( double Y,  // значение в точке Y
                      double Y2, // точка Y2
                      double Y1, // точка Y1
                      double X2, // точка X2
                      double X1);// точка X1
//! линейная интерполяция
double linearInterpolation( double X,  // значение в точке Y
                            double Y2, // точка Y2
                            double Y1, // точка Y1
                            double X2, // точка X2
                            double X1);// точка X1

//! Преобразование сферических в декартовы
//! lambda0,fi0 - географическая точка старта
//! lambda, fi  - текущие координаты, которые нужно пересчитать в прямоугольные
void convertSphereToDekart(double lambda0   /*рад*/,    double fi0  /*рад*/,
                           double lambda    /*рад*/,    double fi   /*рад*/,
                           double &x        /*метры*/,  double &z   /*метры*/);

//! Преобразование декартовых в сферические
void convertDekartToSphere(double lambda0   /*рад*/,    double fi0  /*рад*/,
                           double x         /*метры*/,  double z    /*метры*/,
                           double &lambda   /*рад*/,    double &fi  /*рад*/);
///////////////////////////////////////////////////////
//! обертка преобразование географических в декартовые
void convertGeoToDekart(double lambda0,double fi0,
                        double lambda,double fi,
                        double &x,double &z);

//! обертка преобразование географических в декартовые
void convertDekartToGeo(double lambda0,double fi0,
                        double x,double z,
                        double &lambda,double &fi);
////////////////////////////////////////////////////////
//! разница между длинами векторов
double dTo(glm::vec3 &vecBegin,glm::vec3 &vecEnd);


//! преобразование координат точки в одной системе координат в другую
//TPoint convertToStartAircraft(TPoint rVectorOut, TPoint rVectorTo);
//! вычисление индекса в строке
int searchColIndexInRow(double X,
                        double *mas,
                        int sizeCol);

//! вычисление индекса в строке(в 2D таблице)
int searchRowIndexIn2DTable(double Y,           /*тек. значение в столбце 0*/
                            double *mas,        /*указатель на массив*/
                            unsigned sizeCol,   /*кол-во столбцов*/
                            unsigned sizeRow);   /*кол-во строк*/

//! вычисление индекса в столбце(2D таблице)
int searchColIndexIn2DTable(double X,           /*тек. значение в строке 0*/
                            double *mas,        /*указатель на массив*/
                            unsigned sizeCol);   /*кол-во столбцов*/

//! итерполяция для одной строки
double rowInterpolation(double Y,double *masY, int sizeCol,int indexCol=-1, int indexRow=1);
double rowInterpolation(double Y,const TTable1D *table,int indexCol, int indexRow);


//! линейная интерполяция двухмерной таблицы
double linearInter2DTable(double X,double Y,double *masXY,unsigned sizeRow,unsigned sizeCol,int indexRow=-1,int indexCol=-1);
double linearInter2DTable(double X,double Y,const TTable2D *table,int indexRow,int indexCol);



//! симуляция движения АСП попадание в любую движущуюся цель координаты и скорости заданы относительно земли

/* Рекоминдации при выборе среднего значения для функции сопротивления E
– если задать слишком малое значение E , то сопротивление воздуха мало,
 АСП будет двигаться как в безвоздушном пространстве, траектория близка к параболической;

– если задать слишком большое значение E , то сопротивление воздуха велико,
 траектория АСП быстро выпрямляется и АСП движется по прямой линии.

 для хорошо обтекаемых гладких АБ можно взять E=0.02
*/
void simTrajASP(glm::vec3 inStartASP,       /*координаты АСП в начальный момент времени (м)*/
                glm::vec3 inSpeedASP,       /*компоненты вектора скорости в начальный момент (м/с)*/
                glm::vec3 inEndASP,         /*координаты цели(конечная точка падения АСП) (м)*/
                double inTimeMoveASP,       /*время движения АСП(сек.)*/
                double inE,                 /*среднее значение функции сопротивления АСП (б/р)*/
                double inCurrentT,          /*текущее значение времени(сек.)*/
                glm::vec3 &curentSpeedASP,  /*Текущие компоненты скорости АСП-выходная переменная (м/с)*/
                glm::vec3 &curentCoordASP   /*Текущие координаты АСП-выходная переменная (м)*/
                );


//! преобразование ед. измерения
double gradToRadian(double x);
double radianToGrad(double x);
TAngle radianToGrad(TAngle);
TAngle gradToRadian(TAngle);
double kmToMeter(double x);
double meterToKm(double x);
//! проверка попадания значения в диапазон
bool checkValue(double value, double cur,double acc);
//! откидывание дробной части
double checkZero(double x);

//! возвращает число num со знаком от числа s
double signF(double num,double s);
//! возвращает знак числа num [-1.0 или 1.0]
double signF(double num);
//! функция сигмода(экспонента), возвращаемое значение
double sigmoid(double value);
//! нормализация занчения дипазоном [-1.0;1.0]
double normValue(double x);
//! преобразование [180.0;-180] в [0;360.0], рад
double psiToKurs(double);
//! проверка выхода за [180;-180]
double checkPI(double);
double check180(double);
double ugol_ogrMPI_toMPI(double value);
//! Преобразование [0;360.0] в [180.0;-180], рад
double kursToPsi(double);
//! проверка выхода за [0;2*Pi]
double check2PI(double);
//! проверка выхода за [0;-360]
double check360(double);
void WGS84LatLon2DxDz(double lat1, double lon1, double lat2, double lon2,
double& DXkm, double& DZkm, double& PSKgrad, double& Dkm);
double Vpr(double Vms, double Hmeters);
//! преобразование на эллипсоиде
void LatLon2DxDz(double &x0,double &z0,
                        double lat, double lon,
                        double lat_0,double lon_0);
void DxDz2LatLon(double x,double z,
                 double &lat, double &lon,
                 double lat_0,double lon_0 );

glm::vec3 aerodC_c(glm::vec3 C_a,double alfa,double beta);
//! ограничение сверху и снизу
/*template<typename T> T limitMinMax(T value,T min,T max)
{
    if(value<min) value=min;
    else if(value>max) value=max;

    return value;
}*/
//! ограничение сверху и снизу c признаком выхода на ограничение
template<typename T> T limitMinMax(T value,T min,T max,bool *limit=0)
{
    if(limit!=0)
        *limit=false;
    if(value<min)
    {
       value=min;
       if(limit!=0)
           *limit=true;
    }
    else if(value>max)
    {
        value=max;
        if(limit!=0)
            *limit=true;
    }
    return value;
}
//! гиперболический синус
double asinh(double x);
//! ограничение сверху
double limitMax(double value,double max);
//! ограничение снизу
double limitMin(double value,double min);
//! чтение данных в 2D таблицу
//void readDataToMatrix(const QDomElement &root, const QString &nameMatrix, TTable2D &pM);
//! чтение данных в 1D таблицу
//void readDataToVector(const QDomElement& root, const QString& nameVector,TTable1D &pM);
//! апериодический фильтр
class FilterAperiodic
{
public:

    FilterAperiodic(double valueStart_,double k_,double step_,double maxValue_=LONG_MAX, double minValue_=LONG_MIN);
    //! сброс фильтра
    void resetFilter(double valueStart_);
    //! установка текущего значения фильтра
    double filterValue(double valueCurr);
    //! обновление фильтра(с заданной частотой)
    void refresh();
    //! возврат текущего значения фильтра
    double setFilterValue(double currentValue);
    //! задать коэффициент при звене
    void setK(double k_);
private:
    double valueStart;
    double valueCurrent;//значение на входе в фильтр
    double maxValue;
    double minValue;

    double value;//текущее знчачение фильтра
    double step;
    double k;
};
//! аппериодический фильтр для углов sigma, tau
class FiltersAperiodicAngle
{
public:
    FiltersAperiodicAngle(TAngle valueStart_,
                          double k_,
                          double step_,
                          double maxValue_,
                          double minValue_);
    //! сброс фильтра
    void resetFilter(TAngle valueStart_);
    //! установка текущего значения фильтра
    TAngle filterValue(TAngle valueCurr);
    //! обновление фильтра(с заданной частотой)
    void refresh();
    //! возврат текущего значения фильтра
    TAngle setFilterValue(TAngle currentValue);
    //! задать коэффициент при звене
    void setK(double k_);

private:

    FilterAperiodic *filterSigma;
    FilterAperiodic *filterTau;
};

//! метод Бутчера 6 порядка
/*
Butcher I.C. On Runge-Ketta processes of high order,
Y.Austral.Math.Soc., Vol.4, Part 2, p.179-194. - 1964
*/
template<typename T,int nParam>
void odd_Butcher_6order(T* const obj,
                    int nSDU,
                    double *inValue,
                    double *outValue,
                    double step)
{
    double tempSDU[nParam];
    double c2=1.0/2.0,      c3=2.0/3.0,     c4=1.0/3.0,     c5=5.0/6.0,     c6=1.0/6.0,     c7=1.0;

    double a21=1.0/2.0;
    double a31=2.0/9.0,     a32=4.0/9.0;
    double a41=7.0/36.0,    a42=2.0/9.0,    a43=-1.0/12.0;
    double a51=-35.0/144.0, a52=-55.0/36.0, a53=35.0/48.0,  a54=15.0/8.0;
    double a61=-1.0/360.0,  a62=-11.0/36.0, a63=-1.0/8.0,   a64=1.0/2.0,    a65=1.0/10.0;
    double a71=-41.0/260.0, a72=22.0/13.0,  a73=43.0/156.0, a74=-118.0/39.0,a75=32.0/195.0,a76=80.0/39.0;

    double b1=13.0/200.0,   b2=0.0,       b3=11.0/40.0,   b4=11.0/40.0,   b5=4.0/25.0,   b6=4.0/25.0,    b7=13.0/200.0;
    //////////////////////////////////////////////////////////////////////////

    double k1[nParam],k2[nParam],k3[nParam],k4[nParam],k5[nParam],k6[nParam],k7[nParam];
    //! обнуление массивов
    for(int i=0;i<nParam;i++)
    {
        k1[i]=0;k2[i]=0;k3[i]=0;k4[i]=0;k5[i]=0;k6[i]=0;k7[i]=0;tempSDU[i]=0;

    }

    for(int i=nSDU;i<nParam;i++) tempSDU[i]=inValue[i];

    obj->SDU(inValue,k1);

    for(int i=1;i<nSDU;i++) tempSDU[i]=inValue[i]+step*a21*k1[i];
    tempSDU[0]=inValue[0]+c2*step;
    obj->SDU(tempSDU,k2);

    for(int i=1;i<nSDU;i++) tempSDU[i]=inValue[i]+step*(a31*k1[i]+a32*k2[i]);
    tempSDU[0]=inValue[0]+c3*step;
    obj->SDU(tempSDU,k3);

    for(int i=1;i<nSDU;i++) tempSDU[i]=inValue[i]+step*(a41*k1[i]+a42*k2[i]+a43*k3[i]);
    tempSDU[0]=inValue[0]+c4*step;
    obj->SDU(tempSDU,k4);

    for(int i=1;i<nSDU;i++) tempSDU[i]=inValue[i]+step*(a51*k1[i]+a52*k2[i]+a53*k3[i]+a54*k4[i]);
    tempSDU[0]=inValue[0]+c5*step;
    obj->SDU(tempSDU,k5);

    for(int i=1;i<nSDU;i++) tempSDU[i]=inValue[i]+step*(a61*k1[i]+a62*k2[i]+a63*k3[i]+a64*k4[i]+a65*k5[i]);
    tempSDU[0]=inValue[0]+c6*step;
    obj->SDU(tempSDU,k6);

    for(int i=1;i<nSDU;i++) tempSDU[i]=inValue[i]+step*(a71*k1[i]+a72*k2[i]+a73*k3[i]+a74*k4[i]+a75*k5[i]+a76*k6[i]);
    tempSDU[0]=inValue[0]+c7*step;
    obj->SDU(tempSDU,k7);

    outValue[0]=inValue[0]+step;
    for(int i=1;i<nSDU;i++) outValue[i]=inValue[i]+step*(b1*k1[i]+b2*k2[i]+b3*k3[i]+b4*k4[i]+b5*k5[i]+b6*k6[i]+b7*k7[i]);

}

//! метод Рунге-Кутты 4 порядка (шаблонная)
template<typename T,int nParam /*общее кол-во параметров*/>
void rk4(T* const obj,         /*объект класса должен содержать функцию SDU*/
         double *inValue,      /*начальные значения ОДУ, inValue!=0*/
         double *outValue      /*вычисленные значения ОДУ, outValue!=0*/,
         int nSDU              /*кол-во дифф. уравнений*/,
         double step           /*шаг интегрирования*/
         )
{
    double df[nParam][4];
    double fout[nParam];

    for(int j = 0; j < 4; j++)
    {
        if(j==0)
            obj->SDU(inValue,fout);
        else
            obj->SDU(outValue,fout);

        for(int i = 0; i < nSDU; i++)
        {
            df[i][j] = fout[i] *step;
            switch(j)
            {
            case 0:{outValue[i] = inValue[i] + 0.5 * df[i][j];break;}
            case 1:{outValue[i] = inValue[i] + 0.5 * df[i][j];break;}
            case 2:{outValue[i] = inValue[i] + df[i][j];break;}
            case 3:{outValue[i] = inValue[i] + (df[i][0]+2.0*(df[i][1]+df[i][2])+df[i][3])/6.0;}
            }
        }
        for(int k=nSDU;k<nParam;k++)
        {
            outValue[k]=inValue[k];
        }
    }
}
//! метод деления по полам
//! находим такие аргументы x, при которых значение функции y=F(x) близко к y_e
template<typename T>
double bisection1D(T* const obj,double x_min,double x_max,double y_e)
{
    double y_min=obj->func(x_min);
    double y_max=obj->func(x_max);
    double x_mid=x_min + ((x_max - x_min)/2.);
    double y_mid=obj->func(x_mid);

    while(fabs(y_mid-y_e)>3.)
    {
        if(y_e>y_mid)
        {
            x_min=x_mid;
            y_min=y_mid;
        }
        else
        {
            y_max=y_mid;
            x_max=x_mid;
        }
        x_mid=x_min + ((x_max - x_min)/2.);
        y_mid=obj->func(x_mid);
    }
    return x_mid;
}

//! метод Адамса 4-порядка
template<typename T, typename X>
void adams4(T* const obj,
            int nSDU,
            double step)
{
    double fout[nSDU];
    double outValue[nSDU];

    //! расчитаем коэфф. для шагов
    double k_0=55.0/24.0;
    double k_1=59.0/24.0;
    double k_2=37.0/24.0;
    double k_3=9.0/24.0;

    obj->SDU(obj->buf[0]->current()->masDouble,fout);

    for(int k=0;k<nSDU;k++)
    {
        double fi=obj->buf_p[0]->current()->masDouble[k];
        double fi_1=obj->buf_p[1]->current()->masDouble[k];
        double fi_2=obj->buf_p[2]->current()->masDouble[k];
        double fi_3=obj->buf_p[3]->current()->masDouble[k];

        double y=obj->buf[0]->current()->masDouble[k];

        double y1=y+step*(k_0*fi-k_1*fi_1+k_2*fi_2-k_3*fi_3);
        outValue[k]=y1;
    }
    BufferDATA<X> bufferdata;
    for(int k=0;k<nSDU;k++)
    {
        bufferdata.masDouble[k]=outValue[k];
    }

    obj->buf.push(bufferdata.value);
    for(int k=0;k<nSDU;k++)
    {
        bufferdata.masDouble[k]=fout[k];
    }
    obj->buf_p.push(bufferdata.value);

}
//! метод Адамса 4-порядка (предикатор-корректор)
template<typename T,typename J,int nParam>
void adams4_pred_correct(T* const obj,
            int nSDU,
            IBuffers<J> *buffers,
            double step)
{

}
//! метод Эйлера
template<typename T,int nParam>
void euler(T* const obj,
           double *inValue,
           double *outValue,
           int nSDU,
           double step)
{

}

//формирование  кода для СТК датчика по углу  Fi, рад
unsigned short int CTKofFi(float  Fi);
//! реализация ПИД-регулятора
class VPid
{
public:
    VPid(double proportional, double integral, double differential,
         double period, double minSaturation, double maxSaturation);

    double getValue(double input);

private:
    //! значения на предыдущем шаге
    double m_lastResult;
    double m_lastInput;

    //! коэффициенты в звеньях
    double m_proportional;
    double m_integral;
    double m_differential;
    //! шаг вызова
    double m_period;
    //! ограничение по выходу
    double m_minSaturation;
    double m_maxSaturation;
};

template <class Type> Type parity()
{

}
////////////////РАБОТА С БИТАМИ
//=============================================================================
//! чтение группы битов, нумерация битов с 0...31
//! hBit старший бит(слева)
//! lBit младший бит(справо)
//! value32 число из которого читаются биты с [hBit31 по lBit0] включительно
template <class Type> Type readCode0(Type value31,  /*число из которого читается код*/
                                     int hBit31,    /*старший бит(hight bit)*/
                                     int lBit0)     /*младший бит(low bit)*/
{
    Type tempValue=0;
    if(hBit31<lBit0)
    {
        tempValue=lBit0;
        lBit0=hBit31;
        hBit31=tempValue;
    }
    tempValue=0;
    int sum=(hBit31-lBit0);
    for(int i=0;i<=sum;i++)
    {
        tempValue=(tempValue<<1)|1;
    }
    return ((((value31)&(tempValue<<(lBit0))))>>(lBit0));
}
//! запись кода образованного битами [hBit,lBit]
//! из value32_from в value32_to с учетом, что нумерация битов
//! подчиняется нумерации МКИО; [c 19,по 4] бит
template <class Type> Type readCodeMKIO(Type value31,  /*число из которого читается код*/
                                     int hBit31,    /*старший бит(hight bit)*/
                                     int lBit0)     /*младший бит(low bit)*/
{
    hBit31=19-hBit31;
    lBit0=19-lBit0;
    return readCode0(value31,hBit31,lBit0);
}

//! чтение битов, нумерация битов с 1...32
//! hBit старший бит(слева)
//! lBit младший бит(справо)
//! value32 число из которого читаются биты с [hBit32 по lBit1] включительно
template <class Type> Type readCode(Type value32,/*число из которого читается код*/
                                    int hBit32,/*старший бит(hight bit)*/
                                    int lBit1)/*младший бит(low bit)*/
{
    hBit32--;
    lBit1--;

    return readCode0(value32,hBit32,lBit1);
}
//=============================================================================
//! чтение бита, нумерация битов с 0...31
template <class Type> Type rBit0(Type value31,  /*число из которого читается бит*/
                                    int bit)       /*позиция бита (31...0)*/
{
    return readCode0(value31,bit,bit);
}
//===============================================================================================
//! запись кода образованного битами [hBit31from,lBit0from]
//! из value32_from в value32_to в биты с позицией [hBit31to,lBit0to] с учетом, что нумерация битов стандартная(Intel)
//! [c 31(старший),по 0(младший)] бит
//! если интервалы [hBit31from,lBit0from] и [hBit31to,lBit0to] не совпадают, то.....
template <class Type> void writeCode(Type &value32_to,
                                     int hBit31to,
                                     int lBit0to,

                                     Type value32_from,
                                     int hBit31from,
                                     int lBit0from)
{
    unsigned mask_from=((0xFFFFFFFF<<lBit0from) & (0xFFFFFFFF>>(31-hBit31from)));
    unsigned mask_to=((0xFFFFFFFF<<lBit0to) & (0xFFFFFFFF>>(31-hBit31to)));

    value32_from=(value32_from & mask_from)<<lBit0to;
    value32_to=(value32_to & ~mask_to) | value32_from;
}
//! запись кода образованного битами [hBit,lBit]
//! из value32_from в value32_to с учетом, что нумерация битов стандартная(Intel)
//! [c 31(старший),по 0(младший)] бит
template <class Type> void writeCode(Type &value32_to,
                                     Type value32_from,
                                     int hBit31,
                                     int lBit0)
{
    unsigned mask=((0xFFFFFFFF<<lBit0) & (0xFFFFFFFF>>(31-hBit31)));

    value32_from=(value32_from<<(lBit0)) & mask;
    value32_to=(value32_to & ~mask) | value32_from;
}
//! нумерация 32..1
template <class Type> void writeCode32(Type &value32_to,
                                       Type value32_from,
                                       int hBit32,
                                       int lBit1)
{
    hBit32--;
    lBit1--;
    unsigned mask=((0xFFFFFFFF<<hBit32) & (0xFFFFFFFF>>(32-lBit1)));

    value32_from=(value32_from<<(lBit1)) & ~mask;
    value32_to=(value32_to & mask) | value32_from;
}

//! запись кода образованного битами [hBit,lBit]
//! из value32_from в value32_to с учетом, что нумерация битов
//! подчиняется нумерации МКИО; [c 19,по 4] бит
template <class Type> void writeCodeMKIO(Type &value32_to, /*в число*/
                                         Type value32_from,/*из числа*/
                                         int hBit,/*с старшего бита(включительно)*/
                                         int lBit)/*по младший бит (включительно)*/
{
    hBit=19-hBit;
    lBit=19-lBit;
    unsigned mask=(0xFFFFFFFF<<hBit) & (0xFFFFFFFF>>(31-lBit));

    value32_from=(value32_from<<(hBit)) & mask;
    value32_to=(value32_to & ~mask) | value32_from;
}
//! сравнение двух участков памяти с одинковой размерностью
bool compareMems(char *dst, char *src,int size);

#endif // GL_FUNC_H
