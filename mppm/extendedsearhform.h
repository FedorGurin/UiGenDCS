#ifndef EXTENDEDSEARHFORM_H
#define EXTENDEDSEARHFORM_H

#include <QWidget>
#include "GenericNode.h"
#include <QTreeWidgetItem>
#include "enginedata.h"
namespace Ui {
    class ExtendedSearhForm;
}

typedef struct
{
    GenericNode* node;
    int startNumWord;
    int endNumWord;
    QString name;
    QTreeWidgetItem *item;
}TTableSearch;

class ExtendedSearhForm : public QWidget
{
    Q_OBJECT

public:
    explicit ExtendedSearhForm(QWidget *parent = 0);
    ~ExtendedSearhForm();

    void setRootData(GenericNode* node);

    //! хешированные данные для поиска в указанной области
    QHash <QTreeWidgetItem *,GenericNode* > hashTreeAreaSearch;
    QTreeWidgetItem *rootTreeWidgetAreaSearch;
    QTreeWidget *treeWidgetAreaSearch;
    EngineData *engineData;
    void generateTreeAreaSearch(GenericNode* rootNode ,QTreeWidgetItem* rootItem);

    void addNodes(QString name,GenericNode* root, QTreeWidgetItem *rootItem);
    //! рекурсивный поиск
    void recursSearch(GenericNode*,QTreeWidgetItem *);
    void setWordToFind(QString);
signals:
    void signalDoubleClicked(GenericNode *);
public slots:
    void slotPushButtonSearch();
    void slotPushButtonArea();
    void slotDoubleClickedItem(QTreeWidgetItem * item, int column);
    void selectedItems(QList<GenericNode*>&);
protected:
    void changeEvent(QEvent *e);
private:
    //! строка с запросом поиска
    QString stringSearch;
    //! хэш-список хранит пару
    QHash <QTreeWidgetItem *,GenericNode* > hashList;
    //!
    QTreeWidgetItem *rootTreeWidgetItem;
    //! список с результатами поиска
    QList<TTableSearch> listResultOfSearch;

    QList<GenericNode*  > findList;



    GenericNode* rootNodeData;
    Ui::ExtendedSearhForm *ui;
};

#endif // EXTENDEDSEARHFORM_H
