#include <QCoreApplication>
#include "../../proxyDCS/proxyDCS.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ProxyDCS *proxyDCS = new ProxyDCS();

    CommandRequestDCS req;
    req.uid_block = 102;
    req.cyclic = 0;

    //! отправляем команду
    req.append("Value1","value");
    req.append("Value2","value");
    req.append("Value3","value");

    proxyDCS->sendRequest(req);
    return a.exec();
}

