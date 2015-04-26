#include "slidervform.h"
#include "ui_slidervform.h"

SliderVForm::SliderVForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SliderVForm)
{
    ui->setupUi(this);
    messure="";
}

SliderVForm::~SliderVForm()
{
    delete ui;
}
QSlider* SliderVForm::slider()
{
    return ui->verticalSlider;
}
void SliderVForm::setValue(int value)
{
   ui->verticalSlider->setValue(value);
   ui->lcdNumber->display(value);
}
void SliderVForm::setLimitMax(int max)
{
    ui->labelMax->setText(tr("Max:")+QString::number(max)+" "+messure);
    ui->verticalSlider->setMaximum(max);

}
void SliderVForm::setLimitMin(int min)
{
    ui->labelMin->setText(tr("Min:")+QString::number(min)+" "+messure);
    ui->verticalSlider->setMinimum(min);

}
int SliderVForm::value()
{
    return ui->verticalSlider->value();
}
void SliderVForm::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
