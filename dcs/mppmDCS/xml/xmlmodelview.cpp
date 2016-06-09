#include "xmlmodelview.h"
#include "VariantNode.h"
#include "../globalFunc/gl_func.h"
#include "SIO.h"
#include "Parameter.h"
#include "itemselectionmodel.h"
#include <QMenu>
#include <QEvent>
#include <QLineEdit>
#include <QStringListModel>
#include "ItemDelegate.h"

#define RECIVE_PORT 4805

//extern VariantNode *glRootVariant;
cl_MouseFilter::cl_MouseFilter(QObject* pobj,QWidget *slotForm_):QObject(pobj)
{
    slotForm=slotForm_;
}
bool cl_MouseFilter::eventFilter(QObject* pobj,QEvent *event)
{
    Q_UNUSED(pobj);
    if(event->type()==QEvent::ContextMenu)
    {
        xmlmodelview *p=qobject_cast<xmlmodelview* >(slotForm);
        if(p!=0)
        {
            p->rightButtonMouseClicked();
            return true;
        }else return false;
    }
    return false;
}

xmlmodelview::xmlmodelview(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    listNodes.clear();
    listForCompleter.clear();
    menu=new QMenu;
    requestBlock=false;
    mainProg=true;
    removeFormBlock=readParamFromXMLFile(nameMainFile,"MPPM","RemoveFormBlock").toInt();

    sizeFont=10;
    settingsData=new SettingXML;

  //connect(ui.treeView,SIGNAL(clicked(const QModelIndex&)),this,SLOT(slot_tableView(const QModelIndex&)));
    connect(menu,                       SIGNAL(triggered(QAction*)),this,SLOT(slotPressButtonMouse(QAction*)));
    connect(menu,                       SIGNAL(hovered(QAction*)),this,SLOT(slotSubMenu(QAction*)));
    connect(ui.comboBox,                SIGNAL(activated(int)),this,SLOT(slotComboBox(int)));
    connect(ui.buttonCreate,            SIGNAL(clicked()),this,SLOT(slotButtonCreate()));
    connect(ui.pushButtonSaveInFile,    SIGNAL(clicked()),this,SLOT(slot_SaveVariants()));
    connect(ui.pushButtonSetup,         SIGNAL(clicked()),this,SLOT(slot_pushButtonSave()));
    connect(ui.toolButton,              SIGNAL(clicked()),this,SLOT(slot_searchButon()));
    connect(ui.pushButtonCollapse,      SIGNAL(clicked()),this,SLOT(slotPushButtonCollapse()));
    connect(ui.pushButtonExpand,        SIGNAL(clicked()),this,SLOT(slotPushButtonExpand()));
    connect(ui.lineEditSearch,          SIGNAL(returnPressed()),this,SLOT(slot_searchButon()));
    connect(ui.buttonDelete,            SIGNAL(clicked()),this,SLOT(slotButtonDelete()));
    connect(ui.buttonRename,            SIGNAL(clicked()),this,SLOT(slotButtonRename()));
    connect(ui.buttonSettings,          SIGNAL(clicked()),this,SLOT(slot_pushButtonSettings()));
    connect(ui.treeView,                SIGNAL(expanded(const QModelIndex&)),this,SLOT(slotForExpanded(const QModelIndex&)));
    connect(ui.toolButtonPlus,          SIGNAL(clicked()),this,SLOT(slotPlusFont()));
    connect(ui.toolButtonMinus,         SIGNAL(clicked()),this,SLOT(slotMinusFont()));
    connect(ui.pushButtonFlush,         SIGNAL(clicked()),this,SLOT(slotFlushCycParam()));
    connect(ui.toolButtonRequestBlock,  SIGNAL(toggled(bool)),this,SLOT(slot_toolButtonRequestBlock(bool)));

    domParser=new DomParser();

    currentVariantState=0;
    engineData=new EngineData(this);
    engineData->setRootData(domParser->rootNodeData());
    connect(engineData,SIGNAL(signalUI()),this,SLOT(slotActiveRefreshCommand()));

    formSetName=new FormSetName(engineData);
    renameVariant=new FormRenameVariant;
    connect(renameVariant,SIGNAL(acpect(bool)),this,SLOT(refreshComboBox()));

    formSetting=new FormSetting;
    formStatusExit=new FormStatusExitProgram;

    listRequest=new ListRequest;
    exSearchForm=new ExtendedSearhForm;
    exSearchForm->engineData=engineData;

    connect(ui.toolButtonSettingFind,SIGNAL(clicked()),this,SLOT(slotExtendedSearchButton()));

    domParser->formStatusExit=formStatusExit;

    exSearchForm->setRootData(domParser->rootNodeData());

    connect(exSearchForm,SIGNAL(signalDoubleClicked(GenericNode*)),this,SLOT(selectedGenericNode(GenericNode*)));

    QWidget     *widget=        new QWidget(this,Qt::Tool);
    QLineEdit   *textEdit=      new QLineEdit;
    QPushButton *pushButton=    new QPushButton(tr("OK"));
    QVBoxLayout *layout =       new QVBoxLayout;

    layout->addWidget(textEdit);
    layout->addWidget(pushButton);
    widget->setLayout(layout);

    QHeaderView *qhv;
    qhv=ui.treeView->header();
    qhv->setSectionResizeMode(QHeaderView::ResizeToContents);

    completer = new QCompleter(this);

    completer->setModel(new QStringListModel(listForCompleter,completer));
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);

    QTreeView *treeViewTemp = new QTreeView;
    completer->setPopup(treeViewTemp);
    treeViewTemp->setRootIsDecorated(false);
    treeViewTemp->header()->hide();
    treeViewTemp->header()->setStretchLastSection(false);
    /*treeViewTemp->header()->setResizeMode(0, QHeaderView::Stretch);
    treeViewTemp->header()->setResizeMode(1, QHeaderView::ResizeToContents);*/

    ui.lineEditSearch->setCompleter(completer);

    if(domParser->rootNodeData()!=0)
    {
        modelData=new ModelData(this);
        modelData->setRootNode(domParser->rootNodeData());


        connect(engineData,SIGNAL(signalFinOperation(QVector<GenericNode *> )),modelData,SLOT(refreshItemData(QVector<GenericNode *> )));

        ui.treeView->setModel(modelData);
        ui.treeView->setItemDelegate(new TreeItemDelegate(4,modelData,&sizeFont));
        ui.treeView->setSelectionModel(new ItemSelectionModel(modelData));

        connect(ui.treeView->selectionModel(),
                SIGNAL(currentChanged(const QModelIndex&,const QModelIndex&)),
                this,SLOT(slot_tableView(const QModelIndex&,const QModelIndex&)));

        connect(ui.treeView,
                SIGNAL(expanded(const QModelIndex&)),
                this,SLOT(slotExpandedItem(const QModelIndex&)));

        connect(ui.treeView,
                SIGNAL(collapsed(const QModelIndex&)),
                this,SLOT(slotCollapsedItem(const QModelIndex&)));


        ui.treeView->installEventFilter(new cl_MouseFilter(ui.treeView,this));

        connect(modelData,SIGNAL(refreshData(GenericNode*)),this,SLOT(slotRefreshData(GenericNode *)));       
    }
    refreshComboBox();

    if(domParser->rootItemVariantState!=0)
    {
        if(domParser->rootItemVariantState->child.size()!=0)
        {
            Node* node=domParser->rootItemVariantState->child[0];
            VariantState* var=static_cast<VariantState* >(node);
            currentVariantState=var;
        }
    }
}
void xmlmodelview::slotPlusFont()
{
    sizeFont++;

    modelData->setSizeFont(sizeFont);
    modelData->resetData();
}
void xmlmodelview::slotMinusFont()
{
    sizeFont--;

    if(sizeFont<8) sizeFont=8;
    modelData->setSizeFont(sizeFont);
    modelData->resetData();
}
void xmlmodelview::slotActiveRefreshCommand(GenericNode *node)
{
    QString command(tr("UI.Refresh"));
    if(requestBlock==false)
    {
        engineData->setValue(node);
    }
//    commonEngine->setValue(command,command);
}
void xmlmodelview::resetModeData()
{
    modelData->resetData();
}

void xmlmodelview::slotExtendedSearchButton()
{
    exSearchForm->setWordToFind(ui.lineEditSearch->text());
    exSearchForm->show();
    exSearchForm->activateWindow();
}
void xmlmodelview::refreshComboBox()
{
    ui.comboBox->clear();
    ui.comboBox->addItem(tr("Не выбран"));

    if(domParser->rootItemVariantState==0) return;

    for(int i=0;i<domParser->rootItemVariantState->child.size();i++)
    {
        ui.comboBox->addItem(domParser->rootItemVariantState->child[i]->displayName);
    }
}
void xmlmodelview::showHelps()
{

}
void xmlmodelview::slot_pushButtonSettings()
{
    if(currentVariantState!=0)  formSetting->setVariantState(currentVariantState);
    formSetting->show();
}
void xmlmodelview::slot_searchButon(void)
{
    QString searchStr=ui.lineEditSearch->text();

    ui.treeView->expandAll();
    ui.treeView->keyboardSearch(searchStr);
    ui.treeView->setFocus();
}
void xmlmodelview::slotForExpanded(const QModelIndex & index)
{
    GenericNode *node = static_cast<GenericNode*>(index.internalPointer());
    if(requestBlock==false)
    {
        if(node->type()==Node::SIO)
        {
            engineData->getValue(node);
        }
    }
}
void xmlmodelview::slotPushButtonCollapse()
{
    ui.treeView->collapseAll();
}
bool xmlmodelview::event(QEvent *event)
{
    if(event->type()==QEvent::Close)
    {
        //! сохранить вариант
        slot_SaveVariants();

        formSetting->close();
        exSearchForm->close();
        formSetName->close();
        renameVariant->close();
    }
    return QWidget::event(event);
}
void xmlmodelview::slotPushButtonExpand()
{
    ui.treeView->expandAll();
}
void xmlmodelview::slotRefreshData(GenericNode *node)
{
    //! если обмен пос сети отключен
    if(requestBlock==false)
    {
        engineData->setValue(node);
    }
}
void xmlmodelview::slot_pushButtonSave()
{
    if(currentVariantState!=0)
    {
        for(int i=0;i<currentVariantState->child.size();i++)
        {
            VariantState* variantState=static_cast<VariantState* >(currentVariantState->child[i]);
            if(variantState->variant!=0)
            {
                VariantNode* variantNode=variantState->variant;
                engineData->setValue((GenericNode*)variantNode->dataNode);
            }
        }
    }
}
//! не используемый слот
void xmlmodelview::slotSubMenu(QAction* act)
{
    workingNameMenu=act->text();
}
void xmlmodelview::slot_formSetName(SIO* node, QString name,QString comment)
{
    bool findVariant=false;
    for(int i=0;i<node->variants.size();i++)
    {
        Node *nodeTemp=node->variants[i];
        if(nodeTemp->displayName==name)
        {
            findVariant=true;
            break;
        }
    };
    //! Проверка есть ли уже вариант с таким именем
    //!  Внимание временно закомментирован
    if(findVariant==false)
    {
        if(name.compare("")!=0)
        {
            VariantNode *variantNode=new VariantNode(node,name);
            variantNode->comment=comment;
            node->variants.push_back(variantNode);
            domParser->rootItemVariant->addChild(variantNode);
            variantNode->setVariant();
        }else
        {
            QMessageBox::warning(0,tr("Внимание"),
                                 tr("Укажите имя варианта"));
        }
    }else
    {
        QMessageBox::warning(0,tr("Внимание"),
                             tr("Вариант с таким именем уже существует.Укажите другое имя"));
    }
}

void xmlmodelview::slot_formSetName(QString nameVariant,QString comment)
{
    QModelIndex modelIndex=ui.treeView->currentIndex();
    SIO *node = static_cast<SIO*>(modelIndex.internalPointer());

    bool findVariant=false;
    for(int i=0;i<node->variants.size();i++)
    {
        Node *nodeTemp=node->variants[i];
        if(nodeTemp->displayName==nameVariant)
        {
            findVariant=true;
            break;
        }
    };
    //! Проверка есть ли уже вариант с таким именем
    //!  Внимание временно закомментирован
    if(findVariant==false)
    {
        if(nameVariant.compare("")!=0)
        {
            //qDebug("Size listSNodes=%d\n",formSetName->engineData->listSNodes.size());
            VariantNode *variantNode=new VariantNode(node,nameVariant,formSetName->engineData->listSNodes);
            variantNode->comment=comment;
            SIO* sio=static_cast<SIO* >(node);
            sio->variants.push_back(variantNode);
            domParser->rootItemVariant->addChild(variantNode);
            //glRootVariant->addChild(variantNode);
            variantNode->setVariant();
            formSetName->close();
        }else
        {
            QMessageBox::warning(0,tr("Внимание"),
                                 tr("Укажите имя варианта"));
        }
    }else
    {
        QMessageBox::warning(0,tr("Внимание"),
                             tr("Вариант с таким именем уже существует.Укажите другое имя"));
    }
}
void xmlmodelview::slot_tableView(const QModelIndex& indexCur,const QModelIndex& indexPrev)
{
    Q_UNUSED(indexPrev);
    ui.textBrowser->clear();
    if(indexCur.isValid() == true)
    {
        GenericNode *node = static_cast<GenericNode*>(indexCur.internalPointer());
        ui.textBrowser->setText(node->comment);
    }
}
void xmlmodelview::slotExpandedItem(const QModelIndex& index)
{
    if(index.isValid() == true)
    {
        GenericNode *node = static_cast<GenericNode* >(index.internalPointer());
        if(node->type() == Node::SIO)
        {
            listNodes.append(node);
        }

    }
}
void xmlmodelview::slotCollapsedItem(const QModelIndex& index)
{
    if(index.isValid() == true)
    {
        GenericNode *node = static_cast<GenericNode* >(index.internalPointer());
        if(node->type() == Node::SIO)
        {
            listNodes.remove(listNodes.indexOf(node));
        }
    }
}
void xmlmodelview::refreshExpandedItem()
{
    for(int i=0;i<listNodes.size();i++)
        engineData->setValue(listNodes[i]);
}
//! реакция на ComboBox
void xmlmodelview::slotComboBox(int j)
{
    if(j==0) return;

    Node* node=domParser->rootItemVariantState->child[j-1];
    VariantState* var=static_cast<VariantState* >(node);
    var->setVariant();

    currentVariantState=var;

    for(int i=0;i<currentVariantState->child.size();i++)
    {
        if(((VariantState*)currentVariantState->child[i])->type()==Node::VARIANTPM)
        {
            if(((VariantState*)currentVariantState->child[i])->variant!=0)
            {
                VariantNode* node=(VariantNode*)(((VariantState*)currentVariantState->child[i])->variant);
                engineData->setValue((GenericNode*)(node->dataNode));
            }
       }
    }
    ui.comboBox->setToolTip(currentVariantState->comment);

    //ui.treeView->collapse(ui.treeView->currentIndex());
    //ui.treeView->expand(ui.treeView->currentIndex());
}
void xmlmodelview::slotButtonCreate()
{
    disconnect(formSetName,SIGNAL(setName(QString,QString)),this,SLOT(slot_formSetName(QString,QString)));
    disconnect(formSetName,SIGNAL(setName(QString,QString)),this,SLOT(slot_formSetNameStateVariant(QString,QString)));
    connect(formSetName,SIGNAL(setName(QString,QString)),this,SLOT(slot_formSetNameStateVariant(QString,QString)));
    formSetName->enableSelectParam(false);
    formSetName->show();
}
void xmlmodelview::slot_formSetNameStateVariant(QString name, QString comment)
{
    //делаем проверку на наличие варанта с таким же именем
    bool check=false;
    if(domParser->rootItemVariantState==0) return;

    for(int i=0;i<domParser->rootItemVariantState->child.size();i++)
    {
        if(domParser->rootItemVariantState->child[i]->displayName==name) check=true;
    }
    if(check==false)
    {
        if(name.compare("")!=0)
        {
            currentVariantState=new VariantState(name);
            currentVariantState->comment=comment;
            domParser->rootItemVariantState->addChild(currentVariantState);
            ui.comboBox->addItem(name);
            slotComboBox(ui.comboBox->count()-1);
            formSetName->close();
        }else
        {
            QMessageBox::warning(0,tr("Внимание"),
                                 tr("Укажите имя варианта"));
        }

    }else
    {
        QMessageBox::warning(0,tr("Внимание"),
                 tr("Вариант с таким именем уже существует.Укажите другое имя"));
    }


}
void xmlmodelview::slotButtonRename()
{
    if(ui.comboBox->currentIndex()==0) return ;

    if(currentVariantState!=0)
    {
        renameVariant->setVariant(currentVariantState);
        renameVariant->show();
    }else
    {
        QMessageBox::warning(0,tr("Внимание"),
        tr("Не выбран вариант состояния"));
    }
}
void xmlmodelview::slotButtonDelete()
{
    if(currentVariantState!=0 && ui.comboBox->currentIndex()>0)
    {
        currentVariantState->deleteVariantState();        
        currentVariantState=0;
        refreshComboBox();
    }
}
void xmlmodelview::refreshAllData()
{
    engineData->getValue(domParser->rootItemData);
}
void xmlmodelview::slotPressButtonMouse(QAction* act)
{
    QModelIndex modelIndex=ui.treeView->currentIndex();
    GenericNode *node = static_cast<GenericNode*>(modelIndex.internalPointer());    

    if(act->text()==tr("Записать"))
    {
        engineData->setValue(node);
    }else if(act->text()==tr("Прочитать"))
    {
        engineData->getValue(node);
    }else if(act->text()==tr("Показать дамп"))
    {
        engineData->showDump();
    }else if(act->text()==tr("Создать вариант"))
    {
        formSetName->disconnect();

        //disconnect(formSetName,SIGNAL(setName(QString)),this, SLOT(slotButtonCreate(QString)));
        //disconnect(formSetName,SIGNAL(setName(QString)),this, SLOT(slot_formSetName(QString)));

        connect(formSetName,SIGNAL(setName(QString,QString)),this, SLOT(slot_formSetName(QString,QString)));
        formSetName->enableSelectParam(true);
        formSetName->engineData->setRootData(node);
        //! выбрать для сохранения все элементы
        formSetName->engineData->selectAllElements();
        formSetName->show();

    }else if(node->type()==Node::PARAM)
    {
        Parameter* param=(Parameter*)node;
        if(act->text()==tr("Циклический опрос"))
        {
            if(param->cycle_request==true)
            {
                param->cycle_request=false;
            }else param->cycle_request=true;

            act->setCheckable(true);
            act->setChecked(param->cycle_request);

            //engineData->addCyclicRequest(param);
        }
    }
    else  if(node->type()==Node::SIO )
    {
        SIO* sio=(SIO*)node;
        VariantNode* variantNode=0;


        for(int i=0;i<sio->variants.size();i++)
        {
            VariantNode* tempNode=(VariantNode*)sio->variants.at(i);
            if(tempNode->displayName==act->data().toString())
            {
                variantNode=tempNode;
            }
        }
        if(act->text()==tr("Расскрыть все поддерево"))
        {
            blockAutoRead(true);
            recTreeForExpanded(node);
            blockAutoRead(false);
        }
        if(act->text()==tr("Установить"))
        {
            variantNode->setVariant();
            engineData->setValue(node);
        }
        if(act->text()==tr("Удалить"))
        {
            sio->variants.removeOne(variantNode);
            variantNode->deleteVariant();
        }
        if(act->text()==tr("Сохранить"))
        {
            //qDebug("Resave variant\n");
            QString nameVariant=variantNode->displayName;
            QString comment=variantNode->comment;

            sio->variants.removeOne(variantNode);
            variantNode->deleteVariant();

            formSetName->enableSelectParam(true);
            formSetName->engineData->setRootData(node);
            formSetName->engineData->selectAllElements();

            slot_formSetName(nameVariant,comment);
            //variantNode->refreshVariant();
        }
        if(act->text()==tr("Переименовать"))
        {
            renameVariant->setVariant(variantNode);
            renameVariant->show();
        }
        if(act->text()==tr("Добавить в вариант состояния"))
        {
            VariantState *variantTemp=new VariantState();
            //! указать что данный элемент содержит вариант программного варианта
            variantTemp->setVariantPM();
            variantTemp->addTailVariantPM(variantNode);

            if(currentVariantState!=0)  currentVariantState->addVariant(variantTemp);
            else
            {
                 QMessageBox::warning(0,tr("Внимание"),
                 tr("Вариант не добавлен. Создайте вариант состояния."));
            }
        }
    }

    if(act->text()==tr("Задать всем модулям"))
    {
        engineData->setValue(node);
    }else if(act->text()==tr("Прочитать все модули"))
    {
        engineData->getValue(node);
    }else if(act->text()==tr("Расскрыть все поддерево"))
    {
        blockAutoRead(true);
        recTreeForExpanded(node);
        blockAutoRead(false);
    }else if(act->text()==tr("Bool"))
    {
        Parameter *tempParam=static_cast<Parameter*> (node);
        tempParam->modeEdit=Parameter::BIN;

    }else if(act->text()==tr("Hex"))
    {
        Parameter *tempParam=static_cast<Parameter*> (node);
        tempParam->modeEdit=Parameter::HEX;

    }else if(act->text()==tr("Dec"))
    {
        Parameter *tempParam=static_cast<Parameter*> (node);
        tempParam->modeEdit=Parameter::DEC;

    }else if(act->text()==tr("Oct"))
    {
        Parameter *tempParam=static_cast<Parameter*> (node);
        tempParam->modeEdit=Parameter::OCT;
    }else if(act->text()==tr("По умолчанию"))
    {
        Parameter *tempParam=static_cast<Parameter*> (node);
        tempParam->modeIndication=Parameter::DEFAULT_IND;
    }else if(act->text()==tr("Круговая шкала"))
    {
        Parameter *tempParam=static_cast<Parameter*> (node);
        tempParam->modeIndication=Parameter::DIAL;
    }else if(act->text()==tr("Слайдер горизонтальный"))
    {
        Parameter *tempParam=static_cast<Parameter*> (node);
        tempParam->modeIndication=Parameter::SLIDER_V;
    }
    else if(act->text()==tr("Слайдер вертикальный"))
    {
        Parameter *tempParam=static_cast<Parameter*> (node);
        tempParam->modeIndication=Parameter::SLIDER_H;
    }
    else if(act->text()==tr("Градусы, минуты, секунды"))
    {
        Parameter *tempParam=static_cast<Parameter*> (node);
        tempParam->modeIndication=Parameter::GRAD_MINUTE_SEC;
        qDebug("selected Grad-Min-Second\n");
    }
    else if(act->text()==tr("Снять ограничения"))
    {
        Parameter *tempParam=static_cast<Parameter*> (node);
        if(tempParam->restriction==true) tempParam->restriction=false;
        else tempParam->restriction=true;
    }else if(act->text()==tr("Прочитать параметры"))
    {
        engineData->getValue(node);
    }   
}

void xmlmodelview::rightButtonMouseClicked()
{
    QModelIndex modelIndex=ui.treeView->currentIndex();
    if(modelIndex.isValid()==false) return;
    GenericNode *node = static_cast<GenericNode*>(modelIndex.internalPointer());

    menu->clear();
    if(node->isHaveHelps==true)  menu->addAction(QIcon(":/ico/read"), tr("Справка"));
    if(node->type()== Node::SIO)
    {
        SIO* sio=(SIO*)node;

        menu->addAction(QIcon(":/ico/write"),   tr("Записать"));
        QMenu *subMenu=menu->addMenu(           tr("Варианты"));
        subMenu->addAction(QIcon(":/ico/add"),  tr("Создать вариант"));
        subMenu->addAction(subMenu->addSeparator());
        menu->addAction(QIcon(":/ico/read"),    tr("Прочитать"));
        menu->addAction(QIcon(":/ico/read"),    tr("Расскрыть все поддерево"));
        menu->addAction(tr("Показать дамп"));

        for(int i=0;i<sio->variants.size();i++)
        {
            Node *nodeTemp=0;
            nodeTemp=sio->variants.at(i);

            QMenu *subMenuVariant=subMenu->addMenu(nodeTemp->displayName);

            subMenuVariant->setAttribute(Qt::WA_AlwaysShowToolTips);
            subMenuVariant->setToolTip(((VariantNode*)nodeTemp)->comment);

            QString nameTemp=nodeTemp->displayName;

            QAction* act1=subMenuVariant->addAction(QIcon(":/ico/write"),   tr("Установить"));
            QAction* act3=subMenuVariant->addAction(QIcon(":/ico/repeat"),  tr("Переименовать"));
            QAction* act2=subMenuVariant->addAction(QIcon(":/ico/refresh"), tr("Сохранить"));
            QAction* act4=subMenuVariant->addAction(QIcon(":/ico/tool"),    tr("Добавить в вариант состояния"));
            QAction* act5=subMenuVariant->addAction(QIcon(":/ico/recycle"), tr("Удалить"));

            //! прикрепим доп. данные
            act1->setData(nameTemp);
            act5->setData(nameTemp);
            act2->setData(nameTemp);
            act3->setData(nameTemp);
            act4->setData(nameTemp);
         }
    }
    else if(node->type()!=Node::PARAM && node->type()!=Node::STRUCT)
    {
        menu->addAction(QIcon(":/ico/write"),tr("Задать всем модулям"));
        menu->addAction(QIcon(":/ico/read"), tr("Прочитать все модули"));
        menu->addAction(QIcon(":/ico/read"), tr("Расскрыть все поддерево"));
    }
    else if(node->type()==Node::PARAM)
    {
        Parameter *param=(Parameter*)node;
        QAction *actBool=0;
        QAction *actHex=0;
        QAction *actDec=0;
        QAction *actOct=0;

        QAction *actDefault=0;
        QAction *actDial=0;
        QAction *actGrad=0;
        QAction *actSliderH=0;
        QAction *actSliderV=0;

        QAction *actCycle=menu->addAction(tr("Циклический опрос"));
        actCycle->setCheckable(true);

        actCycle->setChecked(param->cycle_request);

        menu->addAction(tr("Прочитать параметры"));
        if(param->typeP==Parameter::UINT || param->typeP==Parameter::INT)
        {

            QMenu *subMenuSystemNum=menu->addMenu(  tr("Система счисления"));
            actBool=subMenuSystemNum->addAction(    tr("Bool"));
            actHex=subMenuSystemNum->addAction(     tr("Hex"));
            actDec=subMenuSystemNum->addAction(     tr("Dec"));
            actOct=subMenuSystemNum->addAction(     tr("Oct"));


            actBool->setCheckable(true);
            actHex->setCheckable(true);
            actDec->setCheckable(true);
            actOct->setCheckable(true);

            if(param->modeEdit==Parameter::DEC)
            {
                actBool->setChecked(false);
                actHex->setChecked(false);
                actDec->setChecked(true);
                actOct->setChecked(false);
            }
            if(param->modeEdit==Parameter::HEX)
            {
                actBool->setChecked(false);
                actHex->setChecked(true);
                actDec->setChecked(false);
                actOct->setChecked(false);
            }
            if(param->modeEdit==Parameter::BIN)
            {
                actBool->setChecked(true);
                actHex->setChecked(false);
                actDec->setChecked(false);
                actOct->setChecked(false);
            }
            if(param->modeEdit==Parameter::OCT)
            {
                actBool->setChecked(false);
                actHex->setChecked(false);
                actDec->setChecked(false);
                actOct->setChecked(true);
            }
        }
        QMenu *subMenuIndicate=menu->addMenu(           tr("Способ редактирования"));
        actDefault=subMenuIndicate->addAction(          tr("По умолчанию"));
        if(param->typeP==Parameter::DOUBLE)
        {
            actGrad=subMenuIndicate->addAction(         tr("Градусы, минуты, секунды"));
            actGrad->setCheckable(true);
        }
        actDial=subMenuIndicate->addAction(             tr("Круговая шкала"));
        actSliderH=subMenuIndicate->addAction(          tr("Слайдер горизонтальный"));
        actSliderV=subMenuIndicate->addAction(          tr("Слайдер вертикальный"));

        /*QMenu *subMenuRestriction=menu->addMenu(      tr("Ограничение на интервал"));

        actDelRestr=subMenuRestriction->addAction(      tr("Снять ограничения"));
        actLeftRestr=subMenuRestriction->addAction(     tr("Задать ограничение слева"));
        actRightRestr=subMenuRestriction->addAction(    tr("Задать ограничение справа"));
        actDelRestr->setCheckable(true);
        if(param->restriction==true)
        {
          actDelRestr->setChecked(false);
        }else  actDelRestr->setChecked(true);*/

        actDefault->setCheckable(true);
        actDial->setCheckable(true);
        actSliderH->setCheckable(true);
        actSliderV->setCheckable(true);


        if(param->modeIndication==Parameter::DEFAULT_IND)
        {
            actDefault->setChecked(true);
            actDial->setChecked(false);
            actSliderH->setChecked(false);
            actSliderV->setChecked(false);
            if(actGrad!=0) actGrad->setChecked(false);
        }
        if(param->modeIndication==Parameter::DIAL)
        {
            actDefault->setChecked(false);
            actDial->setChecked(true);
            actSliderH->setChecked(false);
            actSliderV->setChecked(false);
            if(actGrad!=0) actGrad->setChecked(false);
        }
        if(param->modeIndication==Parameter::SLIDER_H)
        {
            actDefault->setChecked(false);
            actDial->setChecked(false);
            actSliderH->setChecked(false);
            actSliderV->setChecked(true);
            if(actGrad!=0) actGrad->setChecked(false);
        }
        if(param->modeIndication==Parameter::SLIDER_V)
        {
            actDefault->setChecked(false);
            actDial->setChecked(false);
            actSliderH->setChecked(true);
            actSliderV->setChecked(false);
            if(actGrad!=0) actGrad->setChecked(false);
        }
        if(param->modeIndication==Parameter::GRAD_MINUTE_SEC)
        {
            actDefault->setChecked(false);
            actDial->setChecked(false);
            actSliderH->setChecked(false);
            actSliderV->setChecked(false);
            if(actGrad!=0) actGrad->setChecked(true);
        }
    }
    menu->setContextMenuPolicy(Qt::ActionsContextMenu);
    menu->exec(QCursor::pos());
}
void xmlmodelview::statusRequest(bool)
{
    //15.05.2011
    /*
    if(binaryPresent->listRequest.size()==0)
    {
        if(b==true) binaryPresent->transferUDP->closeWindowWait();

        //! Здесь можно занулить списки
        ui.treeView->update(ui.treeView->currentIndex());

    }*/
}
void xmlmodelview::slot_SaveVariants()
{
    qDebug("MPPM: SaveVariants\n");
    formStatusExit->show();
    formStatusExit->setMainMsg(tr("Сохранение вариантов ПМ"));
    formStatusExit->setCountMax(domParser->sizeVariants());
    domParser->saveVariant();

    qDebug("MPPM: SaveVariantsState\n");
    formStatusExit->setMainMsg(tr("Сохранение вариантов состояния"));
    formStatusExit->setCountMax(domParser->sizeVariantsState());
    domParser->saveStateVariant();

    formStatusExit->close();
}
void xmlmodelview::selectedGenericNode(GenericNode *node)
{
    this->activateWindow();
    ui.treeView->expandAll();

    ui.treeView->setCurrentIndex(node->modelIndexByCol(0));
    ui.treeView->expand(node->modelIndexByCol(0));
    ui.treeView->setFocus();
}
void xmlmodelview::recTreeForExpanded(GenericNode* node)
{
    ui.treeView->expand(node->modelIndexByCol(0));
    for(int i=0;i<node->childVision.size();i++)
    {
        recTreeForExpanded((GenericNode*)node->childVision[i]);
    }
}
//! блокировка автоматического чтения данных при расскрытии узла
void xmlmodelview::blockAutoRead(bool pr)
{
    disconnect(ui.treeView,SIGNAL(expanded(const QModelIndex&)),this,SLOT(slotForExpanded(const QModelIndex&)));
    if(pr==false)
    {
        connect(ui.treeView,SIGNAL(expanded(const QModelIndex&)),this,SLOT(slotForExpanded(const QModelIndex&)));
    }
}
void xmlmodelview::slot_toolButtonRequestBlock(bool toggled)
{
    if(toggled==true)
    {
        requestBlock=true;
        ui.toolButtonRequestBlock->setText(tr("Заблокировано"));
    }
    else
    {
        requestBlock=false;
        ui.toolButtonRequestBlock->setText(tr("Разблокировано"));
    }
}
void xmlmodelview::slotFlushCycParam()
{
    //engineData->flushCyclicRequest();
}
void xmlmodelview::slotConnectionFind()
{

}
void xmlmodelview::slotConnectionLost()
{
    //! сбросить во всех параметрах индекс элемента в таблице
    engineData->unselectIndexSIO();
    //! свернуть структуру
    slotPushButtonCollapse();
}
xmlmodelview::~xmlmodelview()
{
    //domParser->saveVariant();
}
