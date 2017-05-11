#include "form.h"
#include "ui_form.h"
#include "fedor_msg.pb.h"
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    proxyDCS = new ProxyDCS();

    connect(ui->pushButtonSendReq,SIGNAL(clicked(bool)),this,SLOT(send(bool)));
}

void Form::send(bool value)
{
    CommandRequestDCS req("idName");
    req.uid_block   = 102;
    req.cyclic      = 0;

    //! отправляем команду
    req.append("value1","-1");
    req.append("value2","0");
    req.append("value3","1");

    proxyDCS->sendRequest(req);

    fedor::SearhRequest request;
    request.set_name("Hello");
}

Form::~Form()
{
    delete ui;
}
