#include "dialform.h"
#include "ui_dialform.h"

DialForm::DialForm(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::DialForm)
{
    m_ui->setupUi(this);
    dial=m_ui->dial;
}

DialForm::~DialForm()
{
    delete m_ui;
}
void DialForm::setValue(int value)
{
   m_ui->dial->setValue(value);
   m_ui->lcdNumber->display(value);
}
void DialForm::setLimitMax(int max)
{
    m_ui->labelMax->setText(tr("Макс: ")+QString::number(max));
    m_ui->dial->setMaximum(max);

}
void DialForm::setLimitMin(int min)
{
    m_ui->labelMin->setText(tr("Мин: ")+QString::number(min));
    m_ui->dial->setMinimum(min);

}
int DialForm::value()
{
    return m_ui->dial->value();
}

void DialForm::changeEvent(QEvent *e)
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
