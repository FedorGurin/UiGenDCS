#include "sliderhform.h"
#include "ui_sliderhform.h"

SliderHForm::SliderHForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SliderHForm)
{
    ui->setupUi(this);
    messure="";
}

SliderHForm::~SliderHForm()
{
    delete ui;
}

QSlider* SliderHForm::slider()
{
    return ui->verticalSlider;
}

void SliderHForm::setValue(int value)
{
   ui->verticalSlider->setValue(value);
   ui->lcdNumber->display(value);
}

void SliderHForm::setLimitMax(int max)
{
    ui->labelMax->setText(tr("Макс: ")+QString::number(max)+" "+messure);
    ui->verticalSlider->setMaximum(max);

}

void SliderHForm::setLimitMin(int min)
{
    ui->labelMin->setText(tr("Мин: ")+QString::number(min)+" "+messure);
    ui->verticalSlider->setMinimum(min);
}

int SliderHForm::value()
{
    return ui->verticalSlider->value();
}
void SliderHForm::changeEvent(QEvent *e)
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
