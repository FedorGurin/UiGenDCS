#ifndef ITEMDELEGATE_H
#define ITEMDELEGATE_H

#include <QItemDelegate>

#include "GenericNode.h"
#include "../globalFunc/gl_func.h"

#include "dialform.h"
#include "sliderhform.h"
#include "slidervform.h"

class TreeItemDelegate:public QItemDelegate
{
    Q_OBJECT;
public:
    TreeItemDelegate(int indexColumn_,QObject *parent,int *sizeFont=0);

    QWidget* createEditor(  QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index)const;
    void setEditorData(     QWidget *editor,const QModelIndex &index)const;
    void setModelData(      QWidget *editor,QAbstractItemModel *model,const QModelIndex &index) const;

    virtual bool eventFilter(QObject *editor, QEvent *event);

    QWidget* createEditorSliderH(   QWidget* parent,GenericNode *node)const;
    QWidget* createEditorSliderV(   QWidget* parent,GenericNode *node)const;
    QWidget* createEditorDial(      QWidget* parent,GenericNode *node)const;
    QWidget* createEditorGradMinSec(QWidget* parent,GenericNode *node)const;

    void setEditorSliderH(   QWidget *editor,const QModelIndex &index,GenericNode *node)const;
    void setEditorSliderV(   QWidget *editor,const QModelIndex &index,GenericNode *node)const;
    void setEditorDial(      QWidget *editor,const QModelIndex &index,GenericNode *node)const;
    void setEditorGradMinSec(QWidget *editor,const QModelIndex &index,GenericNode *node)const;

    QVariant setModelSliderH(   QWidget *editor,GenericNode *node)const;
    QVariant setModelSliderV(   QWidget *editor,GenericNode *node)const;
    QVariant setModelDial(      QWidget *editor,GenericNode *node)const;
    QVariant setModelGradMinSec(QWidget *editor,GenericNode *node)const;

private slots:
    void commitAndCloseEditor();
    void commitAndCloseCheckBox();
    void commitAndCloseEditorCombo();
    void commitAndCloseEditorDouble();
    void commitAndCloseEditorLineFiLamda();
    void commitAndCloseDialEditor();
    void commitAndCloseSliderHEditor();
    void commitAndCloseSliderVEditor();
    void commitAndCloseEditorLine();
private:
    int indexColumn;
    int *sizeFont;
};

#endif // ITEMDELEGATE_H
