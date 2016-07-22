#include <QCoreApplication>
#include "../../proxyDCS/ProxyDCS.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ProxyDCS *proxyDCS = new ProxyDCS();
    return a.exec();
}

