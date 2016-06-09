#include "tPrimitives.hpp"

//#define  DEBUG_CROSS

//! проверка, что координаты находятся внутри этой фигуры
bool CircleZone::isInsideCircle(TAngle angle,TAngle center,float radius)
{
    Q_UNUSED(center);
    if((angle.sigma*angle.sigma+angle.tau*angle.tau)>(gradToRadian(radius)*gradToRadian(radius)))
        return false;

    return true;
}
//! проверка, что координаты находятся в сложной фигуре
bool  CircleZone::isInside(TAngle angle/*рад*/)
{
    if(isInsideCircle(angle,c1,r1)==true || isInsideCircle(angle,c2,r2)==true)
        return true;
    else
        return false;
}

//! ограничение углов
TAngle CircleZone::limitCircle(TAngle angle,TAngle center,float radius)
{
    if(isInsideCircle(angle,center,radius) == false)
    {
        double dx0=cos(angle.tau)*cos(angle.sigma);
        double dy0=sin(angle.tau);
        double dz0=-cos(angle.tau)*sin(angle.sigma);

        double dyz=sqrt(dy0*dy0+dz0*dz0);
        double k=0;
        double alfa=radius;
        double salfa=sin(alfa);
        if(dx0>=0.0)
        {
            if(dyz<salfa) k=alfa/salfa;
            else k=alfa/dyz;
        }else k=alfa/dyz;

//        an.tau=gradToRadian(k*dy0);
//        an.sigma=-gradToRadian(k*dz0);

        return TAngle(gradToRadian(k*dy0),-gradToRadian(k*dz0));
    }
    return angle;
}
//! ограничение углов
TAngle CircleZone::limit(TAngle angle)
{
    TAngle p1,p2;
    if(isInside(angle) == true)
        return angle;
    if(isInsideCircle(angle,c1,r1) == false)
    {
        p1=limitCircle(angle,c1,r1);
    }
    if(isInsideCircle(angle,c2,r2) == false)
    {
        p2=limitCircle(angle,c2,r2);
    }

    TAngle dA1=(angle-p1);
    TAngle dA2=(angle-p2);

    if(dA1.distance()>dA2.distance())
        return p2;
    else
        return p1;


}



////////////////////////////////////////////////////////////////////////////////////////////////////
LimitPositionKAI::LimitPositionKAI(double radius_,
                                   double maxVDown,
                                   double maxVUp,
                                   double maxHRight,
                                   double maxHLeft)
{
    radius=radius_;
    maxVerUpAngle=maxVUp;
    maxVerDownAngle=maxVDown;

    maxGorLeftAngle=maxHLeft;
    maxGorRightAngle=maxHRight;

    init();
}
void LimitPositionKAI::init()
{
    angle.sigma=0.0;
    angle.tau=0.0;

    angleCurr.sigma=0.0;
    angleCurr.tau=0.0;

    angleGor=0.0;
    angleVer=0.0;

    gorPos_=0.0;
    verPos_=0.0;
    onLimits=false;
}

//! проверить углы
void LimitPositionKAI::checkAngle(double &gorPos,double &verPos,double &gorPosPred,double &verPosPred)
{
    if(verPos<=0.0)
    {
        if((gorPos*gorPos+verPos*verPos)>1.0)
        {
            gorPos=gorPosPred;
            verPos=verPosPred;
        }
    }
    double scaleVer=fabs(maxVerUpAngle)/fabs(maxVerDownAngle);

    if(verPos>=scaleVer) verPos=scaleVer;

    if(gorPos>0.0) angleGor=gorPos*fabs(maxGorRightAngle);
    else angleGor=gorPos*fabs(maxGorLeftAngle);

    if(verPos>0.0) angleVer=verPos*fabs(maxVerDownAngle);
    else angleVer=verPos*fabs(maxVerDownAngle);

    gorPos_=gorPos;
    verPos_=verPos;

    if((angleVer*angleVer+angleGor*angleGor)>=((radius-0.1)*(radius-0.1)))
    {
        onLimits=true;
    }else onLimits=false;

    angleCurr.sigma=gradToRadian(angleGor);
    angleCurr.tau=gradToRadian(angleVer);

}

/* углы передаваемые этой функции должны быть в градусах*/
TAngle LimitPositionKAI::limitAngle(TAngle angle)
{
    TAngle an;
    if((angle.sigma*angle.sigma+angle.tau*angle.tau)>(gradToRadian(radius)*gradToRadian(radius)))
    {
        double dx0=cos(angle.tau)*cos(angle.sigma);
        double dy0=sin(angle.tau);
        double dz0=-cos(angle.tau)*sin(angle.sigma);

        double dyz=sqrt(dy0*dy0+dz0*dz0);
        double k=0;
        double alfa=radius;
        double salfa=sin(gradToRadian(alfa));
        if(dx0>=0.0)
        {
            if(dyz<salfa) k=alfa/salfa;
            else k=alfa/dyz;
        }else k=alfa/dyz;

        an.tau=gradToRadian(k*dy0);
        an.sigma=-gradToRadian(k*dz0);

        return an;
    }
    return angle;
}
TAngle LimitPositionKAI::limitAngle10(TAngle angle, double rad)
{
    TAngle an;

    double dx0=cos(angle.tau)*cos(angle.sigma);
    double dy0=sin(angle.tau);
    double dz0=-cos(angle.tau)*sin(angle.sigma);

    double dyz=sqrt(dy0*dy0+dz0*dz0);
    double k=0;
    double alfa=rad;
    double salfa=sin(gradToRadian(alfa));
    if(dx0>=0.0)
    {
        if(dyz<salfa) k=alfa/salfa;
        else k=alfa/dyz;
    }else k=alfa/dyz;

    an.tau=gradToRadian(k*dy0);
    an.sigma=-gradToRadian(k*dz0);

    return an;
}

TAngle LimitPositionKAI::limitAngle(TAngle angle, double rad)
{
    TAngle an;
    if((angle.sigma*angle.sigma+angle.tau*angle.tau)>(gradToRadian(rad)*gradToRadian(rad)))
    {
        double dx0=cos(angle.tau)*cos(angle.sigma);
        double dy0=sin(angle.tau);
        double dz0=-cos(angle.tau)*sin(angle.sigma);

        double dyz=sqrt(dy0*dy0+dz0*dz0);
        double k=0;
        double alfa=rad;
        double salfa=sin(gradToRadian(alfa));
        if(dx0>=0.0)
        {
            if(dyz<salfa) k=alfa/salfa;
            else k=alfa/dyz;
        }else k=alfa/dyz;

        an.tau=gradToRadian(k*dy0);
        an.sigma=-gradToRadian(k*dz0);

        return an;
    }
    return angle;
}

TAngle LimitPositionKAI::limitAngle1(TAngle angleCenter, TAngle angle_, double R)
{
    TAngle angle,an;

    R=radius-R;
    angle.sigma=angleCenter.sigma-angle_.sigma;
    angle.tau=angleCenter.tau-angle_.tau;

    double dx0=cos(angle.tau)*cos(angle.sigma);
    double dy0=sin(angle.tau);
    double dz0=-cos(angle.tau)*sin(angle.sigma);

    double dyz=sqrt(dy0*dy0+dz0*dz0);
    double k=0;

    double alfa=R;
    double salfa=sin(gradToRadian(alfa));
    if(dx0>=0.0)
    {
        if(dyz<salfa)
            k=alfa/salfa;
        else
            k=alfa/dyz;
    }else
        k=alfa/dyz;

    an.tau=gradToRadian(k*dy0);
    an.sigma=-gradToRadian(k*dz0);

    return an;
}

TAngle LimitPositionKAI::limitAngle(TAngle angle,           /*точка которую нужно ограничить*/
                                    TAngle angleCenter,     /*центральная точка от которой будут строятся ограничения*/
                                    double radius_grad_max, /*минимальный радиус*/
                                    double radius_grad_min) /*максимальный радиус*/
{
    TAngle an;
    double Rmax=gradToRadian(radius_grad_max);
    double Rmin=gradToRadian(radius_grad_min);
    if(Rmax<0.0)
        Rmax=gradToRadian(radius);

    if((angle.sigma*angle.sigma+angle.tau*angle.tau)>(Rmax*Rmax))
    {
        double x=0.0,y=0.0;

        if(fabs(angle.sigma-angleCenter.sigma)>1e-8)
        {
            double a=(angle.tau-angleCenter.tau)/(angle.sigma-angleCenter.sigma);
            double b=angleCenter.tau-a*angleCenter.sigma;

            double disc=sqrt(pow(2*a*b,2)-4*(a*a+1)*(b*b-Rmax*Rmax));

            double x1=(-2*a*b-disc)/(2*(a*a+1));
            double x2=(-2*a*b+disc)/(2*(a*a+1));

            double y1=a*x1+b;
            double y2=a*x2+b;

            double d2=sqrt(pow(y2-angle.tau,2)+pow(x2-angle.sigma,2));
            double d1=sqrt(pow(y1-angle.tau,2)+pow(x1-angle.sigma,2));

            if(d1>d2)
            {
                y=y2;x=x2;
            }
            else
            {
                y=y1;x=x1;
            }

        }else
        {
            x=angle.sigma;
            y=-sqrt(Rmax*Rmax-x*x);
            //y=sqrt(R*R-x*x);
        }
        an.sigma=x;
        an.tau=y;

        return an;
    }else if(((angle.sigma*angle.sigma+angle.tau*angle.tau)<(Rmin*Rmin)) && Rmin>0.0)
    {
 /*       double sigma=(angle.sigma-angleCenter.sigma);
        double tau=  (angle.tau  -angleCenter.tau);

        double t_2=(Rmin*Rmin)/(sigma*sigma)-tau*tau);

        an.sigma=angleCenter.sigma+sigma*sqrt(fabs(t_2));
        an.tau=angleCenter.tau+tau*sqrt(fabs(t_2));

        return an;*/
        double x=0.0,y=0.0;

        if(fabs(angle.sigma-angleCenter.sigma)>1e-8)
        {
            double a=(angle.tau-angleCenter.tau)/(angle.sigma-angleCenter.sigma);
            double b=angleCenter.tau-a*angleCenter.sigma;

            double disc=sqrt(pow(2*a*b,2)-4*(a*a+1)*(b*b-Rmin*Rmin));

            double x1=(-2*a*b-disc)/(2*(a*a+1));
            double x2=(-2*a*b+disc)/(2*(a*a+1));

            double y1=a*x1+b;
            double y2=a*x2+b;

            double d2=sqrt(pow(y2-angle.tau,2)+pow(x2-angle.sigma,2));
            double d1=sqrt(pow(y1-angle.tau,2)+pow(x1-angle.sigma,2));

            if(d1>d2)
            {
                y=y2;x=x2;
            }
            else
            {
                y=y1;x=x1;
            }

        }else
        {
            x=angle.sigma;
            y=-sqrt(Rmin*Rmin-x*x);
        }
        an.sigma=x;
        an.tau=y;

        return an;

    }
    return angle;
}
TAngle LimitPositionKAI::limitAngle(TAngle angle,TAngle angleCenter,double radius_grad)
{
    TAngle an;
    double R=gradToRadian(radius);
    if(radius_grad>0.0) R=gradToRadian(radius_grad);

    if((angle.sigma*angle.sigma+angle.tau*angle.tau)>(R*R))
    {
        double x=0.0,y=0.0;

        if(fabs(angle.sigma-angleCenter.sigma)>1e-8)
        {
            double a=(angle.tau-angleCenter.tau)/(angle.sigma-angleCenter.sigma);
            double b=angleCenter.tau-a*angleCenter.sigma;

            double disc=sqrt(pow(2*a*b,2)-4*(a*a+1)*(b*b-R*R));

            double x1=(-2*a*b-disc)/(2*(a*a+1));
            double x2=(-2*a*b+disc)/(2*(a*a+1));

            double y1=a*x1+b;
            double y2=a*x2+b;

            double d2=sqrt(pow(y2-angle.tau,2)+pow(x2-angle.sigma,2));
            double d1=sqrt(pow(y1-angle.tau,2)+pow(x1-angle.sigma,2));

            if(d1>d2)  {y=y2;x=x2;}
            else {y=y1;x=x1;}

        }else
        {
            x=angle.sigma;
            y=-sqrt(R*R-x*x);
            //y=sqrt(R*R-x*x);
        }
        an.sigma=x;
        an.tau=y;

        return an;
    }
    if(radius_grad>0.0) angle.tau*=-1.0;
    return angle;
}

double LimitPositionKAI::limitAngleGor(double currentAngleGor)
{
    angle.sigma=limitMinMax(currentAngleGor,maxGorRightAngle,maxGorLeftAngle);
    return angle.sigma;
}

double LimitPositionKAI::limitAngleVer(double currentAngleVer)
{
    angle.tau=limitMinMax(currentAngleVer,maxVerDownAngle,maxVerUpAngle);
    return angle.tau;
}

double LimitPositionKAI::mappingAngleGorToGorPos(double aGor)
{
    aGor=limitAngleGor(aGor);

    if(aGor<0.0) return aGor/fabs(maxGorLeftAngle);
    return aGor/fabs(maxGorRightAngle);
}

double LimitPositionKAI::mappingAngleVerToVerPos(double aVer)
{
    aVer=limitAngleVer(aVer);

    if(aVer<0.0) return aVer/fabs(maxVerDownAngle);
    return aVer/fabs(maxVerDownAngle);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
DelayValue::DelayValue(bool* inValue_,bool* outValue_,QString idName):ICalculateElement(idName)
{
    inValue=inValue_;
    outValue=outValue_;

    *outValue=*inValue;
    timer_delay.run=false;
    timer_delay.msec=0;

    trigger100Hz=new Trigger<bool> (*inValue_);
    setFrec(ICalculateElement::Hz100);
    //! запуск данной модели
    this->setStart();
}
void DelayValue::setTimeDelay(long msec)
{
    timeMsec=msec;
    createTimer(&timer_delay,timeMsec);
}

void DelayValue::init()
{
    timer_delay.run=false;
    timer_delay.msec=0;
    *outValue=*inValue;
}
void DelayValue::calculate()
{
    trigger100Hz->setState(*inValue);
    if(trigger100Hz->isHightFront()==true && timer_delay.run==false)
    {
        createTimer(&timer_delay,timeMsec);
        timer_delay.run=true;
        //timer_delay.msec=0;
        *outValue=true;
    }
    if(trigger100Hz->isLowFront()==true && timer_delay.run==false)
    {
        createTimer(&timer_delay,timeMsec);
        timer_delay.run=true;
        //timer_delay.msec=0;
        *outValue=false;
    }
    if(timer_delay.msec==timeMsec)
    {
        timer_delay.run=false;
        timer_delay.msec=0;
        *outValue=*inValue;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
DefaultSpeed::DefaultSpeed(const float *LR,
             const float *UD,
             double step_)
{
    step=step_;

    speedHor_=LR;
    speedVer_=UD;

    limitHorPos=1.0;
    limitVerPos=1.0;

    divideHor=1.0;
    divideVer=1.0;

    horFilter=new FilterAperiodic(*speedHor_,1/0.1,step,limitHorPos,-limitHorPos);
    verFilter=new FilterAperiodic(*speedVer_,1/0.1,step,limitVerPos,-limitVerPos);
}

double DefaultSpeed::speedVer()
{
   return currentSpeedVer;
}
double DefaultSpeed::speedHor()
{
    return currentSpeedHor;
}
void DefaultSpeed::setDivideSpeedHor(double d)
{
    divideHor=d;
}

void DefaultSpeed::setDivideSpeedVer(double d)
{
    divideVer=d;
}

void DefaultSpeed::refresh()
{
    float valueHor=*speedHor_;
    float valueVer=*speedVer_;

    if(fabs(valueHor)<0.1)
        valueHor=0.0;

    if(fabs(valueVer)<0.1)
        valueVer=0.0;
    currentSpeedHor=divideHor*horFilter->filterValue(valueHor);
    currentSpeedVer=divideVer*verFilter->filterValue(valueVer);
}
