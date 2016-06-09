#include "dumpform.h"
#include "ui_dumpform.h"
#include <math.h>

#include <QBrush>

DumpForm::DumpForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DumpForm)
{
    ui->setupUi(this);
    gray_green=0;
}
void DumpForm::addValue(int addr,QString value,int cells)
{
    double row=0,column=0;
    QTableWidgetItem *newItem = new QTableWidgetItem(value);

    if(gray_green==0)   newItem->setBackground(QBrush(Qt::gray));
    else newItem->setBackground(QBrush(Qt::green));

    double val=addr/8.0;
    column = modf (val ,(double*)&row);
    ui->tableWidget->setItem((int)row, (int)(addr-(8*row)), newItem);

    for(int i=1;i<cells;i++)
    {
        QTableWidgetItem *tempItem = new QTableWidgetItem();

        if(gray_green==0)   tempItem->setBackground(QBrush(Qt::gray));
        else tempItem->setBackground(QBrush(Qt::green));

        double val=(addr+i)/8.0;
        column = modf (val ,(double*)&row);
        ui->tableWidget->setItem((int)row, (int)((addr+i)-(8*row)), tempItem);
    }
    if(gray_green==0) gray_green=1;
    else gray_green=0;

}
void DumpForm::clear()
{
    ui->tableWidget->clear();
}

DumpForm::~DumpForm()
{
    delete ui;
}
