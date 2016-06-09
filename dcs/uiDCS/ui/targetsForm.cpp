#include "cl_TargetsForm.h"
#include "cl_TableFormSocket.h"
#include "../globalFunc/gl_func.h"

#include <QHeaderView>
#include <QVBoxLayout>

cl_TargetsForm::cl_TargetsForm(QWidget *parent, Qt::WindowFlags f):QWidget(parent,f)
{
    blockSignalItemChanged=true;
    numTargets=0;
    tabWidget=new QTabWidget(this);

    connect(tabWidget,SIGNAL(currentChanged(int)),this,SIGNAL(sigTab(int)));
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(tabWidget);
    setLayout(layout);
    //setBaseSize(800,600);
}
void cl_TargetsForm::setNumTargets(int num)
{
    QString str;
    numTargets=num;

    int f=tabWidget->count();
    for(int i=0;i<f;i++)
    {
        disconnect(listTable[i]);
        tabWidget->removeTab(0);
    }
    listTable.clear();

    for(int i=0;i<num;i++)
    {
        listTable.push_back(new QTableWidget(items.size(),4));
        tabWidget->addTab(((QWidget*)listTable.back()),tr("Цель №")+str.setNum(i+1));
        connect(listTable.back(),SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(slotItemChanged()));

    }
    setItems(items);
}
void cl_TargetsForm::setValue(QStringList &value,int index)
{
    for(int i=0;i<value.size();i++)
    {
        QTableWidgetItem *item=listTable[index]->item(i,3);
        if(item!=0)
            item->setText(value[i]);
    }
}
void cl_TargetsForm::setBlockItemChanged(bool value)
{
    if(value == true && blockSignalItemChanged == false)
    {
        for(int i=0;i<tabWidget->count();i++)
        {
            disconnect(listTable[i]);
        }
    }if(value == false && blockSignalItemChanged == true)
    {
        for(int i=0;i<listTable.size();i++)
        {
            connect(listTable[i],SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(slotItemChanged()));
        }
    }
    blockSignalItemChanged = value;
}

QStringList cl_TargetsForm::values(int index)
{
    val.clear();
    for(int i=0;i<listTable[index]->rowCount();i++)
    {
        QTableWidgetItem *tempitem=(listTable[index]->item(i,3));
        if(tempitem!=0)
            val<<(listTable[index]->item(i,3)->text());
    }
    return val;
}
void cl_TargetsForm::slotItemChanged()
{
    if(blockSignalItemChanged == false)
    {
        emit itemChanged();
        qDebug("emit signal cl_TargetsForm::itemChanged()11\n");
    }
}
void cl_TargetsForm::setItems(QVector <ItemTable*> &items)
{
    QFont sFont("Times",11,QFont::Light);
    serifFont=sFont;

    QHeaderView *qhv;
    QStringList listHeader;

    listHeader<<tr("Название параметра")<<tr("Ед. изм.")<<tr("Пр")<<tr("Значение");

    this->items=items;

    typeMask.clear();

    for(int i=0;i<items.size();i++) typeMask.push_back(items[i]->typeId);

    TableItemDelegate *tD=new TableItemDelegate(1,typeMask);

    for(int j=0;j<numTargets;j++)
    {
        listTable[j]->setColumnCount(4);
        listTable[j]->setRowCount(items.size());

        listTable[j]->setAlternatingRowColors(true);
        listTable[j]->setHorizontalHeaderLabels(listHeader);

        qhv=listTable[j]->horizontalHeader();
        qhv->setFont(serifFont);
        qhv->setSectionResizeMode(QHeaderView::Stretch);

        for(int i=0;i<items.size();i++)
        {
            QTableWidgetItem *it=(QTableWidgetItem*)items[i];

            items[i]->setFlags(Qt::ItemIsEnabled);
            QFont f(serifFont);
            f.setWeight(QFont::Black);
            items[i]->setFont(f);

            listTable[j]->setItem(i,0,new QTableWidgetItem(*it));
            it=new QTableWidgetItem(items[i]->mess);
            listTable[j]->setItem(i,1,it);

            QIcon icon(":/png/tool");

            if(items[i]->comUst==true)
                it=new QTableWidgetItem(icon,"");
            else
                it=new QTableWidgetItem("");

            it->setFlags(Qt::ItemIsEnabled);
            listTable[j]->setItem(i,2,it);
            typeMask.push_back(items[i]->typeId);

            QTableWidgetItem* valueItem=new QTableWidgetItem("0");

            valueItem->setFont(serifFont);
            listTable[j]->setItem(i,3,valueItem);
        }

        listTable[j]->setItemDelegate(tD);
        listTable[j]->setFont(serifFont);
        listTable[j]->setItemDelegate(new TableItemDelegate(3,typeMask));
    }

}
