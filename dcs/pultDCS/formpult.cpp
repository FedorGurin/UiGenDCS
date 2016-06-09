#include "formpult.h"
#include "ui_formpult.h"
#include <QHBoxLayout>
FormPult::FormPult(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormPult)
{
    ui->setupUi(this);
    pultOn_=false;
    engineData=0;
    commonEngineData=0;
    stop_=false;
    start_=false;
    restart_=false;

    kupr_=false;
    regime12_=false;
    lockWrite_=false;

    pixmapRed.load(":/svg/ledRed");
    pixmapGreen.load(":/svg/ledGreen");

    listNamePages.append(tr("Главная страница"));

    palette.setColor(QPalette::Foreground,QColor(Qt::green));
    QVBoxLayout *layoutStart = new QVBoxLayout;

    labelStart=new QLabel("Start",ui->page);
    labelStart->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    labelStart->setPixmap(pixmapRed);

    buttonStart = new QtSvgButton(ui->page);
    buttonStart->setSkin("BerylSquare");
    buttonStart->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);

    layoutStart->addWidget(labelStart);
    layoutStart->addWidget(buttonStart);

    QVBoxLayout *layoutStop = new QVBoxLayout;
    labelStop=new QLabel("Stop",ui->page);

    labelStop->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    labelStop->setPixmap(pixmapRed);

    buttonStop = new QtSvgButton(ui->page);
    buttonStop->setSkin("BerylSquareStop");
    buttonStop->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);

    scrollWheelPages=new QtScrollWheel(ui->frameWheel);
    scrollWheelPages->setRange(0, 40);
    scrollWheelPages->setValue(0);
    scrollWheelPages->setSkin("Beryl");
    ui->frameWheel->setVisible(true);
    buttonNextVariant=new QtSvgButton(ui->frameNextVar);
    //buttonNextVariant->setSkin("Beryl");
    buttonNextVariant->setToolTip(tr("Следующий подвариант"));

    //layoutWheel->addWidget(scrollWheelPages);

    layoutStop->addWidget(labelStop);
    layoutStop->addWidget(buttonStop);

    QVBoxLayout *layoutRestart = new QVBoxLayout;
    labelRestart=new QLabel("Start",ui->page);
    labelRestart->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    labelRestart->setPixmap(pixmapRed);

    buttonRestart = new QtSvgButton(ui->page);
    buttonRestart->setSkin("BerylSquareRestart");
    buttonRestart->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);

    layoutRestart->addWidget(labelRestart);
    layoutRestart->addWidget(buttonRestart);

    QVBoxLayout *layoutSliders = new QVBoxLayout;
    slideKupr=new QtSvgSlideSwitch(ui->page);
    slideKupr->setSkin("BerylKUpr");
    slideKupr->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    slideKupr->setChecked(true);
    slideKupr->setToolTip(tr("При включенном тумблере и при нажатии на исходное долгота и широта местоположения носителя берется из [Установки географии земли], иначе долгота и широта будут равны текущим значениям"));
    layoutSliders->addWidget(slideKupr);


    slideRegime12=new QtSvgSlideSwitch(ui->page);
    slideRegime12->setSkin("BerylRegime12");
    slideRegime12->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    layoutSliders->addWidget(slideRegime12);

    slideLockWrite=new QtSvgSlideSwitch(ui->page);
    slideLockWrite->setSkin("BerylLockWrite");
    slideLockWrite->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    layoutSliders->addWidget(slideLockWrite);

    slideOnVPult=new QtSvgSlideSwitch(ui->page);
    slideOnVPult->setSkin("BerylVirtPult");
    slideOnVPult->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    layoutSliders->addWidget(slideOnVPult);

    QHBoxLayout *layoutS = new QHBoxLayout;
    layoutS->addLayout(layoutSliders,0);
    layoutS->addLayout(layoutStart,0);
    layoutS->addLayout(layoutStop,0);
    layoutS->addLayout(layoutRestart,0);
    ui->page->setLayout(layoutS);

    engineVPult=new EngineVPult;
    settingPultPNM=new SettingPultPNM;

    connect(buttonStop,             SIGNAL(pressed()),this,SLOT(setButtonStop()));
    connect(buttonStart,            SIGNAL(pressed()),this,SLOT(setButtonStart()));
    connect(buttonRestart,          SIGNAL(pressed()),this,SLOT(setButtonRestart()));

    connect(buttonStop,             SIGNAL(released()),this,SLOT(releasedStop()));
    connect(buttonStart,            SIGNAL(released()),this,SLOT(releasedStart()));
    connect(buttonRestart,          SIGNAL(released()),this,SLOT(releasedRestart()));

    //! для движка данных
    connect(engineVPult,            SIGNAL(pushStop()),this,SLOT(setButtonStop()));
    connect(engineVPult,            SIGNAL(releasedStop()),this,SLOT(releasedStop()));

    connect(engineVPult,            SIGNAL(pushStart()),this,SLOT(setButtonStart()));
    connect(engineVPult,            SIGNAL(releasedStart()),this,SLOT(releasedStart()));

    connect(engineVPult,            SIGNAL(pushRestart()),this,SLOT(setButtonRestart()));
    connect(engineVPult,            SIGNAL(releasedRestart()),this,SLOT(releasedRestart()));

    connect(engineVPult,            SIGNAL(pushOn(bool)),this,SLOT(checkedVPult(bool)));
    connect(engineVPult,            SIGNAL(pushSlideKupr(bool)),this,SLOT(checkedSlideKupr(bool)));
    connect(engineVPult,            SIGNAL(pushSlideRegime12(bool)),this,SLOT(checkedSlideRegime12(bool)));
    connect(engineVPult,            SIGNAL(pushSlideLockWrite(bool)),this,SLOT(checkedLockWrite(bool)));

    connect(engineVPult,            SIGNAL(readStop(QString&)),this,SLOT(slotReadStop(QString&)));
    connect(engineVPult,            SIGNAL(readStart(QString&)),this,SLOT(slotReadStart(QString&)));
    connect(engineVPult,            SIGNAL(readRestart(QString&)),this,SLOT(slotReadRestart(QString&)));
    //////////////////////////////////////////////////////////////////////////////////////////////////

    connect(slideOnVPult,           SIGNAL(toggled(bool)),this,SLOT(setSlideOnVPult(bool)));
    connect(slideKupr,              SIGNAL(toggled(bool)),this,SLOT(setSlideKupr(bool)));
    connect(slideRegime12,          SIGNAL(toggled(bool)),this,SLOT(setSlideRegime12(bool)));
    connect(slideLockWrite,         SIGNAL(toggled(bool)),this,SLOT(setSlideLockWrite(bool)));
    connect(scrollWheelPages,       SIGNAL(valueChanged(int)),this,SLOT(slotChangePages(int)));

    ui->labelNamePage->setPalette(palette);
    ui->labelNPages->setPalette(palette);

    setSlideOnVPult(pultOn_);
    slotChangePages(settingPultPNM->defaultNumPage*10);
    if(settingPultPNM->defaultVirtPult==1) hide();
    else show();
}
void FormPult::refreshAll()
{
    /*qDebug("pultPNM refreshAll()\n");
    printf("pultPNM refreshAll()\n");
    QString value;

    uint uid;
    uid=commonEngineData->getValue(tr("UI.Kupr"),value);
    if(uid==0) qDebug("No found UI.Kupr");

    checkedSlideKupr(value.toInt());

    uid=commonEngineData->getValue(tr("UI.Regim12"),value);
    if(uid==0) qDebug("No found UI.Regime12");

    checkedSlideRegime12(value.toInt());

    uid=commonEngineData->getValue(tr("UI.VPult"),value);
    if(uid==0) qDebug("No found UI.VPult");

    if(value.toInt()==1)  checkedVPult(false);
    else  checkedVPult(true);

    uid=commonEngineData->getValue(tr("UI.LockWrite"),value);
    if(uid==0) qDebug("No found UI.LockWrite");

    checkedLockWrite((value.toInt()));

    TRequestEvent request;
    slotEventsRequest(request);*/
}

void FormPult::slotReadStop(QString& value)
{
    value=stop_;
}
void FormPult::slotReadStart(QString& value)
{
    value=start_;
}
void FormPult::slotReadRestart(QString& value)
{
    value=restart_;
}
void FormPult::setEngineData(EngineData *engine)
{  
    engineData=engine;
    //! парсеры
    parser=new ParserXMLPult(engineData);

    QHBoxLayout *layoutPage1 = new QHBoxLayout;
    QHBoxLayout *layoutPage2 = new QHBoxLayout;
    QHBoxLayout *layoutPage3 = new QHBoxLayout;
    QHBoxLayout *layoutPage4 = new QHBoxLayout;

    QVector<ToggleSwitch* > *list=parser->retList();
    for(int i=0;i<list->size();i++)
    {
        if((*list)[i]->page()==1)
        {
            layoutPage1->addLayout(((*list)[i])->layoutV,0);
        }else if((*list)[i]->page()==2)
        {
            layoutPage2->addLayout(((*list)[i])->layoutV,0);
        }else if((*list)[i]->page()==3)
        {
            layoutPage3->addLayout(((*list)[i])->layoutV,0);
        }else if((*list)[i]->page()==4)
        {
            layoutPage4->addLayout(((*list)[i])->layoutV,0);
        }
    }
    ui->page_1->setLayout(layoutPage1);
    ui->page_2->setLayout(layoutPage2);
    ui->page_3->setLayout(layoutPage3);
    ui->page_4->setLayout(layoutPage4);


    listNamePages.append(parser->names());
    //checkBlockButton();
    connect(engineData,SIGNAL(signalEventsRequest(TRequestEvent)),this,SLOT(slotEventsRequest(TRequestEvent)));
}

void FormPult::slotEventsRequest(TRequestEvent req)
{

    if(req.uid == event.uid)
    {
        qDebug("Answer FORM_PULT in slotEventsRequest\n");
    }
    /*
    QVector<ToggleSwitch* > *list=parser->retList();
    for(int i=0;i<list->size();i++)
    {
        (*list)[i]->setToggle();
    }*/
}


void FormPult::slotChangePages(int index_)
{
    //float mod=index_%10;
    int index=0;

    index=index_/10;
    ui->stackedWidget->setCurrentIndex(index);
    ui->labelNPages->setText(QString::number(index)+"/"+QString::number(ui->stackedWidget->count()-1));
    if(index<listNamePages.size())
        ui->labelNamePage->setText(listNamePages[index]);
    else ui->labelNamePage->setText(tr("не задано"));

}
void FormPult::setVPult(bool f)
{
    slideOnVPult->setChecked(f);
}

void FormPult::setRegime12(bool f)
{
    slideRegime12->setChecked(f);
}

void FormPult::setKupr(bool f)
{
    slideKupr->setChecked(f);
}

void FormPult::setSlideOnVPult(bool f)
{
    //! Только для ТЕСТА
    if(commonEngineData!=0)
    {
        TCommonRequest request;
        request.setSender("VPult");
        request.setReciver("MPPM");
        request.append("Models.Setup.RV","0");
        request.append("Models.Setup.ARK","0");
        request.append("Models.Setup.BKS","0");

        event=commonEngineData->getValue(request,IEngineData::CYCLIC_ENGINE);
        //QString value=event.value[0];
    }
    ////////////////////////////////////////////
    pultOn_=f;
    if(pultOn_==true)
    {

        buttonRestart->setEnabled(true);
        buttonStop->setEnabled(true);
        buttonStart->setEnabled(true);

        slideRegime12->setEnabled(true);
        slideKupr->setEnabled(true);
        slideLockWrite->setEnabled(true);
    }else
    {

        buttonRestart->setEnabled(false);
        buttonStop->setEnabled(false);
        buttonStart->setEnabled(false);

        slideRegime12->setEnabled(false);
        slideKupr->setEnabled(false);
        slideLockWrite->setEnabled(false);
    }

    emit refresh();
}
void FormPult::createSlider()
{

}

void FormPult::createButtons()
{

}

void FormPult::createToggle()
{

}

void FormPult::setSlideRegime12(bool f)
{
    regime12_=f;
    emit refresh();
}

void FormPult::setSlideKupr(bool f)
{
    //! только для тестирования
    TCommonRequest request;
    request.setSender("VPult");
    request.setReciver("MPPM");
    request.append("RemoveAllCyclic");
    TRequestEvent event=commonEngineData->command(request,IEngineData::SYNCH_ENGINE);

    ///////////////////////////////////////////////////////
    kupr_=f;
    emit refresh();
}
void FormPult::setSlideLockWrite(bool f)
{
    lockWrite_=f;
    emit refresh();
}
void FormPult::releasedStop()
{
    stop_=false;
    emit refresh();
}
void FormPult::releasedStart()
{
    start_=false;
    emit refresh();
}
void FormPult::releasedRestart()
{
    restart_=false;
    emit refresh();
}

void FormPult::setButtonStop()
{
    stop_=true;
    emit refresh();
}
void FormPult::setButtonStart()
{
    start_=true;
    emit refresh();
}
void FormPult::setButtonRestart()
{
    restart_=true;
    emit refresh();
}
void FormPult::setLedStop()
{
    labelStart->setPixmap(pixmapRed);
    labelStop->setPixmap(pixmapGreen);
    labelRestart->setPixmap(pixmapRed);
}
void FormPult::setLedStart()
{
    labelStart->setPixmap(pixmapGreen);
    labelStop->setPixmap(pixmapRed);
    labelRestart->setPixmap(pixmapRed);
}
void FormPult::setLedRestart()
{
    labelStart->setPixmap(pixmapRed);
    labelStop->setPixmap(pixmapRed);
    labelRestart->setPixmap(pixmapGreen);
}
void FormPult::setLedReset()
{
    labelStart->setPixmap(pixmapRed);
    labelStop->setPixmap(pixmapRed);
    labelRestart->setPixmap(pixmapRed);
}

void FormPult::checkedSlideRegime12(bool v)
{
    slideRegime12->setChecked(v);
    if(pultOn()==false) slideRegime12->setEnabled(false);
}

void FormPult::checkedSlideKupr(bool v)
{
    slideKupr->setChecked(v);
    if(pultOn()==false) slideKupr->setEnabled(false);
}

void FormPult::checkedVPult(bool v)
{
    slideOnVPult->setChecked(v);
}

void FormPult::checkedLockWrite(bool v)
{
    slideLockWrite->setChecked(v);
    if(pultOn()==false) slideLockWrite->setEnabled(false);
}

FormPult::~FormPult()
{
    delete ui;
}


