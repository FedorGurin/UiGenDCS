#ifndef ITEMSELECTIONMODEL_H
#define ITEMSELECTIONMODEL_H

#include <QItemSelectionModel>

class ItemSelectionModel : public QItemSelectionModel
{
    Q_OBJECT
public:
    explicit ItemSelectionModel(QAbstractItemModel * model);
    
signals:
    
public slots:
    
};

#endif // ITEMSELECTIONMODEL_H
