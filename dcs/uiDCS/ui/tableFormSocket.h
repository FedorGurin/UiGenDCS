#ifndef CL_TABLEFORMSOCKET_H
#define CL_TABLEFORMSOCKET_H

#include "ui_tableformsocket.h"


#include <QItemDelegate>
#include <QTableWidgetItem>
#include <QMenu>
/*
//Элемент таблицы
class cl_MouseFilterTableForm:public QObject
{
    Q_OBJECT
protected:
    virtual bool eventFilter(QObject*,QEvent*);
public:
    cl_MouseFilterTableForm(QObject* pobj=0);
};
*/
class ItemTable:public QTableWidgetItem
{
public:
    ItemTable(const QString &text1="none",int t=0,bool ust=false,
              const QString &text2="", const QString &textToolTip="");
    void setValue(const QString &str)
    {
        curValue=str;

    }
    QString* value(void)
    {
        return &curValue;
    }
    void setTimeStep(double time_)
    {
        time=time_;
    }

    int typeId;
    QString text;
    QString mess;
    bool comUst;
    double time;
private:
    QString curValue;

};

class TableItemDelegate:public QItemDelegate
{
    Q_OBJECT;
public:
    TableItemDelegate(int indexColumn,QVector<int>& typeMask,QObject *parent=0);
    QWidget* createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,const QModelIndex &index)const;
    void setEditorData(QWidget *editor,const QModelIndex &index)const;
    void setModelData(QWidget *editor,QAbstractItemModel *model,
                      const QModelIndex &index) const;

private slots:
    void commitAndCloseEditor();
    void commitAndCloseEditorLineEdit();
    void commitAndCloseEditorDouble();
private:
    QVector <int> typeMask;
    int indexColumn;

};
class cl_TableFormSocket:public QWidget,Ui::TableFormSocket
{
    Q_OBJECT;
public:
    cl_TableFormSocket();
    //Вернуть значения таблицы
    QStringList values(void);
    //Задать элементы таблицы
    void setItems(QVector <ItemTable*> &);
    //Задать значения параметров в таблице
    void setValue(QStringList list);
    //Соответствие параметрам тадлицы типам данных (false-целое,true-вещественное)
    QVector<int> typeMask;

    //! блокировка сигнала и слота "элемент изменен"
    void setBlockItemChanged(bool value);

    QStringList value;
    QVector<QString> nameMyParam;
    QTableWidget* returnTableWidget(){return tableWidget;}
    QMenu *menu;

private:
    QFont serifFont;
    //! блокировка отправки сигнала "элемент изменен"
    bool blockSignalItemChanged;
public slots:  
    void slotItemChanged();         //! признак того, что содержимое изменилось
signals:
    void itemChanged();
};
#endif
