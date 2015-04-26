#include "formsetname.h"
#include "ui_formsetname.h"

FormSetName::FormSetName(EngineData *engineData_,QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::FormSetName)
{
    m_ui->setupUi(this);
    engineData=engineData_;
    connect(m_ui->pushButton,SIGNAL(clicked()),this,SLOT(slotPushButton()));
    connect(m_ui->pushButtonSelectParam,SIGNAL(clicked()),this,SLOT(slotPushButtonSelectParam()));
}

FormSetName::~FormSetName()
{
    delete m_ui;
}
void FormSetName::enableSelectParam(bool f)
{
    m_ui->pushButtonSelectParam->setEnabled(f);
}
void FormSetName::slotPushButton()
{   
    emit setName(m_ui->lineEdit->text(),m_ui->textEditComment->toPlainText());
}
void FormSetName::slotPushButtonSelectParam()
{
    if(engineData!=0)
    {
        engineData->treeWidget->move(mapToGlobal(m_ui->pushButtonSelectParam->pos()));
        engineData->treeWidget->show();
    }
}

void FormSetName::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
