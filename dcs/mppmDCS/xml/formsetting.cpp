#include "formsetting.h"
#include "ui_formsetting.h"
#include "VariantNode.h"

FormSetting::FormSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormSetting)
{
    ui->setupUi(this);
    menu=new QMenu;
    ui->treeWidgetSetting->installEventFilter(new cl_MouseFilterSetting(ui->treeWidgetSetting,this));   
    connect(menu,SIGNAL(triggered(QAction*)),this,SLOT(slotPressButtonMouse(QAction*)));
    currentVariant=0;  
}

FormSetting::~FormSetting()
{
    delete ui;
}
cl_MouseFilterSetting::cl_MouseFilterSetting(QObject* pobj,QWidget *slotForm_):QObject(pobj)
{
    slotForm=slotForm_;
}
void FormSetting::slotPressButtonMouse(QAction* act)
{
    QTreeWidgetItem *item=ui->treeWidgetSetting->currentItem();

    if(act->text()==tr("Удалить"))
    {
        ui->treeWidgetSetting->removeItemWidget(item,0);
        for(int i=0;i<currentVariant->child.size();i++)
        {
            QString nameItemText=item->text(0);
            if(((VariantState*)(currentVariant->child[i]))->variant->displayName==nameItemText)
            {
                //ui->treeWidgetSetting->removeItemWidget(item,col);

                VariantState* node=static_cast<VariantState* > (currentVariant->child[i]);

                node->deleteVariantState();
                currentVariant->child.removeOne((Node*)node);
                setVariantState(currentVariant);

            }
        }
    }
}

bool cl_MouseFilterSetting::eventFilter(QObject* pobj,QEvent *event)
{
    Q_UNUSED(pobj);
    if(event->type()==QEvent::ContextMenu)
    {
        FormSetting *p=qobject_cast<FormSetting* >(slotForm);
        if(p!=0)
        {
            p->rightButtonMouseClicked();
            return true;
        }else return false;
    }
    return false;
}

void FormSetting::setVariantState(VariantState *node)
{
    ui->treeWidgetSetting->clear();
    QList<QTreeWidgetItem *> items;
    QList<QTreeWidgetItem *> itemsInCols;
    QStringList list;

    currentVariant=node;

    for(int i=0;i<node->child.size();i++)
    {
        VariantState* nodeVar=(VariantState*)(node->child[i]);

        if(nodeVar->variant!=0)
        {
            QStringList list;

            list.push_back(nodeVar->variant->displayName);
            list.push_back(nodeVar->variant->pathToVariant());

            items.append(new QTreeWidgetItem((QTreeWidget*)0,list));
        }
    }
    ui->treeWidgetSetting->insertTopLevelItems(0,items);    

}
void FormSetting::rightButtonMouseClicked()
{
    menu->clear();

    menu->addAction(QIcon(":/ico/recycle"),tr("Удалить"));

    menu->setContextMenuPolicy(Qt::ActionsContextMenu);
    menu->exec(QCursor::pos());

}

void FormSetting::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
