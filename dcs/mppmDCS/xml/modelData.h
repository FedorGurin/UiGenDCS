/*
 * ModelData.h
 *
 *  Created on: 27.08.2008
 *      Author: Fedor
 */

#ifndef MODELDATA_H_
#define MODELDATA_H_

#include <QAbstractItemModel>
#include <QList>
#include <QObject>

#include <QModelIndex>

#include <QItemSelectionModel>
#include <QMenu>
#include <QEvent>


#include "GenericNode.h"


class ModelData: public QAbstractItemModel
{
    Q_OBJECT;
public:
    ModelData(QObject *parent=0);
    //! задать корневой узел
    void setRootNode(GenericNode*);
    //! индекс элемента
    QModelIndex index(int row,int column, const QModelIndex &parent )const;
    //! родительский элемент
    QModelIndex parent(const QModelIndex &child)const;
    //! флаги для данного элемента
    Qt::ItemFlags flags(const QModelIndex &index) const;
    //! кол-во  строк
    int rowCount(const QModelIndex &parent)const;
    //! кол-во столбцов
    int columnCount(const QModelIndex &parent)const;
    //! вернуть кол-во данных
    QVariant data(const QModelIndex &index,int role)const;
    //! задать/поменять данные
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    //! заголовок таблицы
    QVariant headerData(int section,Qt::Orientation orientation, int role)const;
    //! сбросить данные
    void resetData();
    //! размер шрифта
    void setSizeFont(int size){sizeFont=size;}
public slots:
    //! обновить данные в узле node
    void refreshItemData(QVector<GenericNode* > nodes);
signals:
    //! сигнал о том, что данные в node поменялись
    void refreshData(GenericNode* node);
private:
    GenericNode* nodeFromIndex(const QModelIndex &index)const;
    GenericNode *rootNode;
    int sizeFont;
    virtual ~ModelData();
};
#endif /* MODELDATA_H_ */
