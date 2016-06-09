#include "math_func.h"

#include <math.h>
#define USE_MODEL_H
//#define USE_SPHERE
//#define USE_GAUSS_KRUGGER



#ifdef USE_GAUSS_KRUGGER
//! преобразование долготы и широты в координаты
void convertBLtoXY(double fi, double lam, double &n, double &e);
void convertXYtoBL(double n, double e, double &fi, double &lam);
#endif

#define _R_ZEML_EKV   6378137.0
#define _R_ZEML_POL   6356752.0

//#define EPS	0.0001f
/*double limitMinMax(double value,double min,double max)
{
    if(value<min) value=min;
    else if(value>max) value=max;

    return value;
}*/


//! ограничение сверху
double limitMax(double value,double max)
{
    if(value>max) value=max;
    return  value;
}
//! ограничение снизу
double limitMin(double value,double min)
{
    if(value<min) value=min;
    return  value;
}
//! линейная интерполяция между двумя значениями
double linearInterpolation(double X,double Y2,double Y1,double X2,double X1)
{
    double a=0.0,b=0.0;

    a=(Y2-Y1)/(X2-X1);

    b=Y1-a*X1;

    return a*X+b;
}
double linearInterpY(double Y,double Y2,double Y1,double X2,double X1)
{
    double a=0.0,b=0.0;

    a=(Y2-Y1)/(X2-X1);

    b=Y1-a*X1;

    return (Y-b)/a;
}
int searchColIndexInRow(double X,
                        double *mas,
                        int sizeCol)
{
    for(int i=0;i<sizeCol;i++)
    {
        if(mas[i]>X)
        {
           return i;
        }

    }
    return -1;
}
//! поиск индекса строки в столбце
int searchRowIndexIn2DTable(double Y,           /*тек. значение в столбце 0*/
                            double *mas,        /*указатель на массив*/
                            unsigned sizeCol,   /*кол-во столбцов*/
                            unsigned sizeRow)   /*кол-во строк*/
{
    //! вычислим индексы
    for(unsigned i=0;i<sizeRow;i++)
    {
        if(mas[i*sizeCol]>=Y)
            return i;
    }
    return -1;
}
//! поиск индекса столбца в строке
int searchColIndexIn2DTable(double X,           /*тек. значение в строке 0*/
                            double *mas,        /*указатель на массив*/
                            unsigned sizeCol)   /*кол-во столбцов*/
{
    X=limitMinMax(X,mas[1],mas[sizeCol-1]);
    //! вычислим индексы
    for(unsigned i=1;i<sizeCol;i++)
    {
        if(mas[i]>=X)
            return i;
    }
    return -1;
}
//! интерполяция только в одной строке
double rowInterpolation(double Y,const TTable1D *table,int indexCol, int indexRow)
{
    if(indexCol==-1)
    {
        for(int i=0;i<table->sizeCol;i++)
        {
            if(table->m[i]>Y)
            {
                indexCol=i;
                break;
            }

        }
    }

    //! если индекс столбца вышел за левую границу, то вернуть крайнее значение левой границы
    if(indexCol<=0) return table->m[table->sizeCol];
    //! если индекс столбца вышел за правую границу, то вернуть крайнее значение правой границы
    if(indexCol>(table->sizeCol-1)) return table->m[2*table->sizeCol-1];

    //! иначе считаем линейку
    int index=indexCol+indexRow*table->sizeCol;//! индекс для перемещения в двухмерном массиве

    return linearInterpolation(Y,table->m[index],table->m[index-1],table->m[indexCol],table->m[indexCol-1]);
}
//! интерполяция только в одной строке
double rowInterpolation(double Y,double *masY, int sizeCol,int indexCol, int indexRow)
{
    if(indexCol==-1)
    {
        for(int i=0;i<sizeCol;i++)
        {
            if(masY[i]>Y)
            {
                indexCol=i;
                break;
            }

        }
    }

    //! если индекс столбца вышел за левую границу, то вернуть крайнее значение левой границы
    if(indexCol<=0) return masY[sizeCol];
    //! если индекс столбца вышел за правую границу, то вернуть крайнее значение правой границы
    if(indexCol>(sizeCol-1)) return masY[2*sizeCol-1];

    //! иначе считаем линейку
    int index=indexCol+indexRow*sizeCol;//! индекс для перемещения в двухмерном массиве

    return linearInterpolation(Y,masY[index],masY[index-1],masY[indexCol],masY[indexCol-1]);
}
double linearInter2DTable(double X,double Y,double *masXY,unsigned sizeRow,unsigned sizeCol,int indexRow,int indexCol)
{

    double y1=0.0,y2=0.0;

    if(indexCol==-1)
    {
        X=limitMinMax(X,masXY[1],masXY[sizeCol-1]);
        //! вычислим индексы
        for(unsigned i=1;i<sizeCol;i++)
        {
            if(masXY[i]>=X)
            {
                indexCol=i;
                break;
            }
        }
    }
    if(indexRow==-1)
    {
        //! вычислим индексы
        for(unsigned i=0;i<sizeRow;i++)
        {
            if(masXY[i*sizeCol]>=Y)
            {
                indexRow=i;
                break;
            }
        }
    }
    indexRow=limitMinMax(indexRow-1,1,(int)(sizeRow-2));
    indexCol=limitMinMax(indexCol-1,1,(int)(sizeCol-1));

    y1=rowInterpolation(X,masXY,sizeCol,indexCol+1,indexRow);
    y2=rowInterpolation(X,masXY,sizeCol,indexCol+1,indexRow+1);

    return linearInterpolation(Y,y2,y1,masXY[sizeCol*(indexRow+1)],masXY[sizeCol*indexRow]);

}
double linearInter2DTable(double X, double Y, const TTable2D *table, int indexRow, int indexCol)
{

    double y1=0.0,y2=0.0;

    if(indexCol==-1)
    {
        X=limitMinMax(X,table->m[1],table->m[table->sizeCol-1]);
        //! вычислим индексы
        for(unsigned i=1;i<table->sizeCol;i++)
        {
            if(table->m[i]>=X)
            {
                indexCol=i;
                break;
            }
        }
    }
    if(indexRow==-1)
    {
        //! вычислим индексы
        for(unsigned i=0;i<table->sizeRow;i++)
        {
            if(table->m[i*table->sizeCol]>=Y)
            {
                indexRow=i;
                break;
            }
        }
    }
    indexRow=limitMinMax(indexRow-1,1,(int)(table->sizeRow-2));
    indexCol=limitMinMax(indexCol-1,1,(int)(table->sizeCol-1));

    y1=rowInterpolation(X,table->m,table->sizeCol,indexCol+1,indexRow);
    y2=rowInterpolation(X,table->m,table->sizeCol,indexCol+1,indexRow+1);

    return linearInterpolation(Y,y2,y1,table->m[table->sizeCol*(indexRow+1)],table->m[table->sizeCol*indexRow]);

}
//double linearInter2DTable(double X,double Y,boost::multi_array<double, 2> A,int indexRow,int indexCol)
//{

//}

void calcVFromTracToEarth(const double tetta_,const double fi_,const double vg_,double &vxg_,double &vyg_,double &vzg_)
{
    vxg_=vg_*cos(tetta_)*cos(fi_);
    vyg_=vg_*sin(tetta_);
    vzg_=-vg_*cos(tetta_)*sin(fi_);
}

//! определение двух углов направления вектора заданного в земной системе координат
void earthTo2Angles(glm::vec3 inVec,TAngle *anglesVec)
{
    //! Нормируем вектор D, т.е. и находим единичный вектор D0;
    double length=glm::length(inVec);

    double D0x1,D0y1,D0z1;

    D0x1=inVec.x/length;
    D0y1=inVec.y/length;
    D0z1=inVec.z/length;

    //double d=D0x1*D0x1+D0y1*D0y1+D0z1*D0z1;
    //Находим выражения компонент единичного вектора   через углы sigma, tau

    double sigma,tau;

    sigma=atan2(D0z1,D0x1);
    checkSigma(sigma,D0x1,D0z1);
    tau=asin(D0y1);

    anglesVec->sigma=sigma;
    anglesVec->tau=tau;
}

//! расчет углов поворота головы относительно контейнера
void calcAgnleRotateHead(glm::vec3 &vecAircraft,     /* вектор на центр самолета относительно земли*/
                         glm::vec3 &vecDevice,       /* вектор на центр устройства(контейнера) относит. самолета*/
                         glm::vec3 &vecOnHead,       /* вектор на головку относительно центра контейнера*/
                         glm::vec3 &vecTarget,       /* вектор на цель(точка привязки) относительно земли*/
                         glm::mat3 &matrixAircraft,  /* матрица поворота самолета относительно земли*/
                         glm::mat3 &matrixDevice,    /* матрица поворота устройства относ. самолета*/
                         TAngle &angle,               /* углы поворота головы контейнера на цель tau=(-90;90) sigma=(-180;180)*/
                         TAngle &angleNeg             /* углы поворота головы контейнера на цель tau=(-180;180) sigma=(-90;90)*/)
{
    // вектор расположения головки относительно контейнера
    glm::vec3 vecDeviceHead(0.0,0.0,0.0);
    vecDeviceHead=vecDevice+vecOnHead;
    // результирующая матрица поворота
    glm::mat3 matrixDevice_Aircraft=matrixAircraft*matrixDevice;
    //Вычисляем компоненты вектора смещения deltaRxdD   относительно связанной СК устройства
    glm::vec3 vecDeltaRxdD=matrixDevice*vecDeviceHead;

    //Вычисляем компоненты вспомогательного вектора deltaRp  относительно полигонной СК
    glm::vec3 vecDeltaRxp=vecTarget-vecAircraft;

    //Вычисляем компоненты вспомогательного вектора deltaRd  относительно связанной СК устройства
    glm::vec3 vecDeltaRxd=vecDeltaRxp*matrixDevice_Aircraft;

    //Вычисляем компоненты вектора дальности Dt  относительно связанной СК устройства
    glm::vec3 vecDt=vecDeltaRxd-vecDeltaRxdD;
    //Длина вектора
    double Dt=glm::length(vecDt);
    //Вычисляем углы
    angle.sigma=-atan2(vecDt.z,vecDt.x);
    angle.tau=asin(vecDt.y/Dt);
    //вычисляем другую пару углов
    angleNeg.sigma=-asin(vecDt.z/Dt);
    angleNeg.tau=atan2(vecDt.y,vecDt.x);
}
//! вычисление углов поворота относительно земли(нужно для индикации камеры)
void calcAngleRotateHeadEarth(glm::vec3 &vecAircraft,   /*вектор на центр самолета относительно земли*/
                              glm::vec3 &vecDevice,     /*вектор на центр устройства(контейнера) относит. самолета*/
                              glm::vec3 &vecOnHead,     /*вектор на головку относительно центра контейнера*/
                              glm::vec3 &vecTarget,     /*вектор на цель(точка привязки) относительно земли*/
                              glm::mat3 &matrixAircraft,/*матрица поворота самолета относительно земли*/
                              TAngle &angle              /*углы поворота головы контейнера на цель*/)
{
    // вектор расположения головки относительно контейнера
    glm::vec3 vecDeviceHead=vecDevice+vecOnHead;

    //Вычисляем компоненты вектора смещения delta_r_d  относительно полигонной СК
    glm::mat3 tempMatrix=glm::transpose(matrixAircraft);
    glm::vec3 vecDeltaRdp=vecDeviceHead*tempMatrix;

    //Вычисляем компоненты вектора дальности Dt  относительно полигонной СК
    glm::vec3 vecDtp=vecTarget-vecAircraft-vecDeltaRdp;

    //Длина вектора
    double Dt=glm::length(vecDtp);

    //Вычисляем углы
    angle.sigma=-atan2(vecDtp.z,vecDtp.x);
    angle.tau=asin(vecDtp.y/Dt);

//    glm::mat3 tempMatrix1=matrixAircraft*matrixHeadOnAircraft;
//    glm::mat3 tempMatrix2=tempMatrix1*matrixSigmaTau;

//    //! определяем третий угол(поворот вокруг оси)
//    angle_tek_target_mu=atan2(tempMatrix2.x[2][1],tempMatrix2.x[1][1]);
}
//! симуляция движения АСП попадание в любую движущуюся цель
// координаты и скорости заданы относительно земли
void simTrajASP(glm::vec3 s0,       /*координаты АСП в начальный момент времени*/
                glm::vec3 v0,       /*компоненты вектора скорости в начальный момент*/
                glm::vec3 e0,       /*координаты цели(конечная точка падения АСП)*/
                double T,           /*время движения АСП(общее)*/
                double E,           /*среднее значение функции сопротивления АСП*/
                double t,           /*текущее значение времени*/
                glm::vec3 &v,       /*Текущие компоненты скорости АСП-выходная переменная*/
                glm::vec3 &coord    /*Текущие координаты АСП-выходная переменная*/
               )
{
    glm::vec3 p;//управляющий импульс

    double temp1=exp(-E*T);
    double temp2=1.0-temp1;
    double temp3=T-temp2/E;

    double temp4=exp(-E*t);
    double temp5=1.0-temp4;


    //! в векторном виде
    p=(E*(e0-s0)-v0*temp2)/temp3;
    v=p/E+(v0-p/E)*temp4;
    coord=s0+p*t/E+(1/E)*(v0-p/E)*temp5;
}

//! rVectorOut - ; rVectorTo -
/*TPoint convertToStartAircraft(TPoint rVectorOut, TPoint rVectorTo)
{
    TPoint startAircraft;

    startAircraft.x=rVectorTo.x+rVectorOut.x;
    startAircraft.y=rVectorTo.y+rVectorOut.y;
    startAircraft.z=rVectorTo.z+rVectorOut.z;

    return startAircraft;
}*/

//! метод Рунге-Кутты 4 порядка
/*double* rk41(short nsdu, double d,double *fb, double *SDU(double f[]))
{
    short i,j;
    double df[10][10];

    static double  f[10];
    double *fout;
    for(j = 0; j < 4; j++)
    {
        if(j==0) fout=SDU(fb);
        else fout=SDU(f);

        for(i = 0; i < nsdu; i++)
        {
            df[i][j] = fout[i] *d;
            switch(j)
            {
            case 0:{f[i] = fb[i] + 0.5 * df[i][j];break;}
            case 1:{f[i] = fb[i] + 0.5 * df[i][j];break;}
            case 2:{f[i] = fb[i] + df[i][j];break;}
            case 3:{f[i] = fb[i]+(df[i][0]+2.0*(df[i][1]+df[i][2])+df[i][3])/6.0;}
            }
        }
    }
    return f;
}*/

glm::vec3 aerodToC_c(glm::vec3 C_a,double alfa,double beta)
{
    glm::vec3 C_c;

    C_c.x=C_a.x*cos(alfa)*cos(beta) - C_a.y*sin(alfa) - C_a.z*cos(alfa)*cos(beta);
    C_c.y=C_a.x*sin(alfa)*cos(beta) + C_a.y*cos(alfa) - C_a.z*sin(alfa)*sin(beta);
    C_c.z=C_a.x*sin(beta) + C_a.z*cos(beta);

    return C_c;
}

double checkZero(double x)//отрезать дробную чпсть
{
    if(fabs(x)<1e-30) return 0.0;
    return x;
}
bool checkValue(double value, double cur,double acc)
{
    if(fabs(cur-value)<=acc)
        return true;
    else
        return false;
}

double signF(double num,double s)
{
    if(s>0.0) num=fabs(num);
    else if(s<0.0)num=-fabs(num);
    return num;
}
double signF(double num)
{
    if(num>=0.0) return 1.0;
    return -1.0;
}
double asinh(double x)
{
    return log(x+sqrt(x*x+1));
}
double sigmoid(double x)
{
    return ((1.0/(1.0+exp(-fabs(x))))-0.5);
}
double normValue(double x)
{
    if(x<-1.0) return -1.0;
    if(x>1.0) return 1.0;
    return x;
}
double ugol_ogrMPI_toMPI(double value)
{
    return value-2.0*M_PI*signF(value);
}
double gradToRadian(double x)
{
    return (x*M_PI)/180.0;
}
double radianToGrad(double x)
{
     return (x*180)/M_PI;
}
TAngle radianToGrad(TAngle angl)
{
    TAngle a;
    a.sigma=radianToGrad(angl.sigma);
    a.tau=radianToGrad(angl.tau);

    return a;
}
TAngle gradToRadian(TAngle angl_grad)
{
    TAngle a;
    a.sigma=gradToRadian(angl_grad.sigma);
    a.tau=gradToRadian(angl_grad.tau);

    return a;
}
double kmToMeter(double x)
{
   return x/3.6;
}
double meterToKm(double x)
{
    return x*3.6;
}
//! проверка выхода за [180;-180]
double checkPI(double angle/*в рад*/)
{
    if(angle>M_PI) angle+=-2.0*M_PI;
    else if(angle<-M_PI)angle+=2.0*M_PI;
    return angle;
}
//! проверка выхода за [0;-360]
double check2PI(double angle/*в рад.*/)
{
    if(angle>(2.0*M_PI)) angle-=2.0*M_PI;
    else if(angle<0.0)angle+=2.0*M_PI;
    return angle;
}
//! проверка выхода за [180;-180]
double check180(double angle/*в град*/)
{
    if(angle>180.0) angle+=-2.0*180.0;
    else if(angle<-180.0)angle+=2.0*180.0;
    return angle;
}
//! проверка выхода за [0;-360]
double check360(double angle/*в град.*/)
{
    if(angle>(2.0*180.0)) angle-=2.0*180.0;
    else if(angle<0.0)angle+=2.0*180.0;
    return angle;
}
double psiToKurs(double psi_)
{
    psi_=-psi_;
    double kurs_=psi_;
    if(psi_<0.0) kurs_=2*M_PI+psi_;
    return kurs_;
}

double kursToPsi(double kurs)
{
    double psi=kurs;
    if(kurs>M_PI) psi=psi-2.0*M_PI;
    psi=-psi;

    return psi ;
}
bool compareMems(char *dst, char *src,int size)
{
    bool equal = true;
    //! сравниваем две структуры
    for(int i = 0; i < size; i++)
    {
        if(dst[i] != src[i])
        {
            //! структуры не равны
            equal = false;
            break;
        }
    }
    return equal;
}
//! преобразование из земной СК в горизонтированную самолетную СК
void convertEarthToGorizontAircraft(glm::vec3 inAircraft,
                                    glm::mat3 matrixPsi,
                                    glm::vec3 inPoint,
                                    glm::vec3 &outPointGor)
{
    //! относительно самолета
    outPointGor=(inPoint-inAircraft)*matrixPsi;
    //outPointGor=matrixPsi*outPointGor;
}

//! преобразование из горизонтированной самолетной СК в земную СК
void convertGorizontAircraftToEarth(glm::vec3 inPointGor,
                                    glm::vec3 inAircraft,
                                    glm::mat3 matrixPsi,
                                    glm::vec3 &outPointEarth)
{
    outPointEarth=inAircraft+(inPointGor*glm::transpose(matrixPsi));
}
void convertGorizontAircraftToEarth(glm::vec3 inPointGor,
                                    glm::mat3 matrixPsi,
                                    glm::vec3 &outPointEarth)
{
    outPointEarth=inPointGor*glm::transpose(matrixPsi);
}
//! обертка преобразование географических в декартовые
void convertGeoToDekart(double lambda0,double fi0,
                        double lambda,double fi,
                        double &x,double &z)
{
#ifdef USE_SPHERE
    convertSphereToDekart(lambda0,fi0,lambda,fi,x,z);
#endif
#ifdef USE_MODEL_H
    LatLon2DxDz(x,
    z,
    (fi),
    (lambda),
    (fi0),
    (lambda0));
#endif
#ifdef USE_GAUSS_KRUGGER
     convertBLtoXY(radianToGrad(fi),radianToGrad(lambda),x,z);
#endif
}

//! обертка преобразование географических в декартовые
void convertDekartToGeo(double lambda0,double fi0,
                        double x,double z,
                        double &lambda,double &fi)
{
#ifdef USE_SPHERE
        convertDekartToSphere(lambda0,
                              fi0,
                              x,
                              z,
                              lambda,
                              fi);
#endif
#ifdef USE_MODEL_H

        DxDz2LatLon(x,
        z,
        fi,
        lambda,
        fi0,
        lambda0
        );


#endif
#ifdef USE_GAUSS_KRUGGER
     convertXYtoBL(x,z,fi,lambda);
     fi=gradToRadian(fi);
     lambda=gradToRadian(lambda);
#endif
}

//! Преобразование сферических в декартовы
void convertSphereToDekart(double lambda0,double fi0,
                           double lambda,double fi,
                           double &x,double &z)
{

    glm::mat3 Alambda0;
    double cosLambda0=cos(lambda0);
    double sinLambda0=sin(lambda0);

    Alambda0[0][0]=1.0;
    Alambda0[0][1]=0.0;
    Alambda0[0][2]=0.0;

    Alambda0[1][0]=0.0;
    Alambda0[1][1]=cosLambda0;
    Alambda0[1][2]=sinLambda0;

    Alambda0[2][0]=0.0;
    Alambda0[2][1]=-sinLambda0;
    Alambda0[2][2]=cosLambda0;
    /////////////////////////////////////////////////////

    glm::mat3 Afi0;
    double cosfi0=cos(fi0);
    double sinfi0=sin(fi0);

    Afi0[0][0]=cosfi0;
    Afi0[0][1]=-sinfi0;
    Afi0[0][2]=0.0;

    Afi0[1][0]=sinfi0;
    Afi0[1][1]=cosfi0;
    Afi0[1][2]=0.0;

    Afi0[2][0]=0.0;
    Afi0[2][1]=0.0;
    Afi0[2][2]=1.0;
    /////////////////////////////////////////////////////
    glm::mat3 AsG=Alambda0*Afi0;
    ////////////////////////////////////////////////////

    glm::mat3 AgG;

    double cosfi=cos(fi);
    double sinfi=sin(fi);
    double cosLambda=cos(lambda);
    double sinLambda=sin(lambda);

    AgG[0][0]=cosfi;
    AgG[0][1]=-sinfi*cosLambda;
    AgG[0][2]=-sinfi*sinLambda;

    AgG[1][0]=sinfi;
    AgG[1][1]=cosfi*cosLambda;
    AgG[1][2]=cosfi*sinLambda;

    AgG[2][0]=0.0;
    AgG[2][1]=-sinLambda;
    AgG[2][2]=cosLambda;

    //glm::mat3 tempAsG=glm::transpose(AsG);
    glm::mat3 Asg=glm::transpose(AsG)*AgG;

    double tetta=asin(Asg[1][0]);
    double psi=atan2(Asg[1][2],Asg[1][1]);

    x=6356767.0*tetta; z=6356767.0*psi;

}
#define _R_ZEML_EKV   6378137.0
#define _R_ZEML_POL   6356752.0
//! Преобразование декартовых в сферические
//! положение стартовой СК относительно земной СК
//!                                             -lambda
//!                                             -fi

//! Декартовы координаты объекта относительно стартовой СК
//!                                             -x
//!                                             -z
void convertDekartToSphere(double lambda0,double fi0,
                           double x,double z,
                           double &lambda,double &fi)
{
    glm::mat3 Alambda0;
    double cosLambda0=cos(lambda0);
    double sinLambda0=sin(lambda0);

    Alambda0[0][0]=1.0;
    Alambda0[0][1]=0.0;
    Alambda0[0][2]=0.0;

    Alambda0[1][0]=0.0;
    Alambda0[1][1]=cosLambda0;
    Alambda0[1][2]=sinLambda0;

    Alambda0[2][0]=0.0;
    Alambda0[2][1]=-sinLambda0;
    Alambda0[2][2]=cosLambda0;
    /////////////////////////////////////////////////////

    glm::mat3 Afi0;
    double cosfi0=cos(fi0);
    double sinfi0=sin(fi0);

    Afi0[0][0]=cosfi0;
    Afi0[0][1]=-sinfi0;
    Afi0[0][2]=0.0;

    Afi0[1][0]=sinfi0;
    Afi0[1][1]=cosfi0;
    Afi0[1][2]=0.0;

    Afi0[2][0]=0.0;
    Afi0[2][1]=0.0;
    Afi0[2][2]=1.0;
    /////////////////////////////////////////////////////
    glm::mat3 AsG=Alambda0*Afi0;
    ////////////////////////////////////////////////////
    double tetta=x/6356767.0;
    double psi=z/6356767.0;

    glm::mat3 Atetta;
    double cosTetta=cos(tetta);
    double sinTetta=sin(tetta);

    Atetta[0][0]=cosTetta;
    Atetta[0][1]=-sinTetta;
    Atetta[0][2]=0;

    Atetta[1][0]=sinTetta;
    Atetta[1][1]=cosTetta;
    Atetta[1][2]=0.0;

    Atetta[2][0]=0.0;
    Atetta[2][1]=0.0;
    Atetta[2][2]=1.0;


    glm::mat3 Apsi;

    double cosPsi=cos(psi);
    double sinPsi=sin(psi);

    Apsi[0][0]=1.0;
    Apsi[0][1]=0.0;
    Apsi[0][2]=0.0;

    Apsi[1][0]=0.0;
    Apsi[1][1]=cosPsi;
    Apsi[1][2]=sinPsi;

    Apsi[2][0]=0.0;
    Apsi[2][1]=-sinPsi;
    Apsi[2][2]=cosPsi;

    glm::mat3 tempMatrix=AsG*Atetta;
    glm::mat3 AgG=tempMatrix*Apsi;

    fi=asin(AgG[1][0]);
    lambda=atan2(AgG[1][2],AgG[1][1]);

}
void sgfToEarthDirectionVec(TAngle inAngleSGF,glm::vec3 inAircraft,glm::mat3 &inMatrixAircraft,glm::vec3 *outDirectionVec)
{
    Q_UNUSED(inAircraft);
    //===================================================
    glm::mat3 matrixSigma, matrixTau;

    matrixSigma[0][0]=cos(inAngleSGF.sigma);
    matrixSigma[0][1]=0.0;
    matrixSigma[0][2]=-sin(inAngleSGF.sigma);

    matrixSigma[1][0]=0.0;
    matrixSigma[1][1]=1.0;
    matrixSigma[1][2]=0.0;

    matrixSigma[2][0]=sin(inAngleSGF.sigma);
    matrixSigma[2][1]=0.0;
    matrixSigma[2][2]=cos(inAngleSGF.sigma);
    //===================================================

    matrixTau[0][0]=cos(inAngleSGF.tau);
    matrixTau[0][1]=sin(inAngleSGF.tau);
    matrixTau[0][2]=0.0;

    matrixTau[1][0]=-sin(inAngleSGF.tau);
    matrixTau[1][1]=cos(inAngleSGF.tau);
    matrixTau[1][2]=0.0;

    matrixTau[2][0]=0.0;
    matrixTau[2][1]=0.0;
    matrixTau[2][2]=1.0;

    //! результирующая матрица поворота
    glm::mat3 matrixResultRotate;
    glm::mat3 tempMatrix;

    tempMatrix=matrixSigma*inMatrixAircraft;
    matrixResultRotate=matrixTau*tempMatrix;

    double D0xg,D0yg,D0zg;

    D0xg=matrixResultRotate[0][0];
    D0yg=matrixResultRotate[0][1];
    D0zg=matrixResultRotate[0][2];

    /*double u=-inAircraft.y/D0yg;

    outDirectionVec->x=inAircraft.x+u*D0xg;
    outDirectionVec->y=inAircraft.y+u*D0yg;
    outDirectionVec->z=inAircraft.z+u*D0zg;*/

    outDirectionVec->x=D0xg;
    outDirectionVec->y=D0yg;
    outDirectionVec->z=D0zg;
}

//! преобразование точки(в земной системе кординат) в координаты КАИ(два угла относительно строительной оси)
void earthToSGF(const glm::vec3 &inCoord,const glm::vec3 &inAircraft, const glm::mat3 &inMatrixAircraft,  TAngle *outAngleSGF)
{
    double Dxg,Dyg,Dzg;

    Dxg=(inCoord.x)-(inAircraft.x);
    Dyg=(inCoord.y)-(inAircraft.y);
    Dzg=(inCoord.z)-(inAircraft.z);

    //! Находим компоненты вектора D  относительно связанной системы координат
    double Dx1,Dy1,Dz1;
    Dx1=Dxg*inMatrixAircraft[0][0]+Dyg*inMatrixAircraft[0][1]+Dzg*inMatrixAircraft[0][2];
    Dy1=Dxg*inMatrixAircraft[1][0]+Dyg*inMatrixAircraft[1][1]+Dzg*inMatrixAircraft[1][2];
    Dz1=Dxg*inMatrixAircraft[2][0]+Dyg*inMatrixAircraft[2][1]+Dzg*inMatrixAircraft[2][2];

    /*Dx1=Dxg*inMatrixAircraft.x[0][0]+Dyg*inMatrixAircraft.x[1][0]+Dzg*inMatrixAircraft.x[2][0];
    Dy1=Dxg*inMatrixAircraft.x[0][1]+Dyg*inMatrixAircraft.x[1][1]+Dzg*inMatrixAircraft.x[2][1];
    Dz1=Dxg*inMatrixAircraft.x[0][2]+Dyg*inMatrixAircraft.x[1][2]+Dzg*inMatrixAircraft.x[2][2];*/

   // glm::vec3 vec=inMatrixAircraft*
   /* Dx1=Dxg*inMatrixAircraft.x[0][0]+Dyg*inMatrixAircraft.x[1][0]+Dzg*inMatrixAircraft.x[2][0];
    Dy1=Dxg*inMatrixAircraft.x[0][1]+Dyg*inMatrixAircraft.x[1][1]+Dzg*inMatrixAircraft.x[2][1];
    Dz1=Dxg*inMatrixAircraft.x[0][2]+Dyg*inMatrixAircraft.x[1][2]+Dzg*inMatrixAircraft.x[2][2];*/


    //! Нормируем вектор D, т.е. и находим единичный вектор D0;
    double length=sqrt(Dx1*Dx1+Dy1*Dy1+Dz1*Dz1);

    double D0x1,D0y1,D0z1;
    D0x1=Dx1/length;
    D0y1=Dy1/length;
    D0z1=Dz1/length;
    //double d=D0x1*D0x1+D0y1*D0y1+D0z1*D0z1;
    //Находим выражения компонент единичного вектора   через углы sigma, tau

    double sigma,tau;

    sigma=atan2(D0z1,D0x1);
    checkSigma(sigma,D0x1,D0z1);
    tau=asin(D0y1);

    outAngleSGF->sigma=sigma;
    outAngleSGF->tau=tau;
}
double dTo(glm::vec3 &vecBegin,glm::vec3 &vecEnd)
{
    return (glm::length(vecEnd)-glm::length(vecBegin));
}
//! преобразование двух углов(относительно СГФ) в прямую заданную параметрическим способом
void sgfToEarth(const TAngle &inAngleSGF,const glm::vec3 &inAircraft,const glm::mat3 &inMatrixAircraft,const double &dH,glm::vec3 *outCoord)
{
    //===================================================
    glm::mat3 matrixSigma, matrixTau;

    double cosSigma=cos(inAngleSGF.sigma);
    double sinSigma=sin(inAngleSGF.sigma);
    matrixSigma[0][0]=cosSigma;
    matrixSigma[0][1]=0.0;
    matrixSigma[0][2]=-sinSigma;

    matrixSigma[1][0]=0.0;
    matrixSigma[1][1]=1.0;
    matrixSigma[1][2]=0.0;

    matrixSigma[2][0]=sinSigma;
    matrixSigma[2][1]=0.0;
    matrixSigma[2][2]=cosSigma;
    //===================================================
    double cosTau=cos(inAngleSGF.tau);
    double sinTau=sin(inAngleSGF.tau);

    matrixTau[0][0]=cosTau;
    matrixTau[0][1]=sinTau;
    matrixTau[0][2]=0.0;

    matrixTau[1][0]=-sinTau;
    matrixTau[1][1]=cosTau;
    matrixTau[1][2]=0.0;

    matrixTau[2][0]=0.0;
    matrixTau[2][1]=0.0;
    matrixTau[2][2]=1.0;

    //! результирующая матрица поворота
    glm::mat3 matrixResultRotate;
    glm::mat3 tempMatrix;

    tempMatrix=inMatrixAircraft*matrixSigma;
    matrixResultRotate=tempMatrix*matrixTau;

    double D0xg,D0yg,D0zg;

    //! направляющий вектор о
    D0xg=matrixResultRotate[0][0];
    D0yg=matrixResultRotate[0][1];
    D0zg=matrixResultRotate[0][2];

    //double d=D0xg*D0xg+D0yg*D0yg+D0zg*D0zg;
    //if(d>1.0) qDebug("Error in NASP code: function=sgfToEarth, vector!=1.0\n");

    //double u=-inAircraft.y/D0yg;
    double u=(dH-inAircraft.y)/D0yg;

    outCoord->x=inAircraft.x+u*D0xg;
    outCoord->y=inAircraft.y+u*D0yg;
    outCoord->z=inAircraft.z+u*D0zg;
}
void intersectPlaneAndLine(glm::vec3 &inVec,glm::vec3 dVec,double &hPlane,glm::vec3 &intersectDot)
{
    double u=(hPlane-inVec.y)/dVec.y;

    intersectDot.x=inVec.x+u*dVec.x;
    intersectDot.y=inVec.y+u*dVec.y;
    intersectDot.z=inVec.z+u*dVec.z;
}

void checkSigma(double &sigma,double D0x1, double D0z1)
{
    if(D0x1>0.0) sigma=-atan(D0z1/D0x1);

    if(fabs(D0x1)<EPS && D0z1>0.0) sigma=-M_PI/2.0;
    if(fabs(D0x1)<EPS && D0z1<0.0) sigma=M_PI/2.0;

    if(D0x1<0.0 && D0z1>0.0) sigma=-atan(D0z1/D0x1)-M_PI;
    if(D0x1<0.0 && D0z1<0.0) sigma=-atan(D0z1/D0x1)+M_PI;



    /*if(fabs(D0z1)<EPS && D0x1>0.0) sigma=0.0;
    if(D0z1==0.0 && D0x1<0.0) sigma=M_PI;//+-M_PI*/
}
glm::mat3 calcTAngleMatrix(TAngle angle)
{
    //===================================================
    glm::mat3 matrixSigma, matrixTau;

    matrixSigma[0][0]=cos(angle.sigma);
    matrixSigma[0][1]=0.0;
    matrixSigma[0][2]=-sin(angle.sigma);

    matrixSigma[1][0]=0.0;
    matrixSigma[1][1]=1.0;
    matrixSigma[1][2]=0.0;

    matrixSigma[2][0]=sin(angle.sigma);
    matrixSigma[2][1]=0.0;
    matrixSigma[2][2]=cos(angle.sigma);
    //===================================================

    matrixTau[0][0]=cos(angle.tau);
    matrixTau[0][1]=sin(angle.tau);
    matrixTau[0][2]=0.0;

    matrixTau[1][0]=-sin(angle.tau);
    matrixTau[1][1]=cos(angle.tau);
    matrixTau[1][2]=0.0;

    matrixTau[2][0]=0.0;
    matrixTau[2][1]=0.0;
    matrixTau[2][2]=1.0;

    //! результирующая матрица поворота

    glm::mat3 tempMatrix;


    tempMatrix=matrixTau*matrixSigma;
    return tempMatrix;
}
//! чтение данных в 2D таблицу
/*void readDataToMatrix(const QDomElement& root, const QString& nameMatrix,TTable2D &pM)
{
    QDomElement ele=root.firstChildElement(nameMatrix);
    pM.sizeCol=ele.firstChildElement("size_cols").text().toInt();
    pM.sizeRow=ele.firstChildElement("size_rows").text().toInt();
    pM.m=new double [pM.sizeCol*pM.sizeRow];

    QDomElement row=ele.firstChildElement("row");
    QDomElement column;
    int indexRow=0;
    int indexCol=0;
    do{
        column=row.firstChildElement("column");
        indexCol=0;
        do
        {
            pM.m[indexRow*pM.sizeCol+indexCol]=column.firstChildElement("value").text().toDouble();
            column=column.nextSiblingElement("column");
            indexCol++;
        }while(column.isNull()==false);
        row=row.nextSiblingElement("row");
        indexRow++;
    }while(row.isNull()==false);
}
//! чтение данных в 2D таблицу
void readDataToVector(const QDomElement& root, const QString& nameVector,TTable1D &pM)
{
    QDomElement ele=root.firstChildElement(nameVector);
    pM.sizeCol=ele.firstChildElement("size_cols").text().toInt();
    pM.sizeRow=2;
    pM.m=new double [pM.sizeCol*pM.sizeRow];

    QDomElement row=ele.firstChildElement("row");
    QDomElement column;
    int indexRow=0;
    int indexCol=0;
    do{
        column=row.firstChildElement("column");
        indexCol=0;
        do
        {
            pM.m[indexRow*pM.sizeCol+indexCol]=column.firstChildElement("value").text().toDouble();
            column=column.nextSiblingElement("column");
            indexCol++;
        }while(column.isNull()==false);
        row=row.nextSiblingElement("row");
        indexRow++;
    }while(indexRow<2);
}*/
//! Апериодический фильтр
FilterAperiodic::FilterAperiodic(double valueStart_,double k_,double step_,double maxValue_, double minValue_)
{
    k=k_;
    step=step_;
    maxValue=maxValue_;
    minValue=minValue_;
    value=valueStart_;
    valueStart=valueStart_;
    valueCurrent=valueStart;
}
//! сброс фильтра (задать текущее значение фильтра)
void FilterAperiodic::resetFilter(double valueStart_)
{
    value=valueStart_;
}
//! возврат текущего значения фильтра
double FilterAperiodic::filterValue(double valueCurr)
{
    value=value+(k*checkZero(valueCurr-value)*step);
    value = limitMinMax(value,minValue,maxValue);
    return value;
}
void FilterAperiodic::setK(double k_)
{
    k=k_;
}
//! обновление фильтра(с заданной частотой)
void FilterAperiodic::refresh()
{
    value=value+(k*checkZero(valueCurrent-value)*step);
    value=limitMinMax(value,minValue,maxValue);
}
//! установка текущего значения фильтра
double FilterAperiodic::setFilterValue(double v)
{
    valueCurrent=v;
    return value;
}
//! Апериодический фильтр
FiltersAperiodicAngle::FiltersAperiodicAngle(TAngle valueStart_,double k_,double step_,double maxValue_, double minValue_)
{
    filterSigma=new FilterAperiodic(valueStart_.sigma,k_,step_,maxValue_,minValue_);
    filterTau=new FilterAperiodic(valueStart_.tau,k_,step_,maxValue_,minValue_);
}
//! сброс фильтра
void FiltersAperiodicAngle::resetFilter(TAngle valueStart_)
{
    filterSigma->resetFilter(valueStart_.sigma);
    filterTau->resetFilter(valueStart_.tau);
}
//! установка текущего значения фильтра
TAngle FiltersAperiodicAngle::filterValue(TAngle valueCurr)
{
    TAngle angl(0.0,0.0);
    angl.sigma=filterSigma->filterValue(valueCurr.sigma);
    angl.tau=filterTau->filterValue(valueCurr.tau);

    return angl;
}
//! обновление фильтра(с заданной частотой)
void FiltersAperiodicAngle::refresh()
{
    filterSigma->refresh();
    filterTau->refresh();
}

//! возврат текущего значения фильтра
TAngle FiltersAperiodicAngle::setFilterValue(TAngle currentValue)
{
    return currentValue;
}

//! задать коэффициент при звене
void FiltersAperiodicAngle::setK(double k_)
{
    filterSigma->setK(k_);
    filterTau->setK(k_);
}

VPid::VPid(double proportional, double integral, double differential,
           double period, double minSaturation, double maxSaturation)
    : m_proportional(proportional),
      m_integral(integral),
      m_differential(differential),
      m_period(period),
      m_minSaturation(minSaturation),
      m_maxSaturation(maxSaturation)
{
    m_lastResult = m_lastInput = 0;
}

double VPid::getValue(double input)
{
    double sum = m_lastResult + m_integral * m_period * input;
    double diff = m_differential / m_period * (input - m_lastInput);
    double result = m_proportional * input + sum + diff;

    result=limitMinMax(result,m_minSaturation,m_maxSaturation);

    m_lastResult = sum;
    m_lastInput = input;

    return result;
}


//! формирование  кода для СТК датчика по углу  Fi, рад
unsigned short int CTKofFi(float  Fi/*рад*/)
{
    float  Fim,C,S,t;
    short int  K,OKT,F;

    Fim=fabs(Fi);
    S=sin(Fim);
    C=cos(Fim);

    if (C >=S)
    {
        t=S/C;
        OKT=0;
    }
    else
    {
        t=C/S;
        OKT=0x4000;
    }

    F=(int)(Fi*0x2000);
    K=(short int)(t*0x4000 +2);

    if (K>=0x4000)
        K=0x3ffc;

    return   (K | OKT |(F &0x8000));
}
void WGS84LatLon2DxDz(double lat1, double lon1, double lat2, double lon2,
            double& DXkm, double& DZkm, double& PSKgrad, double& Dkm)
{
    //a length of major axis of the ellipsoid (radius at equator) (6,378,137.0 metres in WGS-84)
    //b length of minor axis of the ellipsoid (radius at the poles) (6,356,752.314 metres in WGS-84)
    //? = (a ? b)/a flattening of the ellipsoid (1/298.257 in WGS-84)
    //?1, ?2 latitude of the points
    //U1 = arctan[(1 ? ?) tan ?1],
    //U2 = arctan[(1 ? ?) tan ?2] reduced latitude
    //?1, ?2 longitude of the points
    //L = ?2 ? ?1 difference in longitude
    //?1, ?2 forward and reverse azimuths
    //s ellipsoidal distance between the two points

    /*
     *   Name           Major axis, a (km)    Flattening (f)
     *   WGS84          6378.13700	   1/298.257223563
     *   GRS80/NAD83    6378.13700	   1/298.257222101
     *   WGS66          6378.145            1/298.25
     *   GRS67/IAU68    6378.16000          1/298.2472
     *   WGS72          6378.135            1/298.26
     *   Krasovsky      6378.245            1/298.3
     *   Clarke66/NAD27 6378.2064           1/294.9786982138
  */

    const double min_error = 0.000000001;
    const double a = 6378137.0;
  const double b = 6356752.314;
  double f = (a-b)/a;
  f = 1.0/298.257223563;   //f=1-f;

  double L   = lon2-lon1;
  if ( fabs(lon2 - lon1) < min_error )
    L = lon2 - lon1 + 2*min_error;

  double Lr  = L;
  double lam = L;        //Initial lambda is L, then it is iterative calculated

  double fi1r = lat1;
  //double la1r = lon1;
  double fi2r = lat2;
  //double la2r = lon2;

  double U1 = atan((1-f)*tan(fi1r));
  double U2 = atan((1-f)*tan(fi2r));

  double lam_old = L;
  int i = 0; double cos2alfa = 0; double sin_sigm = 0; double cos_sigm = 0;
  double sigma = 0; double cos2sigmm = 0;
  double cU1 = cos(U1); double cU2 = cos(U2);
  double sU1 = sin(U1); double sU2 = sin(U2);
  double sLam = 0; double cLam = 0;;
  while( (fabs(lam_old - lam) > min_error) && (i<100) )
  {
    sLam = sin(lam);
    cLam = cos(lam);
    double s1 = cU2*sLam; s1 *= s1;
    double s2 = cU1*sU2-sU1*cU2*cLam; s2 *= s2;
    sin_sigm = sqrt(s1 + s2);
    cos_sigm = sU1*sU2 + cU1*cU2*cLam;

    if(sin_sigm == 0) return;

    sigma = atan2(sin_sigm,cos_sigm);
    double sin_alfa = cU1*cU2*sLam/sin_sigm;
    cos2alfa = 1 - sin_alfa*sin_alfa;
    cos2sigmm = cos_sigm - 2*sU1*sU2/cos2alfa;
    double C = (f/16)*cos2alfa*(4+f*(4-3*cos2alfa));

    lam_old = lam;
    lam = Lr+(1-C)*f*sin_alfa*(sigma
          + C*sin_sigm*(cos2sigmm+C*cos_sigm*(-1+2*cos2sigmm*cos2sigmm)));
    i++;
  }


  double uu2 = cos2alfa*((a*a-b*b)/(b*b));
  double A = 1+uu2/16384.0 * (4096.0 + uu2*(-768.0+uu2*(320.0-175.0*uu2)));
  double B = (uu2/1024.0)*(256+uu2*(-128.0+uu2*(74.0-47.0*uu2)));
  double dSigma = B*sin_sigm*(cos2sigmm+0.25*B*(cos_sigm*(-1.0+2.0*cos2sigmm*cos2sigmm)
              - (1.0/6.0)*B*cos2sigmm*(-3.0+4.0*sin_sigm*sin_sigm*(-3.0+4.0*cos2sigmm*cos2sigmm)) ));

  //Outputs
  double S = b*A*(sigma - dSigma);
  Dkm = S*0.001;
  double tet12ir  = atan2(cU2*sLam,(cU1*sU2 - sU1*cU2*cLam));   //Initial bearing P1->P2
  //double tet12igr = tet12ir*_RAD2GRAD;
  double tet12fr  = atan2(cU1*sLam,(-sU1*cU2 + cU1*sU2*cLam));  //Final bearing P1->P2
  PSKgrad = tet12fr;
  DXkm    = Dkm*cos(tet12ir);
  DZkm    = Dkm*sin(tet12ir);
}
double Vpr(double Vms, double Hmeters)
{
    double const Rz = 6371210;
    double const R  = 287.039;
    double const F  = Rz*Hmeters/(Rz+Hmeters);
    double ro_kgs = 0;

    if (Hmeters <= 11000.)
    {
        ro_kgs  =   ( pow(10,(log10(0.12492)-(1+9.80665/(-1.86575))*
        log10((288.15-0.0065*F)*0.003471))) );             //[kg*c**2/m**4]
    }
    else
    {
        double Fz  =   Rz*11000/(Rz+11000);
        ro_kgs     =   ( pow(10,(log10(0.037204)-0.434294*(9.80665/(R*216.66))*(F-Fz))) );
    }

    double q05tek  = ro_kgs*Vms*Vms*0.5;
    double Vpr = sqrt(15.873*q05tek);
    return Vpr;
}
void DxDz2LatLon(double x,double z,
                 double &lat, double &lon,
                 double lat_0,double lon_0 )
{

    //x,z - meters
    double  ceg,seg,k1,k2,k0,a,b,e2,Nyt;
    double  cf0,sf0,Lc,aa,xd,zd,yd,xyt,zyt,yyt;
    double  dla,cdla,sdla;

     cf0=cos(lat_0); sf0=sin(lat_0);
     a=_R_ZEML_EKV; b=_R_ZEML_POL;
     Lc=sqrt(x*x + z*z);
     if(Lc>0.01)
     {
     ceg = x / Lc;
     seg = z / Lc;

     e2 = 1-b*b/(a*a);
     Nyt = a/ sqrt(1 - e2 * sf0*sf0);

     k1 = (1 - e2* sf0 * sf0)/ ((1 - e2)*Nyt);
     k2 = 1/Nyt;
     k0 = k1 *ceg*ceg  + k2 *seg*seg;


     aa =  Lc * k0;

     xd = sin(aa)/k0 * ceg;
     zd = sin(aa)/k0 *seg;
     yd = 1/k0 *(cos(aa)-1);

     xyt = -xd * sf0 +(yd +Nyt)* cf0;
     yyt =  xd * cf0 + (yd + Nyt*(1 - e2))*sf0;
     zyt = zd;

     lon = lon_0 + atan(zyt/xyt);
     dla=lon-lon_0;
     cdla= cos(dla); sdla = sin(dla);

     lat = atan(yyt/((1 - e2)*(xyt*cdla + zyt*sdla)));
     }
     else
     {lat=lat_0;
      lon=lon_0;
     };
}
//------------------------------------------------------------------------------------
void LatLon2DxDz(double &x0,double &z0,
                        double lat, double lon,
                        double lat_0,double lon_0)
{
    double  xd,yd,zd,xyt,yyt,zyt,Nyt,Nc,e2;
    double  cf1,sf1,cf0,sf0,dla,sdla,cdla;
    double a,b;
    double k1,k2,k0,ceg,seg,Lc;

    cf0=cos(lat_0); sf0=sin(lat_0);
    cf1=cos(lat);   sf1=sin(lat);
    dla=lon-lon_0;
    cdla= cos(dla); sdla = sin(dla);
    a=_R_ZEML_EKV; b=_R_ZEML_POL;

    e2 = 1-b*b/(a*a);
    Nyt = a/ sqrt(1 - e2 * sf0*sf0);
    Nc =  a/ sqrt(1 - e2 * sf1*sf1);

    xyt = Nc * cf1 * cdla;
    yyt = Nc*(1-e2)* sf1;
    zyt = Nc*cf1* sdla;

    xd = yyt*cf0 - xyt*sf0 + Nyt*e2*sf0*cf0;
    yd = yyt*sf0 + xyt*cf0 - Nyt*(1-e2*sf0*sf0);
    zd = zyt;

    Lc =sqrt(xd*xd + zd*zd);
    if(Lc>0.01)
    {
        k1 = (1 - e2* sf0 * sf0)/ ((1-e2)*Nyt);
        k2 = 1/Nyt;
        ceg = xd/Lc;
        seg = zd/Lc;
        k0= ceg * ceg * k1 + seg * seg * k2;

        Lc = 2/k0 * asin(k0 * sqrt(xd*xd + yd*yd + zd*zd)/2);
        x0 = Lc * ceg;
        z0 = Lc * seg;
    }
    else
    {x0=0;z0=0;};

        //x0 *= 0.001;    //To km
        //z0 *= 0.001;    //To km
}
//! преобразование точки(в земной системе кординат) в координаты КАИ(два угла относительно строительной оси)
void earthToSGF(const Vector3D_D &inCoord,const Vector3D_D &inAircraft, const Matrix3D_D &inMatrixAircraft,  TAngle *outAngleSGF)
{
    double Dxg,Dyg,Dzg;

    Dxg=(inCoord.x)-(inAircraft.x);
    Dyg=(inCoord.y)-(inAircraft.y);
    Dzg=(inCoord.z)-(inAircraft.z);

    //! Находим компоненты вектора D  относительно связанной системы координат
    double Dx1,Dy1,Dz1;
    Dx1=Dxg*inMatrixAircraft.x[0][0]+Dyg*inMatrixAircraft.x[0][1]+Dzg*inMatrixAircraft.x[0][2];
    Dy1=Dxg*inMatrixAircraft.x[1][0]+Dyg*inMatrixAircraft.x[1][1]+Dzg*inMatrixAircraft.x[1][2];
    Dz1=Dxg*inMatrixAircraft.x[2][0]+Dyg*inMatrixAircraft.x[2][1]+Dzg*inMatrixAircraft.x[2][2];

    /*Dx1=Dxg*inMatrixAircraft.x[0][0]+Dyg*inMatrixAircraft.x[1][0]+Dzg*inMatrixAircraft.x[2][0];
    Dy1=Dxg*inMatrixAircraft.x[0][1]+Dyg*inMatrixAircraft.x[1][1]+Dzg*inMatrixAircraft.x[2][1];
    Dz1=Dxg*inMatrixAircraft.x[0][2]+Dyg*inMatrixAircraft.x[1][2]+Dzg*inMatrixAircraft.x[2][2];*/

   // Vector3D_D vec=inMatrixAircraft*
   /* Dx1=Dxg*inMatrixAircraft.x[0][0]+Dyg*inMatrixAircraft.x[1][0]+Dzg*inMatrixAircraft.x[2][0];
    Dy1=Dxg*inMatrixAircraft.x[0][1]+Dyg*inMatrixAircraft.x[1][1]+Dzg*inMatrixAircraft.x[2][1];
    Dz1=Dxg*inMatrixAircraft.x[0][2]+Dyg*inMatrixAircraft.x[1][2]+Dzg*inMatrixAircraft.x[2][2];*/


    //! Нормируем вектор D, т.е. и находим единичный вектор D0;
    double length=sqrt(Dx1*Dx1+Dy1*Dy1+Dz1*Dz1);

    double D0x1,D0y1,D0z1;
    D0x1=Dx1/length;
    D0y1=Dy1/length;
    D0z1=Dz1/length;
    //double d=D0x1*D0x1+D0y1*D0y1+D0z1*D0z1;
    //Находим выражения компонент единичного вектора   через углы sigma, tau

    double sigma,tau;

    sigma=atan2(D0z1,D0x1);
    checkSigma(sigma,D0x1,D0z1);
    tau=asin(D0y1);

    outAngleSGF->sigma=sigma;
    outAngleSGF->tau=tau;
}
