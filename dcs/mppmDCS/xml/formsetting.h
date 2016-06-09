#ifndef FORMSETTING_H
#define FORMSETTING_H

#include <QWidget>
#include <QMenu>
#include <QTreeWidgetItem>

#include "VariantState.h"

namespace Ui {
    class FormSetting;
}

class cl_MouseFilterSetting:public QObject
{
    Q_OBJECT
protected:
    virtual bool eventFilter(QObject*,QEvent*);
public:
    cl_MouseFilterSetting(QObject* pobj=0,QWidget *slotForm_=0);
    QWidget *slotForm;
};

class FormSetting : public QWidget {
    Q_OBJECT
public:
    FormSetting(QWidget *parent = 0);
    ~FormSetting();

    QMenu *menu;
    VariantState* currentVariant;

    void setVariantState(VariantState *node);
protected:
    void changeEvent(QEvent *e);
public slots:

    //! реакция на нажатие правой кнопки мыши на объекте TreeView
    void rightButtonMouseClicked();
    void slotPressButtonMouse(QAction*);

private:
    Ui::FormSetting *ui;
};

#endif // FORMSETTING_H
