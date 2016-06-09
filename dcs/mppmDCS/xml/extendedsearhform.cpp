#include "extendedsearhform.h"
#include "ui_extendedsearhform.h"

ExtendedSearhForm::ExtendedSearhForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExtendedSearhForm)
{
    ui->setupUi(this);

    connect(ui->pushButtonFind,SIGNAL(clicked()),this,SLOT(slotPushButtonSearch()));
    connect(ui->pushButtonSelectArea,SIGNAL(clicked()),this,SLOT(slotPushButtonArea()));
    connect(ui->treeWidgetResult,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(slotDoubleClickedItem(QTreeWidgetItem*,int)));


    listResultOfSearch.clear();
    rootTreeWidgetAreaSearch=new QTreeWidgetItem(QStringList(tr("Данные")));
    hashTreeAreaSearch.clear();

    treeWidgetAreaSearch=new QTreeWidget;
    //engineData=new EngineData;
    //engineData->treeWidget->setParent(this);
    //15.05.2011
    //connect(engineData,SIGNAL(selectedItems(QList<GenericNode*>&)),this,SLOT(selectedItems(QList<GenericNode*>&)));

}
void ExtendedSearhForm::slotPushButtonArea()
{
    engineData->treeWidget->move(mapToGlobal(ui->pushButtonSelectArea->pos()));
    engineData->treeWidget->show();    
}
void ExtendedSearhForm::setWordToFind(QString name)
{
    ui->lineEditFind->setText(name);
}

ExtendedSearhForm::~ExtendedSearhForm()
{
    delete ui;
}
void ExtendedSearhForm::slotPushButtonSearch()
{
    listResultOfSearch.clear();
    ui->treeWidgetResult->clear();

    rootTreeWidgetItem=new QTreeWidgetItem(QStringList(tr("Результат поиска")));

    hashList.clear();
    stringSearch=ui->lineEditFind->text();
    for(int i=0;i<findList.size();i++)
    {
        recursSearch(findList[i],rootTreeWidgetItem);
    }
    //recursSearch(rootNodeData,rootTreeWidgetItem);
    ui->treeWidgetResult->insertTopLevelItem(0,rootTreeWidgetItem);
    ui->treeWidgetResult->expandAll();

}
void ExtendedSearhForm::addNodes(QString name,GenericNode* root, QTreeWidgetItem *rootItem)
{
    bool flag=false;

    if(ui->checkBoxReg->checkState()==Qt::Checked) flag=name.contains(stringSearch,Qt::CaseSensitive);
    else flag=name.contains(stringSearch,Qt::CaseInsensitive);

    if(flag==true)
    {
        TTableSearch temp;
        temp.name=name;
        QStringList listTemp;

        listTemp<<temp.name;
        listTemp<<root->pathName;

        QTreeWidgetItem *itemTemp=new QTreeWidgetItem(listTemp);


        itemTemp->setToolTip(1,root->pathName);
        itemTemp->setToolTip(0,temp.name);
        rootItem->addChild(itemTemp);

        temp.item=itemTemp;
        listResultOfSearch.push_back(temp);
        GenericNode* tempGenericNode=(GenericNode*)(root);

        hashList.insert(itemTemp,tempGenericNode);
    }
}

void ExtendedSearhForm::recursSearch(GenericNode* root, QTreeWidgetItem *rootItem)
{
    for(int i=0;i<root->child.size();i++)
    {
        GenericNode* tempNode=(GenericNode*)root->child[i];
        if(ui->checkBoxComment->checkState()==Qt::Checked)
        {
            addNodes(tempNode->comment,tempNode,rootItem);
        }
        if(ui->checkBoxName->checkState()==Qt::Checked)
        {
            addNodes(tempNode->displayName,tempNode,rootItem);
        }
        if(ui->checkBoxNamePIC->checkState()==Qt::Checked)
        {
            addNodes(tempNode->picName,tempNode,rootItem);
        }
        recursSearch(tempNode,rootItem);
    }
}
void ExtendedSearhForm::generateTreeAreaSearch(GenericNode* rootNode ,QTreeWidgetItem* rootItem)
{
    for(int i=0;i<rootNode->child.size();i++)
    {
        if(rootNode->child[i]->type()!=Node::PARAM)
        {
            QStringList listTemp;
            listTemp<<rootNode->child[i]->displayName;
            QTreeWidgetItem *itemTemp=new QTreeWidgetItem(listTemp);
            itemTemp->setCheckState(0,Qt::Unchecked);


            itemTemp->setToolTip(0,listTemp[0]);
            rootItem->addChild(itemTemp);
            GenericNode* tempNode=(GenericNode*)rootNode->child[i];

            hashTreeAreaSearch.insert(itemTemp,tempNode);
        }
    }
}
void ExtendedSearhForm::slotDoubleClickedItem(QTreeWidgetItem * item, int column)
{
    Q_UNUSED(column);
    GenericNode *tempNode=hashList.value(item);
    emit signalDoubleClicked(tempNode);
}
void ExtendedSearhForm::setRootData(GenericNode* node)
{
    if(node==0) return;
    rootNodeData=node;
    engineData->setRootData(rootNodeData);
    generateTreeAreaSearch(rootNodeData,rootTreeWidgetAreaSearch);
    treeWidgetAreaSearch->insertTopLevelItem(0,rootTreeWidgetAreaSearch);
    findList.clear();
    findList.push_back(rootNodeData);
    //модель со структурой
    //ui->comboBoxArea->setView(treeWidgetAreaSearch);
}
void ExtendedSearhForm::selectedItems(QList<GenericNode*>& list)
{
    if(list.size()!=0)
    {
        findList.clear();
        findList=list;
        ui->lineEditArea->clear();
        QString tempStr="";
        for(int i=0;i<list.size();i++)
        {
            tempStr=tempStr+list[i]->displayName+";";
        }
        ui->lineEditArea->setText(tempStr);
    }else
    {
        findList.clear();
        findList.push_back(rootNodeData);
        ui->lineEditArea->setText(tr("Везде"));
    }
}
void ExtendedSearhForm::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type())
    {
    case QEvent::LanguageChange:
	ui->retranslateUi(this);
	break;
    default:
        break;
    }
}
