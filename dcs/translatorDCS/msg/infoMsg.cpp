#include "infoMsg.h"
#include "ui_infomsg.h"

InfoMsg::InfoMsg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoMsg)
{
    ui->setupUi(this);
    connect(ui->pushButtonNext,SIGNAL(clicked()),this,SIGNAL(signalNextButtton()));
}
void InfoMsg::setMsg(QString msg)
{
    ui->labelMsg->setText(msg);
}

InfoMsg::~InfoMsg()
{
    delete ui;
}
