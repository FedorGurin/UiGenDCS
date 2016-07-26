#include <QCoreApplication>
#include "../../proxyDCS/proxyDCS.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ProxyDCS *proxyDCS = new ProxyDCS();
    return a.exec();
}

