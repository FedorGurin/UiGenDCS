#include "cl_MainFormSocket.h"

#include <QColor>
#include "../globalFunc/gl_func.h"
#include "../globalFunc/Matrix3D_D.h"
#include <QTranslator>


//#define AUTOLOCK
double t=0.0;

cl_MainFormSocket::cl_MainFormSocket(GenericData* ptr)
{
    setupUi(this);
    data=0;
    data=ptr;
    curWindow=0;
    regime_prev=NO_REGIME;
    int touch=readParamFromXMLFile(nameMainFile,"UI","Touch").toInt();
    QString nameStend=readParamFromXMLFile(nameMainFile,"UI","typeGlobalDefs");
    commonEngineData=new CommonEngineData;
    formSettings=new FormSettingsAll;
    help=new MainWindowHelp(this);
    //режим ОВК
    ovk=0;
    if(nameStend!="Su35_1")
    {
        menu->removeAction(actionOVK);
    }else
    {
        ovk=new OVK;
        ovk->setCommonEngineData(commonEngineData);
    }

    engineDataUI=new EngineDataUI(data);
    connect(engineDataUI,SIGNAL(refreshCommand()),this,SLOT(slot_pushButtonRefresh()));
    //! указатель на движок
    visualVar=new VisualVariant::MainWindowVisVar(commonEngineData);

    if(touch==1)
    {
        QGridLayout *layout= new QGridLayout(pageMPPM);
        mppm=new xmlmodelview(pageMPPM);
        layout->addWidget(mppm);
    }else
        mppm=new xmlmodelview();

    //! указатель на движок
    mppm->setCommonEngine(commonEngineData);
    //! класс сетевого взаимодействия
    networkCommunication=new NetworkCommunication;
    //! потеря соединения
    connect(networkCommunication,SIGNAL(connectionLost()),mppm,SLOT(slotConnectionLost()));
    data->setTransmitObject(new Transmit(networkCommunication));
    connect(networkCommunication,SIGNAL(ready()),this,SLOT(slotReadyNetworkCommunication()));
   // connect(networkCommunication,SIGNAL(connectionFind()),mppm,SLOT(slotConnectionFind()));

    //! имитатор СУО
    ///////////////////////////////////////////////////
    if(nameStend == "Su35_1")
    {
        widgetComSusp = new WidgetComSusp();
        for(int i = 0; i < 12; i++)
        {
            widgetComSusp->gruz[i]->cED = commonEngineData;//unused
            widgetComSusp->gruz[i]->eD = mppm->engineData;
        }
        widgetComSusp->setEngine(mppm->engineData);
        widgetComSusp->mppm = mppm;
        actionComSusp->setEnabled(true);
    }else
        actionComSusp->setEnabled(false);
    ///////////////////////////////////////////////////

    trans3DWorld=new Trans3DWorld;
    trans3DWorld->setCommonEngine(commonEngineData);

    formPult=new FormPult();
    formPult->setWindowFlags(Qt::WindowTitleHint | Qt::WindowStaysOnTopHint |Qt::WindowCloseButtonHint);
   // formPult->setEngineData(mppm->engineData);
    formPult->setCommonEngineData(commonEngineData);

    editorScript=new EditorScript;
    editorScript->translator->commonEngineData=commonEngineData;
    connect(formPult,SIGNAL(refresh()),this,SLOT(slot_refreshPultPNM()));

    palette[0].setColor(QPalette::Foreground,QColor(Qt::green));
    palette[1].setColor(QPalette::Foreground,QColor(Qt::red));
    palette[2].setColor(QPalette::Foreground,QColor(Qt::blue));

    paletteButton[0].setColor(QPalette::Text,QColor(Qt::green));
    paletteButton[1].setColor(QPalette::Text,QColor(Qt::red));

    connect(pushButtonRefresh,  SIGNAL(clicked()),this,             SLOT(slot_pushButtonRefresh()));
    connect(pushButtonRestart,  SIGNAL(pressed()),this,             SLOT(slot_pressedButtonRestartModel()));
    connect(pushButtonRestart,  SIGNAL(released()),this,            SLOT(slot_relesedButtonRestartModel()));
    connect(menu,               SIGNAL(triggered(QAction*)),this,   SLOT(slotTriggered(QAction*)));
    connect(menu_4,             SIGNAL(triggered(QAction*)),this,   SLOT(slotTriggeredMenuLang(QAction*)));
    connect(menuSettings,       SIGNAL(triggered(QAction*)),this,   SLOT(slotTriggeredMenuSettings(QAction*)));
    connect(menuNetworkSwitch,  SIGNAL(triggered(QAction*)),this,   SLOT(slotTriggeredMenuNetworkSwitch(QAction*)));
    connect(menuHelp,           SIGNAL(triggered(QAction*)),this,   SLOT(slotTriggeredMenuHelp(QAction*)));

    for(int i=0;i<4;i++)
    {
        tableForms.push_back(new cl_TableFormSocket());
        //connect(tableForms.last(),SIGNAL(itemChanged()),this,SLOT(slot_pushButtonSend()));
    }

    connect(pushButtonTar,          SIGNAL(clicked()),this,SLOT(slot_pushButtonTar()));
    connect(pushButtonConst,        SIGNAL(clicked()),this,SLOT(slot_pushButtonConst()));
    connect(pushButtonAtmGeo,       SIGNAL(clicked()),this,SLOT(slot_pushButtonAtmGeo()));
    connect(pushButtonKin,          SIGNAL(clicked()),this,SLOT(slot_pushButtonKin()));

    connect(spinBoxNumVariant,      SIGNAL(valueChanged(int)),this,SLOT(slotSpinBoxVariant(int)));

    connect(buttonBeginCommonConst, SIGNAL(clicked()),this,SLOT(slot_pushBeginCommonConst()));
    connect(toolButtonVariant,      SIGNAL(clicked(bool)),this,SLOT(slotClickedIsx()));

    connect(radioKab,       SIGNAL(toggled(bool)),this,SLOT(slot_radioButtonsUpr()));
    connect(radioDet,       SIGNAL(toggled(bool)),this,SLOT(slot_radioButtonsUpr()));
    connect(radioDetCircle, SIGNAL(toggled(bool)),this,SLOT(slot_radioButtonsUpr()));
    connect(radioKabCircle, SIGNAL(toggled(bool)),this,SLOT(slot_radioButtonsUpr()));
    connect(radioUvod,      SIGNAL(toggled(bool)),this,SLOT(slot_radioButtonsUpr()));
    connect(radioFDR,       SIGNAL(toggled(bool)),this,SLOT(slot_radioButtonsUpr()));

    //! таблицы с целями
    targetsForm=new cl_TargetsForm;
    //! cоздаем данные
    data->setTableForm(tableForms);
    data->setTargetsForm(targetsForm);
    connect(data,SIGNAL(ReciveData()),this,SLOT(slotIsResived()));

    QFont f("Helvetica", 12, QFont::Bold);
    labelRegime->setFont(f);

    //! создаем окна
    loadData();

#ifdef AUTOLOCK
    this->setEnabled(false);
#endif

    connect(networkCommunication,   SIGNAL(connectionLost()),this,SLOT(slotTimeout()));
    connect(networkCommunication,   SIGNAL(connectionFind()),this,SLOT(slotConnectionFind()));

    //!подключаем реакцию на выборе checkBox`ах
    connect(pushButtonComUst,       SIGNAL(clicked()),this,SLOT(slotClickedSend()));
    connect(toolButtonVariant,      SIGNAL(clicked()),this,SLOT(slotClickedSend()));

    connect(radioKab,               SIGNAL(toggled(bool)),this,SLOT(slotToggledRadio(bool)));
    connect(radioDet,               SIGNAL(toggled(bool)),this,SLOT(slotToggledRadio(bool)));
    connect(radioDetCircle,         SIGNAL(toggled(bool)),this,SLOT(slotToggledRadio(bool)));
    connect(radioKabCircle,         SIGNAL(toggled(bool)),this,SLOT(slotToggledRadio(bool)));
    connect(radioUvod,              SIGNAL(toggled(bool)),this,SLOT(slotToggledRadio(bool)));
    connect(radioFDR,               SIGNAL(toggled(bool)),this,SLOT(slotToggledRadio(bool)));

    connect(radioButtonRUD,         SIGNAL(toggled(bool)),this,SLOT(slotToggledRadio(bool)));
    connect(radioButtonAvtoTiaga,   SIGNAL(toggled(bool)),this,SLOT(slotToggledRadio(bool)));

    connect(radioButtonProdChannel, SIGNAL(toggled(bool)),this,SLOT(slotToggledRadio(bool)));
    connect(radioButtonSAUAvtopilot,SIGNAL(toggled(bool)),this,SLOT(slotToggledRadio(bool)));
    connect(radioButtonAvtoCancel,  SIGNAL(toggled(bool)),this,SLOT(slotToggledRadio(bool)));


    connect(radioButtonAerod1,      SIGNAL(toggled(bool)),this,SLOT(slotToggledRadio(bool)));
    connect(radioButtonDeter,       SIGNAL(toggled(bool)),this,SLOT(slotToggledRadio(bool)));
    connect(radioButtonCancel,      SIGNAL(toggled(bool)),this,SLOT(slotToggledRadio(bool)));

    connect(radioButtonLinearMotion,SIGNAL(toggled(bool)),this,SLOT(slotToggledRadio(bool)));
    connect(radioButtonSerpent,     SIGNAL(toggled(bool)),this,SLOT(slotToggledRadio(bool)));
    connect(checkBoxManevrTaget,    SIGNAL(toggled(bool)),this,SLOT(slotToggledRadio(bool)));

    //! связываем изменение элементов с посылкой данных в УЦВС
    connect(targetsForm,SIGNAL(itemChanged()),this,SLOT(slot_pushButtonSend()));
    for(int i=0;i<tableForms.size();i++)
    {
        connect(tableForms[i],      SIGNAL(itemChanged()),this,SLOT(slot_pushButtonSend()));
    }

//    commonEngineData->addEngine(formPult->engineVPult);
    //! добавляем движки каждого модуля в обобщенный движок
    commonEngineData->addEngine(mppm->engineData);
    commonEngineData->addEngine(engineDataUI);
    commonEngineData->addEngine(visualVar->engineVariant);

    //! разрешаем жесты
    //grabGesture(Qt::PanGesture);
    //grabGesture(Qt::SwipeGesture);

    buttonVar=new QToolButton;
    buttonVar->setIcon(QIcon(":/png/var"));
    buttonVar->setToolTip(tr("Редактор вариантов"));
    toolBar->addWidget(buttonVar);

    buttonPM=new QToolButton;
    buttonPM->setIcon(QIcon(":/png/pm"));
    buttonPM->setToolTip(tr("Просмотр/изменение параметров БРЭО"));
    toolBar->addWidget(buttonPM);

    buttonPult=new QToolButton;
    buttonPult->setIcon(QIcon(":/svg/pult"));
    buttonPult->setToolTip(tr("Пульт ПНМ"));
    toolBar->addWidget(buttonPult);


    buttonTest=new QToolButton;
    buttonTest->setIcon(QIcon(":/png/bullet"));
    buttonTest->setToolTip(tr("Автоматические тесты"));
    toolBar->addWidget(buttonTest);

    if(touch!=0)
    {
        buttonPrev=new QToolButton;
        buttonPrev->setIcon(QIcon(":/png/arrowLeft"));
        buttonPrev->setToolTip(tr("Назад"));
        toolBar->addWidget(buttonPrev);

        buttonNext=new QToolButton;
        buttonNext->setIcon(QIcon(":/png/arrowRight"));
        buttonNext->setToolTip(tr("Вперед"));
        toolBar->addWidget(buttonNext);

        connect(buttonPrev,SIGNAL(clicked()),this,SLOT(goPrevWidget()));
        connect(buttonNext,SIGNAL(clicked()),this,SLOT(goNextWidget()));
    }

    connect(buttonPult,SIGNAL(clicked()),this,SLOT(slot_toolButtonPult()));
    connect(buttonPM,  SIGNAL(clicked()),this,SLOT(slot_toolButtonPM()));
    connect(buttonTest,SIGNAL(clicked()),this,SLOT(slot_toolButtonTest()));
    connect(buttonVar, SIGNAL(clicked()),this,SLOT(slot_toolButtonVariant()));

    //pushButtonComUst->setPalette(palette[1]);

    show();
}

void cl_MainFormSocket::slotTriggeredMenuSettings(QAction *act)
{
    qDebug("slotTriggeredMenuSettings");
    if(act==actionProfile)
    {
        if(actionProfile->isChecked()==true)
        {
            formSettings->show();
        }else
        {
            formSettings->hide();
        }
    }
}
void cl_MainFormSocket::slotTriggeredMenuHelp(QAction* act)
{
    if(act==actionHelp)
    {
        help->showHelp("3dworld");
    }
}
void cl_MainFormSocket::slotTriggeredMenuNetworkSwitch(QAction* act)
{
    if(act==actionPKIPOn)
    {
        networkCommunication->wolPKIP();
    }
    if(act==actionUCVSOn)
    {
        networkCommunication->wolUCVS();
    }
    if(act==actionIOSOOn)
    {
        networkCommunication->wolIOSO();
    }
    if(act==actionConsoleOn)
    {
        networkCommunication->wolRemoteConsole();
    }
}
void cl_MainFormSocket::slot_pressedButtonRestartModel()
{
    data->pressButtonRestartModel(true);
    slot_pushButtonSend();
}
void cl_MainFormSocket::slot_relesedButtonRestartModel()
{
    data->pressButtonRestartModel(false);
    slot_pushButtonSend();
}
void cl_MainFormSocket::slotClickedSend()
{
    slot_pushButtonSend();
}

void cl_MainFormSocket::slotToggledRadio(bool f)
{
    if(f==true)
    {
        slot_pushButtonSend();
    }
}

void cl_MainFormSocket::wolPKIP()
{
    QByteArray array;
    QByteArray byteArray_;

    array.clear();
    byteArray_.clear();
    byteArray_.append((char)0x00);
    byteArray_.append((char)0xD0);
    byteArray_.append((char)0xC9);
    byteArray_.append((char)0xAC);
    byteArray_.append((char)0x42);
    byteArray_.append((char)0xE5);

    for(int i=0;i<6;i++)
    {
        array.append(QByteArray(0xFF,1));
    }
    for(int i=0;i<16;i++)
    {
        array.append(byteArray_);
    }
    socket.writeDatagram(array,QHostAddress::Broadcast,5);
}

void cl_MainFormSocket::switchLang(int i)
{
    QTranslator translator;
    if(i==0)
    {
        qDebug("setEnglish lang");
        translator.load("ui_fedor_eng",qApp->applicationDirPath());
    }else if(i==1)
    {
        qDebug("setRussian lang");
        translator.load("ui_fedor_ru",qApp->applicationDirPath());
    }
    qApp->installTranslator(&translator);
    this->retranslateUi(this);
}
void cl_MainFormSocket::slotReadyNetworkCommunication()
{
    //! мне нужно поменять на другой порт
    if(networkCommunication->mainProgram==false)
    {
        this->labelStatus->setText(tr("Ведомая"));
    }else this->labelStatus->setText(tr("Ведущая"));
}
void cl_MainFormSocket::slotSpinBoxVariant(int value)
{
    data->setNumVariant(value);
}

void cl_MainFormSocket::slot_toolButtonOpenVariant()
{
   //settingVariantsFile->openNetDisk(lineEditFileName->text());
}
void cl_MainFormSocket::slot_refreshPultPNM(void)
{
    static bool flag=false;

    if(data->transmit->firstRecive()==false) return;

    if(formPult->pultOn()==true)
    {
        data->pressButtonOnVirtualPult(0);
        flag=false;
        if(formPult->stop()==true)
        {
            data->pressButtonStop();
        }
        if(formPult->start()==true)
        {
            data->pressButtonStart();
        }
        if(formPult->restart()==true)
        {
            data->pressButtonRestart();
        }
        data->pressButtonKupr(formPult->kupr());
        data->pressButtonLockWrite(formPult->lockWrite());
        data->pressButtonRegim12(formPult->regime12());
        data->sendData();
    }else
    {
        //! включение реального пульта
        data->pressButtonOnVirtualPult(1);

        if(flag==false)
            data->sendData();

        flag=true;
    }
}
void cl_MainFormSocket::slot_checkBoxComUst()
{
    //qDebug("cl_MainFormSocket::slot_checkBoxComUst()\n");

    data->setComUst(pushButtonComUst->isChecked());
}
void cl_MainFormSocket::slotClickedIsx()
{
    //qDebug("cl_MainFormSocket::slotClickedIsx()\n");

    data->setPrNewVariant(toolButtonVariant->isChecked());
    /*if(toolButtonVariant->isChecked()==true)
    {
        data->setPrNewVariant(true);
    }else
    {
        data->setPrNewVariant(false);
    }*/
}
void cl_MainFormSocket::slot_toolButtonPM()
{
    mppm->show();
    mppm->showNormal();
    mppm->setFocus();
}
void cl_MainFormSocket::slot_toolButtonPult()
{
    formPult->show();
    formPult->showNormal();
    formPult->setFocus();
}
void cl_MainFormSocket::slot_toolButtonTest()
{
    editorScript->show();
    editorScript->showNormal();
    editorScript->setFocus();
}
void cl_MainFormSocket::slot_toolButtonVariant()
{
    visualVar->show();
    visualVar->showNormal();
    visualVar->setFocus();
}
void cl_MainFormSocket::slot_toolComSusp()
{
    widgetComSusp->show();
    widgetComSusp->showNormal();
    widgetComSusp->setFocus();
}
void cl_MainFormSocket::slot_radioButtonsUpr(void)
{
    bool flags[4]={true,true,true,true};
    if(radioKab->isChecked()==true)
    {
        flags[0]=false;
    }
    else if(radioDet->isChecked()==true)
    {
        flags[1]=false;
        flags[2]=false;
    }
    else if(radioDetCircle->isChecked()==true )
    {
        flags[0]=true;
        flags[1]=false;
        flags[2]=false;
        flags[3]=false;
    }else if(radioUvod->isChecked()==true)
    {
        flags[0]=false;
        flags[1]=false;
        flags[2]=false;
        flags[3]=false;
    }
    else if(radioKabCircle->isChecked()==true)
    {
        flags[0]=false;
        flags[1]=false;
        flags[2]=false;
    }
    else if(radioFDR->isChecked()==true)
    {
        //groupBoxFunc->setEnabled(true);
    }
    groupBoxDvi->setEnabled(flags[0]);
    groupBoxEngine->setEnabled(flags[1]);
    groupBoxAuto->setEnabled(flags[2]);
    groupBoxAerod1->setEnabled(flags[3]);
}
bool cl_MainFormSocket::event(QEvent *e)
{
    //! обработка "жестов"
    if(e->type() == QEvent::Gesture)
        return gestureEvent(static_cast<QGestureEvent*>(e));

    if(e->type()==QEvent::Close)//! Если закрыли это окно
    {
        qApp->quit();
    }
    return QWidget::event(e);
}
void cl_MainFormSocket::slotTriggered(QAction *act)
{
    if(act == actionViewPM)
    {
        mppm->show();
        mppm->showNormal();
        mppm->setFocus();
    }
    if(act == actionPultPNM)
    {
        formPult->show();
        formPult->showNormal();
        formPult->setFocus();
    }
    if(act == actionView3DArea)
    {
        //! запустить программу 3D просмотра
        QProcess::startDetached("./3dWorld.exe");
    }
    if(act == actionVarEdir)
    {
        visualVar->show();
        visualVar->showNormal();
        visualVar->setFocus();
    }
    if(act == actionTest)
    {
        editorScript->show();
        editorScript->showNormal();
        editorScript->setFocus();
    }
    if(act == actionOVK && ovk!=0)
    {
        ovk->show();
        ovk->showNormal();
        ovk->setFocus();
    }
    if(act == actionComSusp)
    {
        widgetComSusp->show();
        widgetComSusp->showNormal();
        widgetComSusp->setFocus();
    }
}
void cl_MainFormSocket::slotTriggeredMenuVar(QAction* act)
{
    if(act==actionNU)
    {

    }
}
void cl_MainFormSocket::slotTriggeredDebug(QAction* act)
{
    if(act==actionNext)
    {
        //! переход к следующей странице
        goNextWidget();
    }
    if(act==actionPrev)
    {
        //! переход в предыдущей странице
        goPrevWidget();
    }
}


void cl_MainFormSocket::slotTriggeredMenuLang(QAction* act)
{
    if(act == actionRussian)
        switchLang(1);
    if(act == actionEnglish)
        switchLang(0);
}
void cl_MainFormSocket::slotTimeout()
{

    ///if(isDataRecived==false)
    //{
        labelRegime->setPalette(palette[2]);
        labelRegime->setText(tr("Ожидание данных...\nЗагрузи модель"));

#ifdef AUTOLOCK
        this->setEnabled(false);
#endif
    //}
}
void cl_MainFormSocket::slotConnectionFind()
{
    //qDebug("cl_MainFormSocket::slotConnectionFind");
    formPult->refreshAll();
}

void cl_MainFormSocket::slot_checkedCircle(int state)
{
    Q_UNUSED(state);
}
void cl_MainFormSocket::slot_pushButtonRefresh(void)
{
    if(data->transmit->firstRecive()==true) //если данные были хоть раз приняты, то можно обновить форму
    {
        //////////////! блокируем обновление///////////////////////////
        targetsForm->setBlockItemChanged(true);
        pushButtonRefresh->setEnabled(false);
        for(int i=0;i<tableForms.size();i++)
        {
            tableForms[i]->setBlockItemChanged(true);
        }
        ///////////////////////////////////////////////////////////////
        refreshData();
        formPult->refreshAll();
        ///////////////////////////////////////////////////////////////
        //////////////! разблокируем обновление////////////////////////
        targetsForm->setBlockItemChanged(false);
        pushButtonRefresh->setEnabled(true);
        for(int i=0;i<tableForms.size();i++)
        {
            tableForms[i]->setBlockItemChanged(false);
        }
        ///////////////////////////////////////////////////////////////
    }
}
void cl_MainFormSocket::loadData(void)
{
    data->createFormKinAircraft();
    data->createFormConst();
    data->createFormAtmGeo();
    data->createFormTargets();
    data->createFormCommonConst();
}

//Отправить данные
void cl_MainFormSocket::slot_pushButtonSend(void)
{
    qDebug("cl_MainFormSocket::slot_pushButtonSend(void)\n");

    if(data->transmit->firstRecive()==false) return;
    qDebug("cl_MainFormSocket::slot_pushButtonSend()+firstRecive()==true\n");

    if(radioKab->isChecked() == true)         data->setControlRegime(KABINA_SAU);
    if(radioDet->isChecked() == true)         data->setControlRegime(DETERM);
    if(radioDetCircle->isChecked() == true)   data->setControlRegime(DETERM_CIRCLE);
    if(radioKabCircle->isChecked() == true)   data->setControlRegime(KABINA_CIRCLE);
    if(radioUvod->isChecked() == true)        data->setControlRegime(TEST_UVOD);
    if(radioFDR->isChecked() == true)         data->setControlRegime(FDR);

    if(radioButtonAvtoTiaga->isChecked()==true) data->setAvtoTiaga(true);
    else data->setAvtoTiaga(false);

    if(radioButtonAerod1->isChecked()==true)    data->setDetAerod1(0);
    if(radioButtonDeter->isChecked()==true)     data->setDetAerod1(1);
    if(radioButtonCancel->isChecked()==true)    data->setDetAerod1(2);

    if(radioButtonProdChannel->isChecked()==true)   data->setSauIdelPilot(0);
    if(radioButtonSAUAvtopilot->isChecked()==true)  data->setSauIdelPilot(1);
    if(radioButtonAvtoCancel->isChecked()==true)    data->setSauIdelPilot(2);

    if(radioButtonLinearMotion->isChecked()==true)  data->setSerpent(false);
    else data->setSerpent(true);

    if(checkBoxManevrTaget->isChecked()==true) data->setManevrTarget(true);
    else data->setManevrTarget(false);

    slot_checkBoxComUst();
    slotClickedIsx();

    qDebug("sendData()\n");
    data->sendData();
}
void cl_MainFormSocket::slot_pushButtonTar(void)
{
    targetsForm->setWindowTitle(tr("Параметры целей"));
    targetsForm->show();
}
void cl_MainFormSocket::slot_pushButtonConst(void)
{
    tableForms[1]->setWindowTitle(tr("Номера исходных вариантов и общие константы"));
    tableForms[1]->show();
}
void cl_MainFormSocket::slot_pushButtonAtmGeo(void)
{
    tableForms[2]->setWindowTitle(tr("Географические и атмосферные параметры"));
    tableForms[2]->show();
}

void cl_MainFormSocket::slot_pushButtonKin(void)
{
    tableForms[0]->setWindowTitle(tr("Кинематические параметры самолета"));
    tableForms[0]->show();
}
void cl_MainFormSocket::slot_pushBeginCommonConst(void)
{
    tableForms[3]->setWindowTitle(tr("Начальные константы кинематики самолета"));
    tableForms[3]->show();
}
void cl_MainFormSocket::setEnabledItemsInForm(bool f)
{
    groupBoxParam->setEnabled(f);
    groupBoxUpr->setEnabled(f);
    groupBoxFunc->setEnabled(f);
    groupBoxTarget->setEnabled(f);

    for(int i=0;i<tableForms.size();i++)
    {
        tableForms[i]->setEnabled(f);
    }
}
//! обновление выбраных данных
void cl_MainFormSocket::refreshSelectedData()
{
     //QModelIndexList list=ui.selectedIndexes();


}
//! обновить данные
void cl_MainFormSocket::refreshData(void)
{
    //! Обновить данные
    data->refreshData();
    //! Обновить индикацию кол-во целей
    lcdNumberTargets->display(data->targetAirNum());
    spinBoxNumVariant->setValue(data->numVariant());

    for(int i=0;i<data->targetNumbers();i++)
    {
        double latTarget=0;
        double lonTarget=0;
/*
        commonEngineData->setValue("VisV.AirTarget["+QString::number(i)+"].Psi",
                                   QString::number(data->targetPsi(i)+data->Aust()),
                                   IEngineData::ASYNCH_ENGINE);
*/
        double xTarget=data->xTarget(i)-data->xc();
        double zTarget=data->zTarget(i)-data->zc();

        //! матрица поворота модельной СК
        Matrix3D_D matrixAust;
        Vector3D_D vecIn,vecOut;
        vecIn.x=xTarget;vecIn.y=0.0;vecIn.z=zTarget;
        double psi_r=-GradToRadian(data->psic());
        //==================================================
        matrixAust.x[0][0]=cos(psi_r);
        matrixAust.x[0][1]=0.0;
        matrixAust.x[0][2]=-sin(psi_r);

        matrixAust.x[1][0]=0.0;
        matrixAust.x[1][1]=1.0;
        matrixAust.x[1][2]=0.0;

        matrixAust.x[2][0]=sin(psi_r);
        matrixAust.x[2][1]=0.0;
        matrixAust.x[2][2]=cos(psi_r);

        vecOut=matrixAust.transpose()*vecIn;

        convertDekartToSphere(GradToRadian(data->lonc()),
                              GradToRadian(data->latc()),
                              vecOut.x,vecOut.z,
                              lonTarget,latTarget);


     /*   commonEngineData->setValue("VisV.AirTarget["+QString::number(i)+"].Lat",
                                   QString::number(RadianToGrad(latTarget)),
                                   IEngineData::ASYNCH_ENGINE);
        commonEngineData->setValue("VisV.AirTarget["+QString::number(i)+"].Lon",
                                   QString::number(RadianToGrad(lonTarget)),
                                   IEngineData::ASYNCH_ENGINE);*/
    }

    radioKab->setChecked(false);
    radioDet->setChecked(false);
    radioDetCircle->setChecked(false);
    radioKabCircle->setChecked(false);
    radioUvod->setChecked(false);
    radioFDR->setChecked(false);

    if(data->comUst()==1)
    {
        pushButtonComUst->setPalette(paletteButton[0]);
        pushButtonComUst->setIcon(QIcon(":/png/toolRed"));
        pushButtonComUst->setChecked(true);
    }
    else
    {
        pushButtonComUst->setPalette(paletteButton[1]);
        pushButtonComUst->setIcon(QIcon(":/png/tool"));
        pushButtonComUst->setChecked(false);
    }

    toolButtonVariant->setChecked(data->prNewVariant());
    checkBoxManevrTaget->setChecked(data->manevrTarget());
    switch(data->controlRegime())
    {
    case KABINA_SAU:    {radioKab->setChecked(true);break;}
    case DETERM:        {radioDet->setChecked(true);break;}
    case DETERM_CIRCLE: {radioDetCircle->setChecked(true);break;}
    case KABINA_CIRCLE: {radioKabCircle->setChecked(true);break;}
    case TEST_UVOD:     {radioUvod->setChecked(true);break;}
    case FDR:           {radioFDR->setChecked(true);break;}
    default:            {qDebug("wrong controlRegime: refreshData()");}
    };

    //! Управление от руда или включен автомат тяги
    if(data->avtoTiaga()==true)
    {
        radioButtonRUD->setChecked(false);
        radioButtonAvtoTiaga->setChecked(true);
    }else
    {
        radioButtonRUD->setChecked(true);
        radioButtonAvtoTiaga->setChecked(false);
    }

    //! САУ + идеальный пилот
    if(data->sauIdelPilot()==0)
    {
        radioButtonProdChannel->setChecked(true);
        radioButtonSAUAvtopilot->setChecked(false);
        radioButtonAvtoCancel->setChecked(false);
    }else if(data->sauIdelPilot()==1)
    {
        radioButtonProdChannel->setChecked(false);
        radioButtonSAUAvtopilot->setChecked(true);
        radioButtonAvtoCancel->setChecked(false);
    }else
    {
        radioButtonProdChannel->setChecked(false);
        radioButtonSAUAvtopilot->setChecked(false);
        radioButtonAvtoCancel->setChecked(true);
    }

    //! Модель Аэродинамики --- Аэродинамика 1/Детерминированная/Отключено
    if(data->detAerod1()==0)
    {
        radioButtonAerod1->setChecked(true);
        radioButtonDeter->setChecked(false);
        radioButtonCancel->setChecked(false);
    }else if(data->detAerod1()==1)
    {
        radioButtonAerod1->setChecked(false);
        radioButtonDeter->setChecked(true);
        radioButtonCancel->setChecked(false);
    }else
    {
        radioButtonAerod1->setChecked(false);
        radioButtonDeter->setChecked(false);
        radioButtonCancel->setChecked(true);
    }
    //! Вид движения прямолинейный/змейка
    if(data->serpent()==0)
    {
        radioButtonLinearMotion->setChecked(true);
        radioButtonSerpent->setChecked(false);
    }else
    {
        radioButtonLinearMotion->setChecked(false);
        radioButtonSerpent->setChecked(true);
    }
    //! Время для оси X
    t=data->t();
    //! задать положение нашего самолета для модуля задания вариантов
//    commonEngineData->setValue("VisV.Aircraft.Psi",QString::number(data->psic()+data->Aust()),IEngineData::ASYNCH_ENGINE);
//    commonEngineData->setValue("VisV.Aircraft.Lat",QString::number(data->latc()),IEngineData::ASYNCH_ENGINE);
//    commonEngineData->setValue("VisV.Aircraft.Lon",QString::number(data->lonc()),IEngineData::ASYNCH_ENGINE);
//    commonEngineData->setValue("VisV.Time",QString::number(t),IEngineData::ASYNCH_ENGINE);
}

//! применик данных по сокетам
void cl_MainFormSocket::slotIsResived()
{
    static bool refresh=true;
    this->setEnabled(true);


    if(data->regime() == STOP)
    {
        targetsForm->setBlockItemChanged(false);
        pushButtonRefresh->setEnabled(true);
        for(int i=0;i<tableForms.size();i++)
        {
            tableForms[i]->setBlockItemChanged(false);
        }
    }else
    {
        //! блокируем отправку изменения параметров
        targetsForm->setBlockItemChanged(true);
        pushButtonRefresh->setEnabled(false);
        for(int i=0;i<tableForms.size();i++)
        {
            tableForms[i]->setBlockItemChanged(true);
        }
    }

    //! Обновить индикацию режимов
    data->refreshRegime();

    if(data->regime()!=STOP)
    {
        refresh=true;
        refreshData();
    }else if(refresh==true)
    {
        refreshData();
        data->blockSending(false);
        refresh=false;
    }

    if((data->regime() == STOP) &&(regime_prev == ISXODNOE))
    {
        mppm->refreshExpandedItem();
    }

    //! Обновление индикации счетчика
    lcdNumberCounter->display(QString::number(data->counter()));
    formPult->setLedReset();

    switch(data->regime())
    {
    case STOP:
        {
            mppm->setEnabledAll(true);
            labelRegime->setPalette(palette[0]);
            labelRegime->setText(tr("Текущее состояние: ОСТАНОВ"));
            formPult->setLedStop();
            break;
        }
    case START:
        {
            mppm->setEnabledAll(false);
            labelRegime->setPalette(palette[1]);
            labelRegime->setText(tr("Текущее состояние: ПУСК"));
            formPult->setLedStart();
            if(formPult->pultOn()==false) formPult->refreshAll();
            break;
        }
    case ISXODNOE:
        {
            mppm->setEnabledAll(false);
            visualVar->slotRestart();
            //! очистка сцены по нажатию исходное
            labelRegime->setPalette(palette[1]);
            labelRegime->setText(tr("Текущее состояние: ИСХОДНОЕ"));
            formPult->setLedRestart();
            if(formPult->pultOn()==false)
                formPult->refreshAll();
            break;
        }
    case COMUST:
        {
            mppm->setEnabledAll(false);
            labelRegime->setPalette(palette[1]);
            labelRegime->setText(tr("Текущее состояние: ПРИЗНАК УСТАНОВКИ"));
            //formPult->setLedStart();
            //if(formPult->pultOn()==false) formPult->refreshAll();
            break;
        }
    default:
        {
            qDebug("Regime() is default:\n");
        }
    };

    regime_prev=data->regime();

}
bool cl_MainFormSocket::gestureEvent(QGestureEvent *event)
{
    Q_UNUSED(event);
    return false;
//    if (QGesture *swipe = event->gesture(Qt::SwipeGesture))         qDebug("Swipe gesture\n");
//    else if (QGesture *pan = event->gesture(Qt::PanGesture))        qDebug("pan gesture\n");
//    else if (QGesture *pinch = event->gesture(Qt::PinchGesture))    qDebug("pinch gesture\n");
//    else if (QGesture *tap = event->gesture(Qt::TapGesture))        qDebug("tap gesture gesture\n");

//    return true;
}
void cl_MainFormSocket::swipeTriggered(QSwipeGesture *gesture)
 {
     qDebug("Detected swipeTrigered\n");

     if (gesture->state() == Qt::GestureFinished) {
         if (gesture->horizontalDirection() == QSwipeGesture::Left
             || gesture->verticalDirection() == QSwipeGesture::Up)
             goPrevWidget();
         else
             goNextWidget();
         update();
     }
 }
//! перейти к предыдущему окну
void cl_MainFormSocket::goPrevWidget()
{
    qDebug("call cl_MainFormSocket::goPrevWidget()\n");
    curWindow--;
    if(curWindow<0) curWindow=stackedWidget->count()-1;
    stackedWidget->setCurrentIndex(curWindow);
}

//! перейти к следующему окну
void cl_MainFormSocket::goNextWidget()
{
    qDebug("call cl_MainFormSocket::goNextWidget()\n");
    curWindow++;
    if(curWindow>=stackedWidget->count()) curWindow=0;
    stackedWidget->setCurrentIndex(curWindow);
}

