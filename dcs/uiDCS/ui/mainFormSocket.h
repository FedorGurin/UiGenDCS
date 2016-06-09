
#ifndef CL_MAINFORMSOCKET_H
#define CL_MAINFORMSOCKET_H

#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QPalette>
#include <QMessageBox>
#include <QMainWindow>
#include <QCheckBox>
#include <QGesture>
#include <QGestureEvent>

#include "ui_mainformsocket.h"
#include "cl_TableFormSocket.h"
#include "cl_TargetsForm.h"
#include "cl_transmit.h"
#include "GenericData.h"

#include "../xml/xmlmodelview.h"
#include "../pultPNM/formpult.h"
#include "../VisualVar/mainwindow.h"
#include "../translator/editorScript.h"
#include "../OVK/ovk.h"
#include "../ui/EngineDataUI.h"
#include "../settings/formsettingsall.h"
#include "../3dworld/trans3dworld.h"
#include "../help/mainwindowhelp.h"
#include "../ComSusp/widgetcomsusp.h"

class Widget;

class cl_MainFormSocket:public QMainWindow,public Ui::MainWindow
{
    Q_OBJECT;
public:
    cl_MainFormSocket(GenericData*);

    //! графический способ управления вариантами
    VisualVariant::MainWindowVisVar *visualVar;
    //! сетевое взаимодействие
    NetworkCommunication *networkCommunication;
    //! менеждер параметров программных модулей (МППМ)
    xmlmodelview *mppm;
    //! Обобщенные данные
    GenericData *data;
    //! виртуальный пульт
    FormPult *formPult;
    //! приложение для запуска тестов
    EditorScript *editorScript;
    //! обобщенный движок для всех данных
    CommonEngineData *commonEngineData;
    //! обработка данных
    EngineDataUI *engineDataUI;
    //! режим ОВК(для лены)
    OVK *ovk;
    //! обмен с 3D визуализацией
    Trans3DWorld *trans3DWorld;
    //! форма для управления настройками
    FormSettingsAll *formSettings;
    //! указатель на справку
    MainWindowHelp *help;
    //!
    WidgetComSusp *widgetComSusp;

    //! Имитатор СУО
    //! включить ПКИП
    void wolPKIP();

    //! обработка событий
    virtual bool event(QEvent*);

    //! набор форм с кинематикой  и т.д
    QVector <cl_TableFormSocket*> tableForms;

    //! формы для целей
    cl_TargetsForm *targetsForm;

    //! Загрузить данные
    void loadData();

    //! подключение форм
    void connectForms(bool flag);
    //! блокировка сигналов для форм
    void blockSignalsForm(bool );

    //! создать окно с атмосферными параметрами и геометрией
    void createFormAtmGeo(void);
    void refreshFormAtmGeo(void);

    //! создать окно с кинематическими параметрами
    void createFormKinAircraft(void);
    void refreshFormKinAircraft(void);

    //! создать окно с целями
    void createFormTargets(void);
    void refreshFormTargets(void);

    //! создать окно с константами
    void createFormConst(void);
    void refreshFormConst(void);

    //! создать окно с общими константами
    void createFormCommonConst(void);
    void refreshFormCommonConst();

    //! блокировка элементов управления
    void setEnabledItemsInForm(bool);

    //! обработка жестов для сенсорных device
    bool gestureEvent(QGestureEvent *event);
    void swipeTriggered(QSwipeGesture *gesture);

    //! Обновить данные
    void refreshData();
    //! обновить выбранные данные из списка
    void refreshSelectedData();
    QPalette palette[3];
    QPalette paletteButton[2];
    
    QUdpSocket socket;
    //! переключение языков
    void switchLang(int);
public slots:
    //! реакция на изменения выбора цели
    //void slotChangeTab(int numTab);
    //! перейти к предыдущему окну
    void goPrevWidget();
    //! перейти к следующему окну
    void goNextWidget();

    //! слот обнаружение соединения
    void slotConnectionFind();

    void slotReadyNetworkCommunication();

    //! слот об обновлении пульта ПНМ
    void slot_refreshPultPNM(void);

    //! кнопка просмотра параметров целей
    void slot_pushButtonTar(void);
    void slot_pushButtonConst(void);
    void slot_pushButtonKin(void);
    void slot_pushButtonAtmGeo(void);
    void slot_pushBeginCommonConst(void);
    void slot_checkBoxComUst();
    void slot_toolButtonOpenVariant();

    void slot_radioButtonsUpr(void);
    //! Отправить данные
    void slot_pushButtonSend(void);
    void slotToggledRadio(bool);
    void slotSpinBoxVariant(int);
    void slotClickedSend();
    void slotClickedIsx();

    //! реакция на нажатие кнопки выбора цели
    void slot_toolButtonTest();
    //! реакция на нажатие кнопки выбора варианта
    void slot_toolButtonVariant();
    //! реакция на нажатие кнопки ПМ
    void slot_toolButtonPM();
    //! реакция на нажатие кнопки вызова Вирт. пульта
    void slot_toolButtonPult();
    //! реакция на нажатие вызова
    void slot_toolComSusp();

    void slot_pushButtonRefresh(void);
    void slot_pressedButtonRestartModel();
    void slot_relesedButtonRestartModel();
    void slotIsResived();
    void slot_checkedCircle(int);
    void slotTimeout();
    void slotTriggered(QAction *);
    void slotTriggeredMenuVar(QAction*);
   
    void slotTriggeredMenuLang(QAction*);
    void slotTriggeredMenuSettings(QAction *);
    void slotTriggeredDebug(QAction* act);
    //! включение/отключение компьютеров
    void slotTriggeredMenuNetworkSwitch(QAction*);
    //! вызов справки
    void slotTriggeredMenuHelp(QAction* act);

private:
    //! значение режима на предыдущем шаге
    Regime regime_prev;
    int curWindow;
    QToolButton *buttonVar;
    QToolButton *buttonPM;
    QToolButton *buttonPult;
    QToolButton *button3D;
    QToolButton *buttonOVK;
    QToolButton *buttonTest;
    QToolButton *buttonPrev;
    QToolButton *buttonNext;
    QToolButton *buttonSusp;
};

#endif
