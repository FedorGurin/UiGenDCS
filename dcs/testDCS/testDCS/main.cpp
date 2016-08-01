#include <QCoreApplication>
#include "../../proxyDCS/proxyDCS.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ProxyDCS *proxyDCS = new ProxyDCS();

    RequestDCS req;
    req.uid_block = 102;
    req.cyclic = 0;

    proxyDCS->sendRequest(req);
    return a.exec();
}

