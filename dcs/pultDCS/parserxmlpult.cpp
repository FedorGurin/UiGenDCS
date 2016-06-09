#include "parserxmlpult.h"

#include <QMessageBox>
#include <QDomDocument>
#include <QApplication>
#include <QFile>

#define PULT_FILE "vpult.xml"

ParserXMLPult::ParserXMLPult(EngineData *engine_)
{
    engine=engine_;
    openXMLFile(qApp->applicationDirPath()+"/xml/"+QString(PULT_FILE));
}
void ParserXMLPult::openXMLFile(const QString &nameFile)
{
    //! DOM - дерево
    QDomDocument dom;

    bool openFile=false;
    QFile file(nameFile);

    openFile=file.open(QIODevice::ReadOnly);
    if(openFile==true)
    {
        bool readXML=false;
        QString errMsg="";
        int errLine=0;
        int errColumn=0;
        readXML=dom.setContent(&file,true,&errMsg,&errLine,&errColumn);

        if(readXML==true)
        {
            QDomElement root=dom.documentElement();
            parse(root.toElement());
            qDebug("list.size()=%d\n",list.size());
        }
        else
        {
            QMessageBox::warning(0,tr("Внимание"),
                                 tr("Ошибка в структуре XML файла \n = ")+QString(PULT_FILE)+"\nError msg="
                                 +errMsg+"\nLine="+errLine+"\nColumn="+errColumn);
        }
    }
#ifdef PRINT_WARNING_LOAD_FILE
    else
    {
        QMessageBox::warning(0,tr("Внимание"),
                             tr("Файл не найден = ")+QString(PULT_FILE));
    }
#endif

}
void ParserXMLPult::parse(const QDomElement &element)
{
    ToggleSwitch *toggle=0;
    QDomElement ele=element.firstChildElement();
    while(!ele.isNull())
    {
        if(ele.tagName()==tr("toggle"))
        {
            toggle=new ToggleSwitch(&ele);
            toggle->setEngine(engine);
            list.push_back(toggle);
        }else if(ele.tagName()==tr("pages"))
        {
            namePages.append((ele.attribute("name",tr("не задано"))));
        }
        if(toggle!=0) parse(ele);
        ele=ele.nextSiblingElement();
    }
}
