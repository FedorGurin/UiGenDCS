
#include "cl_DataForVxWorks_Su35_1.h"

using namespace Su35_1;
cl_DataForVxWorks_Su35_1::cl_DataForVxWorks_Su35_1(void):GenericData()
{
    qDebug("Create cl_DataForVxWorks\n");
    memset((void*)&bufferData,0,sizeof(TDSTRUCTVISULISATION));
    memset((void*)&middleBufferData,0,sizeof(TDSTRUCTVISULISATION));

    bufferData.controlPULT.Kupr=1;
    middleBufferData.controlPULT.Kupr=1;

    bufferData.controlPULT.RealPult=1;
    middleBufferData.controlPULT.RealPult=1;

    ptrBufData=&middleBufferData;
    numTargets=0;
    bufferData.controlPULT.pr_ostanov=1;
    bufferData.controlPULT.pr_isxodnoe=0;
    bufferData.controlPULT.pr_pusk=0;

    middleBufferData.controlPULT.pr_ostanov=1;
    middleBufferData.controlPULT.pr_isxodnoe=0;
    middleBufferData.controlPULT.pr_pusk=0;

    // TODO Auto-generated constructor stub
}
void cl_DataForVxWorks_Su35_1::newTransmitObject()
{
    if(transmit!=0)
    {
        transmit->setSizeBytes(sizeof(TDSTRUCTVISULISATION));
        connect(transmit,SIGNAL(ReciveData(char*)),this,SLOT(slotResived(char*)));
        transmit->enableRecive(true);
    }else qDebug("Warning::In cl_DataForVxWorks pointer to transmit Object is NULL\n");
}
void cl_DataForVxWorks_Su35_1::refreshFormTargets()
{
    QStringList value;

    if(numTargets!=middleBufferData.NumberTarget)
    {
        numTargets=bufferData.NumberTarget;
        targetsForm->setNumTargets(numTargets);
    }
    for(int i=0;i<numTargets;i++)
    {
        TDesTarget *tar=&(middleBufferData.DesArjObject.DesTarget[i]);

        value<<QString::number(tar->fix_relational,FORM,PRE);   //1
        value<<QString::number(tar->fiy_relational,FORM,PRE);   //2
        value<<QString::number(tar->fiz_relational,FORM,PRE);   //3
        value<<QString::number(tar->di_relational,FORM,PRE);    //4
        value<<QString::number(tar->pdi_relational,FORM,PRE);   //5
        value<<QString::number(tar->v_target,FORM,PRE);         //6
        value<<QString::number(tar->vx_target,FORM,PRE);        //7
        value<<QString::number(tar->vy_target,FORM,PRE);        //8
        value<<QString::number(tar->vz_target,FORM,PRE);        //9
        value<<QString::number(tar->x_target,FORM,PRE);         //10
        value<<QString::number(tar->y_target,FORM,PRE);         //11
        value<<QString::number(tar->z_target,FORM,PRE);         //12
        value<<QString::number(tar->psi_target,FORM,PRE);       //13
        value<<QString::number(tar->teta_target,FORM,PRE);      //14
        value<<QString::number(tar->gama_target,FORM,PRE);      //15
        value<<QString::number(tar->fix_relational1,FORM,PRE);  //16
        value<<QString::number(tar->fiy_relational1,FORM,PRE);  //17
        value<<QString::number(tar->fiz_relational1,FORM,PRE);  //18
        //value<<val.setNum(tar->l_target,FORM,PRE);            //19

        targetsForm->setValue(value,i);
        value.clear();
    }
}
void cl_DataForVxWorks_Su35_1::refreshRegime()
{
    if(middleBufferData.Flag==0) _regime=STOP;
    else if(middleBufferData.Flag==3) _regime=START;
    else if(middleBufferData.Flag==2) _regime=ISXODNOE;

}
int cl_DataForVxWorks_Su35_1::targetNumbers()
{
     return numTargets;
}
int cl_DataForVxWorks_Su35_1::targetAirNum()
{
    return middleBufferData.airtarget_Q;
}
void cl_DataForVxWorks_Su35_1::refreshData()
{
    bufferData=middleBufferData;
    switch(middleBufferData.ComRegimeStend.RegimeContr)
    {
    case 0:{_controlReg=KABINA_SAU;break;}
    case 1:{_controlReg=DETERM;break;}
    case 2:{_controlReg=DETERM_CIRCLE;break;}
    case 3:{_controlReg=KABINA_CIRCLE;break;}
    case 4:{_controlReg=TEST_UVOD;break;}
    case 5:{_controlReg=FDR;break;}
    };
    refreshFormTargets();
    refreshFormAtmGeo();
    refreshFormKinAircraft();
    refreshFormConst();
    refreshFormCommonConst();
}
void cl_DataForVxWorks_Su35_1::refreshFormAtmGeo(void)
{
    QStringList value;
    ItemTable* item=0;

    ///////////Geography_Earth
    Tgeography_Earth* geo=&middleBufferData.Geography_Earth;
    Tair_parametrs* air=&middleBufferData.Air_parametrs;
    Tkinematiks_aircraft *pKinAir=&middleBufferData.DesArjObject.Kinematiks_aircraft;
    TDSUOCOM *suoCom=&middleBufferData.DSUOCOM;

    value<<QString::number(geo->fit_geography,FORM,PRE);                //1
    item=(ItemTable*)(tableForms[2]->returnTableWidget()->item(0,0));
    item->setValue(QString::number(geo->fit_geography));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(geo->limdat_geography,FORM,PRE);             //2
    item=(ItemTable*)(tableForms[2]->returnTableWidget()->item(1,0));
    item->setValue(QString::number(geo->limdat_geography));

    item->setTimeStep(pKinAir->t_pol_aircraft);
    value<<QString::number(geo->Au_geography,FORM,PRE);                 //3
    item=(ItemTable*)(tableForms[2]->returnTableWidget()->item(2,0));
    item->setValue(QString::number(geo->Au_geography));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(geo->DeltaM0,FORM,PRE);                      //4
    item=(ItemTable*)(tableForms[2]->returnTableWidget()->item(3,0));
    item->setValue(QString::number(geo->DeltaM0));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(air->v_dev_airPrev,FORM,PRE);                    //5
    item=(ItemTable*)(tableForms[2]->returnTableWidget()->item(4,0));
    item->setValue(QString::number(air->v_dev_airPrev));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(air->Pst_airPrev,FORM,PRE);                      //6
    item=(ItemTable*)(tableForms[2]->returnTableWidget()->item(5,0));
    item->setValue(QString::number(air->Pst_airPrev));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(air->g_airPrev,FORM,PRE);                        //7
    item=(ItemTable*)(tableForms[2]->returnTableWidget()->item(6,0));
    item->setValue(QString::number(air->g_airPrev));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(pKinAir->G_engine,FORM,PRE);                 //8
    item=(ItemTable*)(tableForms[2]->returnTableWidget()->item(7,0));
    item->setValue(QString::number(pKinAir->G_engine));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(suoCom->Gasp,FORM,PRE);                      //9
    item=(ItemTable*)(tableForms[2]->returnTableWidget()->item(8,0));
    item->setValue(QString::number(suoCom->Gasp));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    tableForms[2]->setValue(value);
    value.clear();
}
void cl_DataForVxWorks_Su35_1::refreshFormKinAircraft(void)
{
    QStringList value;
    ItemTable* item=0;

    Tkinematiks_aircraft *pKinAir=&middleBufferData.DesArjObject.Kinematiks_aircraft;

    //! Обновляем данные кинематики
    value<<QString::number(pKinAir->psic_aircraft,FORM,PRE);		//1
    item=(ItemTable*)(tableForms[0]->returnTableWidget()->item(0,0));
    item->setValue(QString::number(pKinAir->psic_aircraft));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(pKinAir->psi_aircraft,FORM,PRE);		//2
    item=static_cast<ItemTable* > (tableForms[0]->returnTableWidget()->item(1,0));
    item->setValue(QString::number(pKinAir->psi_aircraft));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(pKinAir->teta_aircraft,FORM,PRE);		//3
    item=static_cast<ItemTable* > (tableForms[0]->returnTableWidget()->item(2,0));
    item->setValue(QString::number(pKinAir->teta_aircraft));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(pKinAir->tetac_aircraft,FORM,PRE);	//4
    item=static_cast<ItemTable* > (tableForms[0]->returnTableWidget()->item(3,0));
    item->setValue(QString::number(pKinAir->tetac_aircraft));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(pKinAir->gamac_aircraft,FORM,PRE);	//5
    item=static_cast<ItemTable* > (tableForms[0]->returnTableWidget()->item(4,0));
    item->setValue(QString::number(pKinAir->gamac_aircraft));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(pKinAir->alfa_aircraft,FORM,PRE);		//6
    item=static_cast<ItemTable* > (tableForms[0]->returnTableWidget()->item(5,0));
    item->setValue(QString::number(pKinAir->alfa_aircraft));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(pKinAir->beta_aircraft,FORM,PRE);		//7
    item=static_cast<ItemTable* > (tableForms[0]->returnTableWidget()->item(6,0));
    item->setValue(QString::number(pKinAir->beta_aircraft));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(pKinAir->omcx_aircraft,FORM,PRE);		//8
    item=static_cast<ItemTable* > (tableForms[0]->returnTableWidget()->item(7,0));
    item->setValue(QString::number(pKinAir->omcx_aircraft));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(pKinAir->omcy_aircraft,FORM,PRE);		//9
    item=static_cast<ItemTable* > (tableForms[0]->returnTableWidget()->item(8,0));
    item->setValue(QString::number(pKinAir->omcy_aircraft));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(pKinAir->omcz_aircraft,FORM,PRE);		//10
    item=static_cast<ItemTable* > (tableForms[0]->returnTableWidget()->item(9,0));
    item->setValue(QString::number(pKinAir->omcz_aircraft));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(pKinAir->ncx_aircraft,FORM,PRE);		//11
    item=static_cast<ItemTable* > (tableForms[0]->returnTableWidget()->item(10,0));
    item->setValue(QString::number(pKinAir->ncx_aircraft));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(pKinAir->ncy_aircraft,FORM,PRE);		//12
    item=static_cast<ItemTable* > (tableForms[0]->returnTableWidget()->item(11,0));
    item->setValue(QString::number(pKinAir->ncy_aircraft));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(pKinAir->ncz_aircraft,FORM,PRE);		//13
    item=static_cast<ItemTable* > (tableForms[0]->returnTableWidget()->item(12,0));
    item->setValue(QString::number(pKinAir->ncz_aircraft));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(pKinAir->vc_aircraft,FORM,PRE);		//14
    item=static_cast<ItemTable* > (tableForms[0]->returnTableWidget()->item(13,0));
    item->setValue(QString::number(pKinAir->vc_aircraft));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(pKinAir->vcx_aircraft,FORM,PRE);		//15
    item=static_cast<ItemTable* > (tableForms[0]->returnTableWidget()->item(14,0));
    item->setValue(QString::number(pKinAir->vcx_aircraft));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(pKinAir->vcy_aircraft,FORM,PRE);		//16
    item=static_cast<ItemTable* > (tableForms[0]->returnTableWidget()->item(15,0));
    item->setValue(QString::number(pKinAir->vcy_aircraft));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(pKinAir->vcz_aircraft,FORM,PRE);		//17
    item=static_cast<ItemTable* > (tableForms[0]->returnTableWidget()->item(16,0));
    item->setValue(QString::number(pKinAir->vcz_aircraft));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(pKinAir->M_aircraft,FORM,PRE);		//18
    item=static_cast<ItemTable* > (tableForms[0]->returnTableWidget()->item(17,0));
    item->setValue(QString::number(pKinAir->M_aircraft));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(pKinAir->xc_aircraft,FORM,PRE);		//19
    item=static_cast<ItemTable* > (tableForms[0]->returnTableWidget()->item(18,0));
    item->setValue(QString::number(pKinAir->xc_aircraft));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(pKinAir->yc_aircraft,FORM,PRE);		//20
    item=static_cast<ItemTable* > (tableForms[0]->returnTableWidget()->item(19,0));
    item->setValue(QString::number(pKinAir->yc_aircraft));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(pKinAir->zc_aircraft,FORM,PRE);		//21
    item=static_cast<ItemTable* > (tableForms[0]->returnTableWidget()->item(20,0));
    item->setValue(QString::number(pKinAir->zc_aircraft));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    tableForms[0]->setValue(value);
    value.clear();
}
void cl_DataForVxWorks_Su35_1::refreshFormConst(void)
{
    QStringList value;
    ItemTable* item=0;

    Tkinematiks_aircraft *pKinAir=&middleBufferData.DesArjObject.Kinematiks_aircraft;
    Tkinematiks_aircraftConst *pKinConst=&middleBufferData.Kinematiks_aircraftConst;
    TDSTRUCTVISULISATION *dstr=&middleBufferData;
    //! Обновлем общие константы
    //CommonConst

    value<<QString::number(dstr->NVarIsh,FORM,PRE);//1
    item=(ItemTable*)(tableForms[1]->returnTableWidget()->item(0,0));
    item->setValue(QString::number(dstr->NVarIsh));
    item->setTimeStep(pKinAir->t_pol_aircraft);


    value<<QString::number(dstr->FlagNewNVarIsh,FORM,PRE);//2
    item=(ItemTable*)(tableForms[1]->returnTableWidget()->item(1,0));
    item->setValue(QString::number(dstr->FlagNewNVarIsh));
    item->setTimeStep(pKinAir->t_pol_aircraft);


    value<<QString::number(dstr->N_BegFromPult,FORM,PRE);//3
    item=(ItemTable*)(tableForms[1]->returnTableWidget()->item(2,0));
    item->setValue(QString::number(dstr->N_BegFromPult));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(dstr->N_EndFromPult,FORM,PRE);//4
    item=(ItemTable*)(tableForms[1]->returnTableWidget()->item(3,0));
    item->setValue(QString::number(dstr->N_EndFromPult));
    item->setTimeStep(pKinAir->t_pol_aircraft);


    //! Здесь должен быть файл начальных условий
    value<<QString::number(dstr->TotalNumberVariants,FORM,PRE);//5
    item=(ItemTable*)(tableForms[1]->returnTableWidget()->item(4,0));
    item->setValue(QString::number(dstr->TotalNumberVariants));
    item->setTimeStep(pKinAir->t_pol_aircraft);


    value<<QString::number(dstr->NumberTarget,FORM,PRE);//6
    item=(ItemTable*)(tableForms[1]->returnTableWidget()->item(5,0));
    item->setValue(QString::number(dstr->NumberTarget));
    item->setTimeStep(pKinAir->t_pol_aircraft);


    value<<QString::number(dstr->airtarget_Q,FORM,PRE);//7
    item=(ItemTable*)(tableForms[1]->returnTableWidget()->item(6,0));
    item->setValue(QString::number(dstr->airtarget_Q));
    item->setTimeStep(pKinAir->t_pol_aircraft);


    value<<QString::number(pKinConst->ux_aircraft,FORM,PRE);//8
    item=(ItemTable*)(tableForms[1]->returnTableWidget()->item(7,0));
    item->setValue(QString::number(pKinConst->ux_aircraft));
    item->setTimeStep(pKinAir->t_pol_aircraft);


    value<<QString::number(pKinConst->uz_aircraft,FORM,PRE);//9
    item=(ItemTable*)(tableForms[1]->returnTableWidget()->item(8,0));
    item->setValue(QString::number(pKinConst->uz_aircraft));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(pKinConst->beta0_aircraft,FORM,PRE);//10
    item=(ItemTable*)(tableForms[1]->returnTableWidget()->item(9,0));
    item->setValue(QString::number(pKinConst->beta0_aircraft));
    item->setTimeStep(pKinAir->t_pol_aircraft);


    value<<QString::number(pKinConst->Hbar_aircraft,	FORM,PRE);//11
    item=(ItemTable*)(tableForms[1]->returnTableWidget()->item(10,0));
    item->setValue(QString::number(pKinConst->Hbar_aircraft));
    item->setTimeStep(pKinAir->t_pol_aircraft);


    value<<QString::number(pKinConst->Hrvrf_C,		FORM,PRE);//12
    item=(ItemTable*)(tableForms[1]->returnTableWidget()->item(11,0));
    item->setValue(QString::number(pKinConst->Hrvrf_C));
    item->setTimeStep(pKinAir->t_pol_aircraft);


    value<<QString::number(pKinConst->Hrvrfmin_C,	FORM,PRE);//13
    item=(ItemTable*)(tableForms[1]->returnTableWidget()->item(12,0));
    item->setValue(QString::number(pKinConst->Hrvrfmin_C));
    item->setTimeStep(pKinAir->t_pol_aircraft);


    value<<QString::number(pKinConst->Hrvrfmax_C,	FORM,PRE);//14
    item=(ItemTable*)(tableForms[1]->returnTableWidget()->item(13,0));
    item->setValue(QString::number(pKinConst->Hrvrfmax_C));
    item->setTimeStep(pKinAir->t_pol_aircraft);


    value<<QString::number(pKinConst->alfarvrf_C,	FORM,PRE);//15
    item=(ItemTable*)(tableForms[1]->returnTableWidget()->item(14,0));
    item->setValue(QString::number(pKinConst->alfarvrf_C));
    item->setTimeStep(pKinAir->t_pol_aircraft);


    value<<QString::number(pKinConst->psirvrf_C,		FORM,PRE);//16
    item=(ItemTable*)(tableForms[1]->returnTableWidget()->item(15,0));
    item->setValue(QString::number(pKinConst->psirvrf_C));
    item->setTimeStep(pKinAir->t_pol_aircraft);


    value<<QString::number(pKinConst->Htargetrf_C,	FORM,PRE);//17
    item=(ItemTable*)(tableForms[1]->returnTableWidget()->item(16,0));
    item->setValue(QString::number(pKinConst->Htargetrf_C));
    item->setTimeStep(pKinAir->t_pol_aircraft);


    value<<QString::number(pKinConst->Htargetrfmin_C,FORM,PRE);//18
    item=(ItemTable*)(tableForms[1]->returnTableWidget()->item(17,0));
    item->setValue(QString::number(pKinConst->Htargetrfmin_C));
    item->setTimeStep(pKinAir->t_pol_aircraft);


    value<<QString::number(pKinConst->Htargetrfmax_C,FORM,PRE);//19
    item=(ItemTable*)(tableForms[1]->returnTableWidget()->item(18,0));
    item->setValue(QString::number(pKinConst->Htargetrfmax_C));
    item->setTimeStep(pKinAir->t_pol_aircraft);


    value<<QString::number(pKinConst->psitargetrf_C,	FORM,PRE);//20
    item=(ItemTable*)(tableForms[1]->returnTableWidget()->item(19,0));
    item->setValue(QString::number(pKinConst->psitargetrf_C));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(pKinConst->AlfaSM, FORM,PRE);//20
    item=(ItemTable*)(tableForms[1]->returnTableWidget()->item(20,0));
    item->setValue(QString::number(pKinConst->AlfaSM));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    tableForms[1]->setValue(value);
    value.clear();
}
void cl_DataForVxWorks_Su35_1::refreshFormCommonConst(void)
{
    QStringList value;
    ItemTable* item=0;

    TCommonConst *cConst=&middleBufferData.CommonConst;
    Tkinematiks_aircraft *pKinAir=&middleBufferData.DesArjObject.Kinematiks_aircraft;
    Tkinematiks_aircraftConst *pKinConst=&middleBufferData.Kinematiks_aircraftConst;

    //! Обновлем общие константы
    //CommonConst

    value<<QString::number(cConst->TAlfa,FORM,PRE);//1
    item=(ItemTable*)(tableForms[3]->returnTableWidget()->item(0,0));
    item->setValue(QString::number(cConst->TAlfa));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(cConst->TBeta,FORM,PRE);//2
    item=(ItemTable*)(tableForms[3]->returnTableWidget()->item(1,0));
    item->setValue(QString::number(cConst->TBeta));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(pKinConst->AlfaBalUst,FORM,PRE);//3
    item=(ItemTable*)(tableForms[3]->returnTableWidget()->item(2,0));
    item->setValue(QString::number(pKinConst->AlfaBalUst));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(cConst->Knx0,FORM,PRE);//4
    item=(ItemTable*)(tableForms[3]->returnTableWidget()->item(3,0));
    item->setValue(QString::number(cConst->Knx0));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(cConst->ny_dop,FORM,PRE);//5
    item=(ItemTable*)(tableForms[3]->returnTableWidget()->item(4,0));
    item->setValue(QString::number(cConst->ny_dop));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(cConst->fi_dv,FORM,PRE);//6
    item=(ItemTable*)(tableForms[3]->returnTableWidget()->item(5,0));
    item->setValue(QString::number(cConst->fi_dv));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(cConst->Vmin_C,FORM,PRE);//7
    item=(ItemTable*)(tableForms[3]->returnTableWidget()->item(6,0));
    item->setValue(QString::number(cConst->Vmin_C));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(cConst->Hmax_C,FORM,PRE);//8
    item=(ItemTable*)(tableForms[3]->returnTableWidget()->item(7,0));
    item->setValue(QString::number(cConst->Hmax_C));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(cConst->Vmin_target,FORM,PRE);//9
    item=(ItemTable*)(tableForms[3]->returnTableWidget()->item(8,0));
    item->setValue(QString::number(cConst->Vmin_target));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(cConst->Vmax_target,FORM,PRE);//10
    item=(ItemTable*)(tableForms[3]->returnTableWidget()->item(9,0));
    item->setValue(QString::number(cConst->Vmax_target));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(cConst->Mat_min,FORM,PRE);//11
    item=(ItemTable*)(tableForms[3]->returnTableWidget()->item(10,0));
    item->setValue(QString::number(cConst->Mat_min));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(cConst->G0,FORM,PRE);//12
    item=(ItemTable*)(tableForms[3]->returnTableWidget()->item(11,0));
    item->setValue(QString::number(cConst->G0));
    item->setTimeStep(pKinAir->t_pol_aircraft);

    value<<QString::number(cConst->Gc,FORM,PRE);//13
    item=(ItemTable*)(tableForms[3]->returnTableWidget()->item(12,0));
    item->setValue(QString::number(cConst->Gc));
    item->setTimeStep(pKinAir->t_pol_aircraft);


    tableForms[3]->setValue(value);
    value.clear();
}

void cl_DataForVxWorks_Su35_1::createFormAtmGeo(void)
{
    QVector <ItemTable*> items;

    items.push_back(new ItemTable(tr("Широта"),                         true,false,tr("гр")));//1
    items.push_back(new ItemTable(tr("Долгота"),                        true,false,tr("гр")));//2
    items.push_back(new ItemTable(tr("Курсовой угол стаб.СК"),          true,false,tr("гр")));//3
    items.push_back(new ItemTable(tr("Угол магнитного склонения"),      true,false,tr("гр")));//4
    items.push_back(new ItemTable(tr("Приборная скорость"),             true,false,tr("м/с")));//5
    items.push_back(new ItemTable(tr("Статическое атм. давление"),      true,false,tr("кгс/м*м")));//6
    items.push_back(new ItemTable(tr("Динамическое давление"),          true,false,tr("кгс/м*м")));//7
    items.push_back(new ItemTable(tr("Вес самолета"),                   true,false,tr("т")));//8
    items.push_back(new ItemTable(tr("Вес подвес. средств"),            true,false,tr("т")));//9

    tableForms[2]->setItems(items);
}
void cl_DataForVxWorks_Su35_1::createFormTargets(void)
{
    QVector <ItemTable*> items;

    items.push_back(new ItemTable(tr("Напр. косинус X"),            true,false,tr("ед.")));
    items.push_back(new ItemTable(tr("Напр. косинус Y"),            true,false,tr("ед.")));
    items.push_back(new ItemTable(tr("Напр. косинус Z"),            true,false,tr("ед.")));
    items.push_back(new ItemTable(tr("Дальность"),                  true,false,tr("м")));
    items.push_back(new ItemTable(tr("Скорость сближения"),         true,false,tr("м/с")));
    items.push_back(new ItemTable(tr("Лин. возд. скорость"),        true,false,tr("м/с")));
    items.push_back(new ItemTable(tr("Лин. возд. скорость X"),      true,false,tr("м/с")));
    items.push_back(new ItemTable(tr("Лин. возд. скорость Y"),      true,false,tr("м/с")));
    items.push_back(new ItemTable(tr("Лин. возд. скорость Z"),      true,false,tr("м/с")));
    items.push_back(new ItemTable(tr("Лин. координата X"),          true,false,tr("м")));
    items.push_back(new ItemTable(tr("Лин. координата Y"),          true,false,tr("м")));
    items.push_back(new ItemTable(tr("Лин. координата Z"),          true,false,tr("м")));
    items.push_back(new ItemTable(tr("Угол. пол. вектора Psi"),     true,false,tr("гр.")));
    items.push_back(new ItemTable(tr("Угол. пол. вектора Teta"),    true,false,tr("гр.")));
    items.push_back(new ItemTable(tr("Угол. пол. вектора Gamma"),   true,false,tr("гр.")));
    items.push_back(new ItemTable(tr("Относит. коорд. X"),          true,false,tr("ед.")));
    items.push_back(new ItemTable(tr("Относит. коорд. Y"),          true,false,tr("ед.")));
    items.push_back(new ItemTable(tr("Относит. коорд. Z"),          true,false,tr("ед.")));
    //items.push_back(new ItemTable(tr("Длинна (м)"),               true));

    targetsForm->setItems(items);
}
void cl_DataForVxWorks_Su35_1::createFormConst(void)
{

    QVector <ItemTable*> items;

    items.push_back(new ItemTable(tr("Номер варианта"),                 false,false,tr("номер")));//1
    items.push_back(new ItemTable(tr("Изменить варианта"),              false,false,tr("признак")));//2
    items.push_back(new ItemTable(tr("Номер начального варианта с ПУ"), false,false,tr("номер")));//3
    items.push_back(new ItemTable(tr("Номер конечного варианта с ПУ"),  false,false,tr("номер")));//4
    items.push_back(new ItemTable(tr("Всего исходных вариантов"),       false,false,tr("кол-во")));//5
    //items.push_back(new ItemTable(tr("Имя файла начальных условий"),  true,false));//6
    items.push_back(new ItemTable(tr("Количество всех целей"),          false,false,tr("кол-во")));//7
    items.push_back(new ItemTable(tr("Количество воздушных целей"),     false,false,tr("кол-во")));//8
    items.push_back(new ItemTable(tr("Скорость ветра по X"),            true,false,tr("м/с"),tr("Относительно модельной системы координат")));         //9
    items.push_back(new ItemTable(tr("Скорость ветра по Z"),            true,false,tr("м/с"),tr("Относительно модельной системы координат")));         //10
    items.push_back(new ItemTable(tr("Угол скольжения установочный"),   true,false,tr("гр")));//11
    items.push_back(new ItemTable(tr("Нулевая бар. высота"),            true,false,tr("м")));//12
    items.push_back(new ItemTable(tr("Нулевая высота рельефа РВ"),      true,false,tr("м")));//13
    items.push_back(new ItemTable(tr("Мин. высота рельефа РВ"),         true,false,tr("м")));//14
    items.push_back(new ItemTable(tr("Макс. высота рельефа РВ"),        true,false,tr("м")));//15
    items.push_back(new ItemTable(tr("Угол наклона рельефа РВ"),        true,false,tr("гр")));//16
    items.push_back(new ItemTable(tr("Курс рельефа РВ"),                true,false,tr("гр")));//17
    items.push_back(new ItemTable(tr("Нулевая высота рельефа НЦ"),      true,false,tr("м")));//18
    items.push_back(new ItemTable(tr("Мин. высота рельефа НЦ"),         true,false,tr("м")));//19
    items.push_back(new ItemTable(tr("Макс. высота рельефа НЦ"),        true,false,tr("м")));//20
    items.push_back(new ItemTable(tr("Курс рельефа НЦ"),                true,false,tr("гр")));//21
    items.push_back(new ItemTable(tr("Угол сверхманевренности"),        true,false,tr("гр")));//22

    tableForms[1]->setItems(items);
}

void cl_DataForVxWorks_Su35_1::createFormKinAircraft(void)
{
    QVector <ItemTable*> items;

    items.push_back(new ItemTable(tr("Курс"),                   true,false,tr("гр")));//1
    items.push_back(new ItemTable(tr("Путевой угол"),           true,true,tr("гр")));//2
    items.push_back(new ItemTable(tr("Угол нак. траектории"),   true,true,tr("гр")));//3
    items.push_back(new ItemTable(tr("Тангаж"),                 true,false,tr("гр")));//4
    items.push_back(new ItemTable(tr("Крен"),                   true,true,tr("гр")));//5
    items.push_back(new ItemTable(tr("Угол атаки-текущий"),     true,false,tr("гр")));//6
    items.push_back(new ItemTable(tr("Угол скольжения-текущий"),true,false,tr("гр")));//7
    items.push_back(new ItemTable(tr("Уг. скорость по X"),      true,true,tr("гр/сек")));//8
    items.push_back(new ItemTable(tr("Уг. скорость по Y"),      true,true,tr("гр/сек")));//9
    items.push_back(new ItemTable(tr("Уг. скорость по Z"),      true,true,tr("гр/сек")));//10
    items.push_back(new ItemTable(tr("Лин. перегрузка по X"),   true,false,tr("ед")));//11
    items.push_back(new ItemTable(tr("Лин. перегрузка по Y"),   true,false,tr("ед")));//12
    items.push_back(new ItemTable(tr("Лин. перегрузка по Z"),   true,false,tr("ед")));//13
    items.push_back(new ItemTable(tr("Лин. возд. скорость"),    true,true,tr("м/с")));//14
    items.push_back(new ItemTable(tr("Лин. возд. скорость по X"),true,false,tr("м/с")));//15
    items.push_back(new ItemTable(tr("Лин. возд. скорость по Y"),true,false,tr("м/с")));//16
    items.push_back(new ItemTable(tr("Лин. возд. скорость по Z"),true,false,tr("м/с")));//17
    items.push_back(new ItemTable(tr("Число Маха"),             true,false,tr("ед")));//18
    items.push_back(new ItemTable(tr("Лин. координаты X"),      true,true,tr("м")));//19
    items.push_back(new ItemTable(tr("Лин. координаты Y"),      true,true,tr("м")));//20
    items.push_back(new ItemTable(tr("Лин. координаты Z"),      true,true,tr("м")));//21

    tableForms[0]->setItems(items);
}
void cl_DataForVxWorks_Su35_1::createFormCommonConst(void)
{
    QVector <ItemTable*> items;

    items.push_back(new ItemTable(tr("Постоянная времени по углу атаки"),       true,false,tr("сек.")));//1
    items.push_back(new ItemTable(tr("Постоянная времени по углу скольжению"),  true,false,tr("сек.")));//2
    items.push_back(new ItemTable(tr("Балансировочный угол атаки"),             true,false,tr("град")));//3
    items.push_back(new ItemTable(tr("Коэффициент перегрузки Knx"),             true,false,tr("б/р")));//4
    items.push_back(new ItemTable(tr("Перегрузка допустимая y"),                true,false,tr("ед")));//5
    items.push_back(new ItemTable(tr("Угол установки двигателя(fi_dv)"),        true,false,tr("град")));//6
    items.push_back(new ItemTable(tr("Скорость минимальная самолета"),          true,false,tr("м/с")));//7
    items.push_back(new ItemTable(tr("Высота маскимальная самолета"),           true,false,tr("м")));//8
    items.push_back(new ItemTable(tr("Скорость мин. цели"),                     true,false,tr("м/с")));//9
    items.push_back(new ItemTable(tr("Скорость макс. цели"),                    true,false,tr("м/с")));//10
    items.push_back(new ItemTable(tr("Mat_min"),                                true,false,tr("ед.")));//11
    items.push_back(new ItemTable(tr("Вес самолета"),                           true,false,tr("т")));//12
    items.push_back(new ItemTable(tr("Полный вес самолета"),                    true,false,tr("т")));//13

    tableForms[3]->setItems(items);
}

void cl_DataForVxWorks_Su35_1::sendData()
{

    //qDebug("call cl_DataForVxWorks_Su35_1::sendData()\n");
    if(blockSend==true) return;
    QStringList list;

    ///////////////Сохраним кинематические параметры
    Tkinematiks_aircraft *kin=&bufferData.DesArjObject.Kinematiks_aircraft;
    TDSTRUCTVISULISATION *dstr=&middleBufferData;

    //////////////////////////////////////////////////////
    TDesTarget* tar=bufferData.DesArjObject.DesTarget;
    qDebug("targetsNumbers()=%d\n",targetNumbers());
    for(int i=0;i<targetNumbers();i++)
    {
        if(targetsForm->listTable.size()!=0)
        {
            list.clear();
            list=targetsForm->values(i);
            if(list.size()==21)
            {
                qDebug("list.size()=%d\n",list.size());

                tar[i].fix_relational=  list[0].toFloat();  //1
                tar[i].fiy_relational=  list[1].toFloat();  //2
                tar[i].fiz_relational=  list[2].toFloat();  //3
                tar[i].di_relational=   list[3].toFloat();  //4
                tar[i].pdi_relational=  list[4].toFloat();  //5
                tar[i].v_target=        list[5].toFloat();  //6
                tar[i].vx_target=       list[6].toFloat();  //7
                tar[i].vy_target=       list[7].toFloat();  //8
                tar[i].vz_target=       list[8].toFloat();  //9
                tar[i].x_target=        list[9].toFloat();  //10
                tar[i].y_target=        list[10].toFloat(); //11
                tar[i].z_target=        list[11].toFloat(); //12
                tar[i].psi_target=      list[12].toFloat(); //13
                tar[i].teta_target=     list[13].toFloat(); //14
                tar[i].gama_target=     list[14].toFloat(); //15
                tar[i].fix_relational1= list[15].toFloat(); //16
                tar[i].fiy_relational1= list[16].toFloat(); //17
                tar[i].fiz_relational1= list[17].toFloat(); //18
                tar[i].l_target=        list[18].toFloat(); //19
                tar[i].num_target=      list[19].toInt();   //20
                tar[i].Beg_num_target=  list[20].toInt();   //21
                list.clear();

            }
        }
    }
    //////////////////////////////////////////////////////
    list=tableForms[0]->values();

    kin->psic_aircraft=list[0].toFloat();   //1
    kin->psi_aircraft=list[1].toFloat();    //3
    kin->teta_aircraft=list[2].toFloat();   //2
    kin->tetac_aircraft=list[3].toFloat();  //4
    kin->gamac_aircraft=list[4].toFloat();  //5
    kin->alfa_aircraft=list[5].toFloat();   //6
    kin->beta_aircraft=list[6].toFloat();   //7
    kin->omcx_aircraft=list[7].toFloat();   //8
    kin->omcy_aircraft=list[8].toFloat();   //9
    kin->omcz_aircraft=list[9].toFloat();   //10
    kin->ncx_aircraft=list[10].toFloat();   //11
    kin->ncy_aircraft=list[11].toFloat();   //12
    kin->ncz_aircraft=list[12].toFloat();   //13
    kin->vc_aircraft=list[13].toFloat();    //14
    kin->vcx_aircraft=list[14].toFloat();   //15
    kin->vcy_aircraft=list[15].toFloat();   //16
    kin->vcz_aircraft=list[16].toFloat();   //17
    kin->M_aircraft=list[17].toFloat();     //18
    kin->xc_aircraft=list[18].toFloat();    //19
    kin->yc_aircraft=list[19].toFloat();    //20
    kin->zc_aircraft=list[20].toFloat();    //21
    list.clear();
    //////////////////////////////////////////////////////

    Tkinematiks_aircraftConst* kinConst=&bufferData.Kinematiks_aircraftConst;
    //TDSTRUCTVISULISATION *dstr=&middleBufferData;
    list=tableForms[1]->values();

    //dstr->NVarIsh=list[0].toInt();
    //dstr->FlagNewNVarIsh=list[1].toInt();
    dstr->N_BegFromPult=list[2].toInt();            //1
    dstr->N_EndFromPult=list[3].toInt();            //2
    dstr->TotalNumberVariants=list[4].toInt();      //3
    dstr->NumberTarget=list[5].toInt();             //4
    //dstr->airtarget_Q=list[6].toInt();              //5
    kinConst->ux_aircraft=list[7].toFloat();        //6
    kinConst->uz_aircraft=list[8].toFloat();        //7
    kinConst->beta0_aircraft=list[9].toFloat();     //8
    kinConst->Hbar_aircraft=list[10].toFloat();     //9
    kinConst->Hrvrf_C=list[11].toFloat();           //10
    kinConst->Hrvrfmin_C=list[12].toFloat();        //11
    kinConst->Hrvrfmax_C=list[13].toFloat();        //12
    kinConst->alfarvrf_C=list[14].toFloat();        //13
    kinConst->psirvrf_C=list[15].toFloat();         //14
    kinConst->Htargetrf_C=list[16].toFloat();       //15
    kinConst->Htargetrfmin_C=list[17].toFloat();    //16
    kinConst->Htargetrfmax_C=list[18].toFloat();    //17
    kinConst->psitargetrf_C=list[19].toFloat();     //18
    kinConst->AlfaSM=list[20].toFloat();            //19
    list.clear();
    //////////////////////////////////////////////////////


    Tair_parametrs* air=&bufferData.Air_parametrs;
    Tgeography_Earth *geo=&bufferData.Geography_Earth;
    TDSUOCOM *suoCom=&bufferData.DSUOCOM;

    list=tableForms[2]->values();

    geo->fit_geography=list[0].toFloat();       //0
    geo->limdat_geography=list[1].toFloat();    //1
    geo->Au_geography=list[2].toFloat();        //2
    geo->DeltaM0=list[3].toFloat();             //3
    air->v_dev_airPrev=list[4].toFloat();           //4
    air->Pst_airPrev=list[5].toFloat();             //5
    air->g_airPrev=list[6].toFloat();               //6
    kin->G_engine=list[7].toFloat();            //7
    suoCom->Gasp=list[8].toFloat();             //8

    list=tableForms[3]->values();
    TCommonConst *cConst=&bufferData.CommonConst;
    cConst->TAlfa=list[0].toFloat();            //0
    cConst->TBeta=list[1].toFloat();            //1
    cConst->AlfaBalUst=list[2].toFloat();       //2
    cConst->Knx0=list[3].toFloat();             //3
    cConst->ny_dop=list[4].toFloat();           //4
    cConst->fi_dv=list[5].toFloat();            //5
    cConst->Vmin_C=list[6].toFloat();           //6
    cConst->Hmax_C=list[7].toFloat();           //7
    cConst->Vmin_target=list[8].toFloat();      //8
    cConst->Vmax_target=list[9].toFloat();      //9
    cConst->Mat_min=list[10].toFloat();         //10
    cConst->G0=list[11].toFloat();              //11
    cConst->Gc=list[12].toFloat();              //12


    qDebug("write compleate :cl_DataForVxWorks_Su35_1::sendData()\n");
    //В случае линуха необходимо перевернуть данные

    transmit->sendDatagram((char*)&bufferData);
}

void cl_DataForVxWorks_Su35_1::setData(char* buf)
{
    middleBufferData=*((TDSTRUCTVISULISATION*)buf);

    ptrBufData=&middleBufferData;
    //! Если режим останов, то производиться полное копирование данных
    //! иначе только те котрые нужны
}

void cl_DataForVxWorks_Su35_1::callSlotResived(char* data)
{
    //если линух необходимо довернуть данные
    setData(data);
    emit GenericData::ReciveData();
}
unsigned int cl_DataForVxWorks_Su35_1::counter()
{
    return middleBufferData.Counter;
}
void cl_DataForVxWorks_Su35_1::setControlRegime(ControlReg reg)
{
    switch(reg)
    {
    case KABINA_SAU:        {bufferData.ComRegimeStend.RegimeContr=0;break;}
    case DETERM:            {bufferData.ComRegimeStend.RegimeContr=1;break;}
    case DETERM_CIRCLE:     {bufferData.ComRegimeStend.RegimeContr=2;break;}
    case KABINA_CIRCLE:     {bufferData.ComRegimeStend.RegimeContr=3;break;}
    case TEST_UVOD:         {bufferData.ComRegimeStend.RegimeContr=4;break;}
    case FDR:               {bufferData.ComRegimeStend.RegimeContr=5;break;}
    default:                {qDebug("cl_DataForVxWorks_Su35_1: not correct reg\n");}
    };
}

void cl_DataForVxWorks_Su35_1::setAvtoTiaga(bool flag)
{
    if(flag==true) bufferData.ComRegimeStend.AvtTiaga=1;
    else bufferData.ComRegimeStend.AvtTiaga=0;
}
bool cl_DataForVxWorks_Su35_1::avtoTiaga()
{
    if(middleBufferData.ComRegimeStend.AvtTiaga==1) return true;
    else return false;
}
void cl_DataForVxWorks_Su35_1::setSauIdelPilot(int flag)
{
    if(flag==0)bufferData.ComRegimeStend.SauIdelPilot=0;
    else if(flag==1) bufferData.ComRegimeStend.SauIdelPilot=1;
    else bufferData.ComRegimeStend.SauIdelPilot=2;
}
int cl_DataForVxWorks_Su35_1::sauIdelPilot()
{
    int reg=middleBufferData.ComRegimeStend.SauIdelPilot;

    if(reg==0)return 0;
    else if(reg==1)return 1;
    else return 2;
}
void cl_DataForVxWorks_Su35_1::setDetAerod1(int flag)
{
    if(flag==0)bufferData.ComRegimeStend.DetAerod1=0;
    else if(flag==1) bufferData.ComRegimeStend.DetAerod1=1;
    else bufferData.ComRegimeStend.DetAerod1=2;
}
int cl_DataForVxWorks_Su35_1::detAerod1()
{
    int reg=middleBufferData.ComRegimeStend.DetAerod1;

    if(reg==0)return 0;
    else if(reg==1)return 1;
    else  return 2;
}
void cl_DataForVxWorks_Su35_1::setSerpent(bool flag)
{
    if(flag==true)
    {
        bufferData.ComRegimeStend.Serpent=1;
    }
    else
    {
        bufferData.ComRegimeStend.Serpent=0;
    }
}
bool cl_DataForVxWorks_Su35_1::serpent()
{
    if(middleBufferData.ComRegimeStend.Serpent==1) return true;
    else return false;
}

void cl_DataForVxWorks_Su35_1::setManevrTarget(bool flag)
{
    if(flag==true) bufferData.ComRegimeStend.ManevrTaget=1;
    else bufferData.ComRegimeStend.ManevrTaget=0;
    middleBufferData.ComRegimeStend.ManevrTaget=bufferData.ComRegimeStend.ManevrTaget;
}
bool cl_DataForVxWorks_Su35_1::manevrTarget()
{
    if(middleBufferData.ComRegimeStend.ManevrTaget==1) return true;
    else return false;
}
void cl_DataForVxWorks_Su35_1::setHrv0(double value)
{
    bufferData.Kinematiks_aircraftConst.Hrvrf_C=value;
}
void cl_DataForVxWorks_Su35_1::setHrvmin(double value)
{
    bufferData.Kinematiks_aircraftConst.Hrvrfmin_C=value;
}
void cl_DataForVxWorks_Su35_1::setHrvmax(double value)
{
    bufferData.Kinematiks_aircraftConst.Hrvrfmax_C=value;
}
void cl_DataForVxWorks_Su35_1::setKursRv(double value)
{
    bufferData.Kinematiks_aircraftConst.psirvrf_C=value;
}
void cl_DataForVxWorks_Su35_1::alfaSM(double value)
{
    bufferData.Kinematiks_aircraftConst.AlfaSM=value;
}
void cl_DataForVxWorks_Su35_1::Vminair(double value)
{
    bufferData.CommonConst.Vmin_C=value;
}
void cl_DataForVxWorks_Su35_1::Hmaxair(double value)
{
    bufferData.CommonConst.Hmax_C=value;
}

//#endif
