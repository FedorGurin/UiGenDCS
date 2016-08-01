#include "domParserProtocol.h"

#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include <QDebug>

#define PROTOCOL_FILE "protocol.xml"
DomParser::DomParser(QObject *parent):QObject(parent)
{
    //! дерево с описательной частью данных
    dataNodes=0;
    //! корень для дерева с описанием данных
    rootItemData=0;

    QString nameFile = qApp->applicationDirPath()+"/"+PROTOCOL_FILE;
    //! открываем файл с содержимым описывающим данные
    bool okDesData=openFileDesData(nameFile);
    if(okDesData==false)
    {
        qDebug()<<"DomParser: Can`t load file="<<nameFile;
        rootItemData=0;
        return;
    }
}
//! поиск блока
NodeBlock* DomParser::findBlockNode(uint32_t uid_block)
{
    for(int i=0;i<rootItemData->child.size();i++)
    {
        NodeBlock *node = (NodeBlock*)(rootItemData->child[i]);
        if(node->uid == uid_block)
        {
            return node;
        }
    }
    return 0;
}
void DomParser::parseData(const QDomElement &element, NodeProtocol *parent)
{
    NodeProtocol *item=0;
    QDomElement ele=element.firstChildElement();
    while(!ele.isNull())
    {
        QString tagName = ele.tagName();
        if(tagName        == tr("BlockInputData"))    {item=new NodeInputBlock (ele,parent);}
        else if(tagName   == tr("BlockOutputData"))   {item=new NodeOutputBlock(ele,parent);}
        else if(tagName   == tr("UseCommand"))        {item=new NodeUseCommand (ele,parent);}
        else if(tagName   == tr("DefCommand"))        {item=new NodeDefCommand (ele,parent);}

       /* if(item!=0)
            parseData(ele,item);*/
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
            rootItemData=new NodeProtocol;
            QDomElement root=domDesData.documentElement();
            parseData(root.toElement(),rootItemData);
        }
        else
        {
            ok=false;
            qDebug()<<"DomParser: Error in structure of xml";
           /* QMessageBox::warning(0,tr("Внимание"),
                                 tr("Ошибка в структуре XML файла = ")+SettingXML::getInstance()->fileData+"\n\nError msg="
                                 +errMsg+"\nLine="+QString::number(errLine)+"\nColumn="+QString::number(errColumn));*/

            //qApp->quit();
        }
    }
    else
    {
        ok=false;
        /*QMessageBox::warning(0,tr("Внимание"),
                             tr("Файл не найден = ")+SettingXML::getInstance()->fileData);*/
    }
    return ok;
}


DomParser::~DomParser() {
        // TODO Auto-generated destructor stub
}
