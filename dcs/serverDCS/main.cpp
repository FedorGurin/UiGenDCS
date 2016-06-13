#include <QCoreApplication>

#include "kernel/kernel_mppm.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //
    KernelMPPM *kernel=new KernelMPPM;

    return a.exec();
}
