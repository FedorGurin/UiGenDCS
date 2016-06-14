#include "formlamps.h"
#include "ui_formlamps.h"
#include <QHBoxLayout>

#include "./trans/Parameter.h"

FormLamps::FormLamps(Structure * str_,QWidget *parent) :
QWidget(parent),
ui(new Ui::FormLamps)
{
    ui->setupUi(this);

    str=str_;

    //! название формы
    setWindowTitle(str->displayName);

    QHBoxLayout *layoutH = new QHBoxLayout(this);
    FormLamp *newLamp=0;
    for(int i=0;i<str->child.size();i++)
    {
        newLamp = new FormLamp((Parameter*)str->child[i],this);
        bits.push_back(newLamp);
        layoutH->addWidget(bits[i]);
    }
    setLayout(layoutH);
    show();

}
void FormLamps::create(int size)
{
   /* FormLamp *newLamp=0;
    for(int i=0;i<size;i++)
    {
        newLamp=new FormLamp(this);
        bits.push_back(newLamp);
    }*/
}
void FormLamps::remove(int index)
{
    if(index<bits.size())
    {
        bits.remove(index);
    }
}
void FormLamps::removeAll()
{

}
void FormLamps::refresh()
{
    for(int i=0;i<bits.size();i++)
        bits[i]->refresh();
}

FormLamps::~FormLamps()
{
    delete ui;
}
