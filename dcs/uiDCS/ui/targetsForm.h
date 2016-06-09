#ifndef CL_TARGETSFORM_H
#define CL_TARGETSFORM_H

#include <QWidget>
#include <QTableWidget>
#include <QDoubleSpinBox>
#include "cl_TableFormSocket.h"


//! класс описывающий цели
class cl_TargetsForm:public QWidget
{
    Q_OBJECT;
public:
    cl_TargetsForm(QWidget * parent = 0, Qt::WindowFlags f = 0 );

    //! список таблиц
    QVector <QTableWidget*> listTable;

    //! окно для хранения таблиц
    QTabWidget *tabWidget;

    //! список имен
    QStringList listName;

    //! указать кол-во целей
    void setNumTargets(int);

    //! список значений
    void setValue(QStringList&,int);

    //! получить список значений
    QStringList values(int index);

    //! задать список параметров
    void setStringList(QStringList &list);

    //! создать элементы
    void setItems(QVector<ItemTable*> &);

    //! тип маски
    QVector <int> typeMask;

    //! список значений
    QStringList val;

    //! данные изменились
    void setBlockItemChanged(bool value);

public slots:
    //! признак того, что содержимое изменилось
    void slotItemChanged();
private:
    //! блокировка отправки сигнала "элемент изменен"
    bool blockSignalItemChanged;
    //! кол-во целей
    int numTargets;
    //! список элементов
    QVector <ItemTable*> items;
    //! шрифт
    QFont serifFont;
signals:
    void itemChanged();
    void sigTab(int i);
};
#endif
