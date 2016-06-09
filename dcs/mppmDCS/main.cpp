#include "./xml/xmlmodelview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //! имя файла с настройками
    nameMainFile="xml/setting.xml";
    if(argc>1)
        nameMainFile="xml/"+QString(argv[1]);

    //! менеждер параметров программных модулей (МППМ)
    xmlmodelview *mppm=new xmlmodelview();
    mppm->show();
    return a.exec();
}
