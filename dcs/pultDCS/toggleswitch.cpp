#include "toggleswitch.h"

ToggleSwitch::ToggleSwitch(QDomElement *ele,QWidget *parent):QWidget(parent)
{
    node=0;
    inv=false;
    //заполнение объекта
    numPage=    (ele->attribute("numPage","4")).toInt();
    inv=        (ele->attribute("inv","0")).toInt();
    idName=     (ele->attribute("idName","0"));
    valueIsBool=(ele->attribute("valueIsBool","0")).toInt();
    ///////////////////////////////////////////////////////////////
    QPalette palette;
    palette.setColor(QPalette::Foreground,QColor(Qt::green));
    layoutV = new QVBoxLayout;
    label=new QLabel(tr("Не найден"),this);
    label->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    label->setPalette(palette);
    toggle=new QtSvgToggleSwitch(this);
    toggle->setEnabled(false);
    toggle->setSkin("BerylSquare");
    toggle->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    layoutV->addWidget(label);
    layoutV->addWidget(toggle);
    ///////////////////////////////////////////////////////////////////
    connect(toggle,SIGNAL(toggled(bool)),this,SLOT(slotToggleSwitch(bool)));
}
void ToggleSwitch::slotToggleSwitch(bool)
{
    bool value=toggle->isChecked();
    if(node!=0)
    {
        if(valueIsBool==1)
        {
            if(node->typeP==Parameter::BIT && inv==false)
            {
                if(value==true) node->setValue(QString("True"));
                else node->setValue(QString("False"));
            }else if(inv==true)
            {
                if(value==true) node->setValue(QString("False"));
                else node->setValue(QString("True"));
            }
        }else
        {
            if(node->typeP==Parameter::INT && inv==false)
            {
                if(value==true) node->setValue(QString("1"));
                else node->setValue(QString("0"));
            }else if(inv==true)
            {
                if(value==true) node->setValue(QString("0"));
                else node->setValue(QString("1"));
            }
        }
        engine->setValue(node);
    }
}

void ToggleSwitch::setNode(Parameter *node_)
{
    node=node_;
    if(node!=0) toggle->setEnabled(true);
    else toggle->setEnabled(false);
}
void ToggleSwitch::setInv(bool inv_)
{
    inv=inv_;
}
void ToggleSwitch::setEngine(EngineData *engine_)
{
    engine=engine_;
    if(engine!=0)
    {
        node=(engine->findParamOnIdName(idName));
        if(node!=0) engine->getValue(node);
    }
    if(node!=0) label->setText(node->displayName);
    if(node!=0) toggle->setEnabled(true);
    else toggle->setEnabled(false);
}
void ToggleSwitch::setToggle()
{
    if(node!=0)
    {
        if(node->typeP==Parameter::BIT && inv==false)
        {
            if(node->value==tr("True")) toggle->setChecked(true);
            else toggle->setChecked(false);
        }else if(inv==false)
        {
            if(node->value==tr("1")) toggle->setChecked(true);
            else toggle->setChecked(false);
        }else if(node->typeP==Parameter::BIT && inv==true)
        {
            if(node->value==tr("True")) toggle->setChecked(false);
            else toggle->setChecked(true);
        }else if(inv==true)
        {
            if(node->value==tr("1")) toggle->setChecked(false);
            else toggle->setChecked(true);
        }
    }
}
void ToggleSwitch::setPage(int page)
{
    numPage=page;
}
