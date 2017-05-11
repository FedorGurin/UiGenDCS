#include "mainwindow.h"
#include <QApplication>
#include "parserMemDCS.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    QByteArray array;
    QDataStream in(&array,QIODevice::WriteOnly);
    in.setVersion(QDataStream::Qt_4_2);
    in.setByteOrder(QDataStream::LittleEndian);//закомментировать только для отладки

    in<<1.f<<2.f<<3.f<<4.f;

    initXmlSerialLib();
    Node* node = loadFileXmlSerialLib("F:/MyProg/Trenager/submodel/UiGenDCS/dcs/testParserDCS/TestParserMemDCS/data.xml");
    cpyMemToTreeSerialLib(node,&array);
    QStringList list = convertValueTreeToStrings(node);
    return a.exec();
}
