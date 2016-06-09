#ifndef FORMPULT_H
#define FORMPULT_H

#include <QWidget>
#include <QLabel>
#include "qtsvgbutton.h"
#include "qtsvgslideswitch.h"
#include "qtsvgtoggleswitch.h"
#include "qtscrollwheel.h"
#include "../xml/enginedata.h"
#include "../xml/Parameter.h"
#include "EngineVPult.h"
#include "SettingPultPNM.h"
#include "parserxmlpult.h"

namespace Ui {
class FormPult;
}

class FormPult : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormPult(QWidget *parent = 0);
    ~FormPult();
    
    //! индикация лампочек
    void setLedStop();
    void setLedStart();
    void setLedRestart();
    //! сброс всез лампочек
    void setLedReset();

    //! переключатель "Вирт. пульт"
    void setVPult(bool);
    //! переключатель "Режим1/2"
    void setRegime12(bool);
    //! переключатель "Купр"
    void setKupr(bool);

    //! обновление всех параметров
    void refreshAll();
    //! указатель на движок с данными
    void setEngineData(EngineData *engine);
    //! указатель
    void setCommonEngineData(CommonEngineData *engine)
    {
        commonEngineData=engine;
        connect(commonEngineData,SIGNAL(signalEventsRequest(TRequestEvent)),this,SLOT(slotEventsRequest(TRequestEvent)));
    }

    //! текущее состояние кнопок
    bool stop()     {return stop_;}
    bool start()    {return start_;}
    bool restart()  {return restart_;}
    //! текущее состояние тумблера
    bool kupr()     {return kupr_;}
    bool regime12() {return regime12_;}
    bool lockWrite(){return lockWrite_;}
    //! текущее состояние виртуального пульта
    bool pultOn()   {return pultOn_;}
    //! сокрытие данных
    EngineVPult *engineVPult;
    //! указатель на общий движок данных
    CommonEngineData *commonEngineData;
public slots:
    //! перемещение сладера
    void checkedSlideRegime12(bool);
    void checkedSlideKupr(bool);
    void checkedVPult(bool);
    void checkedLockWrite(bool);

    //! реакция на нажатие кнопки "Стоп"
    void setButtonStop();
    void releasedStop();
    //! реакция на нажатие кнопки "Старт"
    void setButtonStart();
    void releasedStart();
    //! реакция на нажатие кнопки "Исходное"
    void setButtonRestart();
    void releasedRestart();

    //! включение виртуального пульта
    void setSlideOnVPult(bool);
    //! реакция переключение тумблера Режим 12
    void setSlideRegime12(bool);
    //! реакция на переключение тумблера Kupr
    void setSlideKupr(bool);
    //! реакция на переключение темблера блокировка записи
    void setSlideLockWrite(bool);
    //! смена страниц
    void slotChangePages(int);

    //! чтение текущего состояния кнопок
    void slotReadStop(QString& value);
    void slotReadStart(QString& value);
    void slotReadRestart(QString& value);

    void slotEventsRequest(TRequestEvent);
signals:
    //! сигнал о обновлении состояния пульта
    void refresh(void);
private:
    void createSlider();
    void createButtons();
    void createToggle();

    TRequestEvent event;
    //!
    QtSvgButton *buttonStop;
    QtSvgButton *buttonRestart;
    QtSvgButton *buttonStart;
    QtSvgButton *buttonNextVariant;

    EngineData *engineData;
    SettingPultPNM *settingPultPNM;

    QPalette palette;

    QtSvgSlideSwitch *slideKupr;
    QtSvgSlideSwitch *slideRegime12;
    QtSvgSlideSwitch *slideLockWrite;
    QtSvgSlideSwitch *slideOnVPult;

    QtScrollWheel *scrollWheelPages;

    QPixmap pixmapRed;
    QPixmap pixmapGreen;

    QLabel *labelStart;
    QLabel *labelStop;
    QLabel *labelRestart;

    bool stop_;
    bool start_;
    bool restart_;

    bool kupr_;
    bool regime12_;
    bool lockWrite_;

    bool pultOn_;
    QStringList listNamePages;

    ParserXMLPult *parser;
private:
    Ui::FormPult *ui;
};

#endif // FORMPULT_H
