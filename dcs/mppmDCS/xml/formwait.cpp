#include "formwait.h"
#include "ui_formwait.h"

FormWait::FormWait(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::FormWait)
{
    m_ui->setupUi(this);
   connect(m_ui->pushButton,SIGNAL(clicked()),this,SLOT(slot_pushButton()));
}

FormWait::~FormWait()
{
    delete m_ui;
}
void FormWait::slot_pushButton()
{
    m_ui->textBrowser->clear();
    close();
}
//! Установить новое значение
void FormWait::setValue(int value)
{
    m_ui->progressBar->setValue(value);
}
//! Добавить сообщение
void FormWait::setMessage(const QString& name)
{
    m_ui->textBrowser->append(name);
}
//! Убрать все сообщения
void FormWait::clearMessages()
{
    m_ui->textBrowser->clear();
}
void FormWait::changeEvent(QEvent *e)
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
