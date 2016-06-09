#include "formRenameVariant.h"
#include "ui_formRenameVariant.h"
#include "VariantNode.h"
#include "VariantState.h"

FormRenameVariant::FormRenameVariant(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormRenameVariant)
{
    ui->setupUi(this);
    connect(ui->pushButtonOk,SIGNAL(clicked()),this,SLOT(slotPushButton()));
    node=0;
    this->setWindowTitle(tr("Задайте имя варианта"));
}

FormRenameVariant::~FormRenameVariant()
{
    delete ui;
}
void FormRenameVariant::setVariant(Node* node_)
    {
    if(node_!=0)
    {
        node=node_;
        ui->lineEdit->setText(node->displayName);
        ui->lineEdit->selectAll();
    }
}

void FormRenameVariant::slotPushButton()
{
    QString name=ui->lineEdit->text();

    if(node->type()==Node::VARIANTPM)
    {
        ((VariantNode*)node)->displayName=name;
        ((VariantNode*)node)->idName=name;

    }
    if(node->type()==Node::VARIANTSTATE)
    {
        ((VariantState*)node)->displayName=name;
        ((VariantState*)node)->idName=name;
    }
    close();
    emit acpect(true);
}

void FormRenameVariant::changeEvent(QEvent *e)
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
