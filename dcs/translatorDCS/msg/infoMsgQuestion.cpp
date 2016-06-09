#include "infoMsgQuestion.h"
#include "ui_infomsgquestion.h"

InfoMsgQuestion::InfoMsgQuestion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoMsgQuestion)
{
    ui->setupUi(this);
    connect(ui->pushButtonYes,SIGNAL(clicked(bool)),this,SLOT(slotButtonYes()));
    connect(ui->pushButtonNo,SIGNAL(clicked(bool)),this,SLOT(slotButtonNo()));
}
void InfoMsgQuestion::setMsg(QString str)
{
    ui->textEdit->setText(str);
}

InfoMsgQuestion::~InfoMsgQuestion()
{
    delete ui;
}
void InfoMsgQuestion::slotButtonYes()
{
    emit signalAnswer(true);
}

void InfoMsgQuestion::slotButtonNo()
{
    emit signalAnswer(false);
}

