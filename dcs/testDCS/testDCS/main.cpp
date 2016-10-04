#include <QCoreApplication>
#include "../../proxyDCS/proxyDCS.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ProxyDCS *proxyDCS = new ProxyDCS();

    CommandRequestDCS req("idName");
    req.uid_block   = 102;
    req.cyclic      = 0;

    //! отправляем команду
    req.append("value1","-1");
    req.append("value2","0");
    req.append("value3","1");

    proxyDCS->sendRequest(req);
    return a.exec();
}

