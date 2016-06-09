#include "cl_TableFormSocket.h"
#include "../globalFunc/gl_func.h"

#include <QFont>
#include <QHeaderView>
#include <QMessageBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QIcon>

cl_TableFormSocket::cl_TableFormSocket()
{
        blockSignalItemChanged=true;

        QFont sFont("Times",11,QFont::Light);
        serifFont=sFont;

        QStringList listHeader;
        setupUi(this);

        tableWidget->setColumnCount(4);
        tableWidget->setRowCount(1);

        listHeader<<tr("Название параметра")
                          <<tr("Ед. изм.")
                          <<tr("Пр")
                          <<tr("Значение");

        tableWidget->setHorizontalHeaderLabels(listHeader);

        QHeaderView *qhv;
        qhv=tableWidget->horizontalHeader();
        qhv->setSectionResizeMode(QHeaderView::ResizeToContents);
        qhv->setFont(serifFont);

        tableWidget->setFont(serifFont);
}
void cl_TableFormSocket::setValue(QStringList value)
{
    for(int i=0;i<value.size();i++)
    {
        QTableWidgetItem *modItem=tableWidget->item(i,3);
        if(modItem != 0)
            modItem->setText(value[i]);
    }
}
void cl_TableFormSocket::setBlockItemChanged(bool value)
{
    if(value == true && blockSignalItemChanged == false)
    {
        //qDebug("setBlockItemChanged() - disonnect()\n");
        disconnect(tableWidget,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(slotItemChanged()));
    }if(value == false && blockSignalItemChanged == true)
    {
        //qDebug("setBlockItemChanged() - connect()\n");
        connect(tableWidget,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(slotItemChanged()));
    }
    blockSignalItemChanged = value;

}
void cl_TableFormSocket::slotItemChanged()
{
    //qDebug("emit11\n");
    if(blockSignalItemChanged == false)
    {
        //qDebug("emit signal itemChanged()\n");
        emit itemChanged();
    }
}

QStringList cl_TableFormSocket::values(void)
{
    value.clear();

    for(int i=0;i<tableWidget->rowCount();i++)
        value<<(tableWidget->item(i,3))->text();

    return value;
}


void cl_TableFormSocket::setItems(QVector <ItemTable*> &items)
{
    tableWidget->setColumnCount(4);
    tableWidget->setRowCount(items.size());

    for(int i=0;i<items.size();i++)
    {
        QTableWidgetItem* item;
        items[i]->setFlags(Qt::ItemIsEnabled);
        QFont f(serifFont);
        f.setWeight(QFont::Black);
        items[i]->setFont(f);
        tableWidget->setItem(i,0,(QTableWidgetItem*)items[i]);

        item=new QTableWidgetItem(items[i]->mess);
        item->setFlags(Qt::ItemIsEnabled);
        tableWidget->setItem(i,1,item);

        QIcon icon(":/png/tool");

        if(items[i]->comUst==true)	item=new QTableWidgetItem(icon,"");
        else item=new QTableWidgetItem("");

        item->setFlags(Qt::ItemIsEnabled);
        tableWidget->setItem(i,2,item);
        typeMask.push_back(items[i]->typeId);

        QTableWidgetItem* itemValue=new QTableWidgetItem("0");
        itemValue->setFont(serifFont);

        tableWidget->setItem(i,3,itemValue);
    }
    tableWidget->setItemDelegate(new TableItemDelegate(3,typeMask));
}

TableItemDelegate::TableItemDelegate(int indexColumn,QVector <int> &typeMask,QObject *parent)
:QItemDelegate(parent)
{
    this->indexColumn=indexColumn;
    this->typeMask=typeMask;
}

QWidget* TableItemDelegate::createEditor(QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index)const
{
    if(index.column()==indexColumn)
    {
        if(typeMask[index.row()]==1)
        {

            QDoubleSpinBox *doubleSpinBox=new QDoubleSpinBox(parent);

            doubleSpinBox->setMaximum(999999.9);//максимальное значение
            doubleSpinBox->setMinimum(-999999.9);//минимальное значение
            doubleSpinBox->setSingleStep(1.0);//шаг изменения числа
            doubleSpinBox->setDecimals(9);//4 знака после запятой

            connect(doubleSpinBox,SIGNAL(editingFinished()),
                    this,SLOT(commitAndCloseEditorDouble()));
            return doubleSpinBox;
        }
        else/* if(typeMask[index.row()]==0)*/
        {
            QSpinBox *intSpinBox=new QSpinBox(parent);

            intSpinBox->setMaximum(999999);//максимальное значение
            intSpinBox->setMinimum(-999999);//минимальное значение
            intSpinBox->setSingleStep(1);//шаг изменения числа

            connect(intSpinBox,SIGNAL(editingFinished()),this,SLOT(commitAndCloseEditor()));
            return intSpinBox;
        }/*else
        {
            QLineEdit *lineEdit=new QLineEdit(parent);
            connect(lineEdit,SIGNAL(editingFinished()),this,SLOT(commitAndCloseEditorLineEdit()));
            return lineEdit;
        }*/

    }else return QItemDelegate::createEditor(parent,option,index);

}
void TableItemDelegate::commitAndCloseEditor()
{
    QSpinBox *editor=qobject_cast<QSpinBox *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}
void TableItemDelegate::commitAndCloseEditorDouble()
{
    QDoubleSpinBox *editor=qobject_cast<QDoubleSpinBox *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}
void TableItemDelegate::commitAndCloseEditorLineEdit()
{
    QLineEdit *editor=qobject_cast<QLineEdit *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}
void TableItemDelegate::setEditorData(QWidget *editor,const QModelIndex &index)const
{
    if(index.column()==indexColumn)
    {
        if(typeMask[index.row()]==1)
        {
            double value=index.model()->data(index,Qt::DisplayRole).toDouble();
            QDoubleSpinBox *doubleSpinBox=qobject_cast<QDoubleSpinBox*>(editor);

            doubleSpinBox->setMaximum(999999.9);//максимальное значение
            doubleSpinBox->setMinimum(-999999.9);//минимальное значение
            doubleSpinBox->setSingleStep(1.0);//шаг изменения числа
            doubleSpinBox->setDecimals(9);//4 знака после запятой

            doubleSpinBox->setValue(value);
        }
        else/* if(typeMask[index.row()]==0)*/
        {
            int value=index.model()->data(index,Qt::DisplayRole).toInt();
            QSpinBox *intSpinBox=qobject_cast<QSpinBox*>(editor);

            intSpinBox->setMaximum(999999);//максимальное значение
            intSpinBox->setMinimum(-999999);//минимальное значение
            intSpinBox->setSingleStep(1);//шаг изменения числа

            intSpinBox->setValue(value);
        }/*else
        {
            QString value=index.model()->data(index,Qt::DisplayRole).toString();
            QLineEdit *lineEdit=qobject_cast<QLineEdit*>(editor);

            lineEdit->setText(value);
        }*/

    }else QItemDelegate::setEditorData(editor,index);
}
void TableItemDelegate::setModelData(QWidget *editor,QAbstractItemModel *model,const QModelIndex &index) const
{
    if(index.column()==indexColumn)
    {
        if(typeMask[index.row()]==1)
        {
            QDoubleSpinBox *doubleSpinBox=qobject_cast<QDoubleSpinBox*>(editor);

            doubleSpinBox->setMaximum(999999.9);//максимальное значение
            doubleSpinBox->setMinimum(-999999.9);//минимальное значение
            doubleSpinBox->setSingleStep(1.0);//шаг изменения числа
            doubleSpinBox->setDecimals(9);//4 знака после запятой

            double value=doubleSpinBox->value();
            model->setData(index,value);
        }
        else/* if(typeMask[index.row()]==0)*/
        {
            QSpinBox *intSpinBox=qobject_cast<QSpinBox*>(editor);

            intSpinBox->setMaximum(999999);//максимальное значение
            intSpinBox->setMinimum(-999999);//минимальное значение
            intSpinBox->setSingleStep(1);//шаг изменения числа

            int value=intSpinBox->value();
            model->setData(index,value);
        }/*else
        {
            QLineEdit *lineEdit=qobject_cast<QLineEdit*>(editor);

            QString value=lineEdit->text();
            model->setData(index,value);
        }*/
    }else QItemDelegate::setModelData(editor,model,index);
}

ItemTable::ItemTable(const QString& text1,int t,bool ust,const QString& text2,  const QString& textToolTip)
{
    text=text1;
    mess=text2;

    comUst=ust;
    QTableWidgetItem::setText(text);
    QTableWidgetItem::setToolTip(textToolTip);
    typeId=t;
    time=0;
}
