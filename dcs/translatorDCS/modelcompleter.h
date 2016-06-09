#ifndef MODELCOMPLETER_H
#define MODELCOMPLETER_H

#include <QAbstractItemModel>
#include <QCompleter>

#include "../xml/GenericNode.h"
class ModelCompleter : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit ModelCompleter(QCompleter* compliter_,QObject *parent = 0);

    void setRootNode(GenericNode*);
    QModelIndex index(int row,int column, const QModelIndex &parent )const;
    QModelIndex parent(const QModelIndex &child)const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    int rowCount(const QModelIndex &parent)const;
    int columnCount(const QModelIndex &parent)const;

    QVariant data(const QModelIndex &index,int role)const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    QVariant headerData(int section,Qt::Orientation orientation, int role)const;
signals:
    void refreshData(GenericNode*);
private:
    GenericNode* nodeFromIndex(const QModelIndex &index)const;
    GenericNode *rootNode;
    QCompleter *completer;

};

#endif // MODELCOMPLETER_H
