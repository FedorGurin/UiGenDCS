#include "domParser.h"
#include "structure.h"
#include "parameter.h"

#include <QFile>
#include <QTextStream>


DomParser::DomParser(QObject *parent):QObject(parent)
{
    //! дерево с описательной частью данных
    dataNodes=0;  

    //! корень для дерева с описанием данных
    rootItemData=0;

    //! открываем файл с содержимым описывающим данные
    bool okDesData=openFileDesData(qApp->applicationDirPath()+"/xml/"+"data.xml");
    if(okDesData==false)
    {
        rootItemData=0;
        return;
    }
}
void DomParser::parseData(const QDomElement &element, Node *parent)
{
    GenericNode *item=0;
    QDomElement ele=element.firstChildElement();
    while(!ele.isNull())
    {
        if(ele.tagName()=="param")
            item=new Parameter (ele,parent);

        if(item!=0)
            parseData(ele,item);
        if(ele.tagName()=="struct")
        {
            Structure *item=new Structure(ele,parent);
            //! рекурсия в содержимое
            parseData(ele,item);
            item->addMassiveStruct();
        }
        item=0;
        ele=ele.nextSiblingElement();
    }
}
bool DomParser::openFileDesData(const QString &nameFile)
{
    //! DOM - дерево c  описанием данных
    QDomDocument domDesData;

    QFile file(nameFile);
    bool openFile=false;
    bool ok=true;

    openFile=file.open(QIODevice::ReadOnly | QIODevice::Text);

    if(openFile==true)
    {
        bool readXML=false;
        QString errMsg="";
        int errLine=0;
        int errColumn=0;
        readXML=domDesData.setContent(&file,true,&errMsg,&errLine,&errColumn);

        if(readXML==true)
        {
            rootItemData=new GenericNode;
            QDomElement root=domDesData.documentElement();
            parseData(root.toElement(),rootItemData);
        }
        else
        {
            ok=false;
            QMessageBox::warning(0,tr("Внимание"),
                                 tr("Ошибка в структуре XML файла = ")+SettingXML::getInstance()->fileData+"\n\nError msg="
                                 +errMsg+"\nLine="+QString::number(errLine)+"\nColumn="+QString::number(errColumn));

            //qApp->quit();
        }
    }
    else
    {
        ok=false;
        QMessageBox::warning(0,tr("Внимание"),
                             tr("Файл не найден = ")+SettingXML::getInstance()->fileData);
    }
    return ok;
}

DomParser::~DomParser() {
        // TODO Auto-generated destructor stub
}
