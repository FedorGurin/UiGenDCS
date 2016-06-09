#ifndef FORMSETNAME_H
#define FORMSETNAME_H

#include <QWidget>
#include "enginedata.h"
namespace Ui {
    class FormSetName;
}

class FormSetName : public QWidget {
    Q_OBJECT
public:
    FormSetName( EngineData *engineData_,QWidget *parent = 0);
    EngineData *engineData;
    void enableSelectParam(bool f);
    ~FormSetName();
signals:
    void setName(QString,QString);
public slots:
    void slotPushButton();
    //! реакция на нажатие кнопки выбора паарметров
    void slotPushButtonSelectParam();
protected:
    void changeEvent(QEvent *e);

private:
    Ui::FormSetName *m_ui;
};

#endif // FORMSETNAME_H
