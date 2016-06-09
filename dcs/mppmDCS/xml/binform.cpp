#include "binform.h"
#include "ui_binform.h"

BinForm::BinForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BinForm)
{
    ui->setupUi(this);
}

BinForm::~BinForm()
{
    delete ui;
}

void BinForm::changeEvent(QEvent *e)
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
