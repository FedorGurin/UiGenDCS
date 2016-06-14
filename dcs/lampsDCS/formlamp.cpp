#include "formlamp.h"
#include "ui_formlamp.h"

FormLamp::FormLamp(Parameter* param_,QWidget *parent) :
QWidget(parent),
ui(new Ui::FormLamp)
{
    ui->setupUi(this);

    param=param_;
    bool isOpen = pixmapRed.load(":/svg/red");
    isOpen      = pixmapGreen.load(":/svg/green");

    ui->labelText->setText("none");
    ui->labelLamp->setPixmap(pixmapRed);

     ui->labelText->setText(param->displayName);

}


void FormLamp::switchOn()
{
    ui->labelLamp->setPixmap(pixmapGreen);
}
void FormLamp::refresh()
{
    switchOff();
    if(param == 0)
        return;

    if(param->value != "0")
        switchOn();

}
void FormLamp::switchOff()
{
   ui->labelLamp->setPixmap(pixmapGreen);
}

FormLamp::~FormLamp()
{
    delete ui;
}
