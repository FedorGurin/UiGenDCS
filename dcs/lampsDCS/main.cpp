#include "mainwindowlamps.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindowLamps w;
    w.show();

    return a.exec();
}
