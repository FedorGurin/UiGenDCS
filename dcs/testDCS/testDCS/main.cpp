#include <QApplication>
#include "form.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Form form;
    form.show();

    ProxyDCS *proxyDCS = new ProxyDCS();

    //! создаем запрос
    CommandRequestDCS req("idName");
    req.uid_block   = 102;
    req.cyclic      = 0;

    //! отправляем команду
    req.append("value1","-1");
    req.append("value2","0");
    req.append("value3","1");
    //! отправляем запрос
    proxyDCS->sendRequest(req);
    return a.exec();
}

