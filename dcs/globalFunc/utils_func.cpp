#include "utils_func.h"
#include <QFile>
#include <QTextStream>
QString readParamFromXMLFile(QString fileName,
                             QString nameProg,
                             QString nameAttrib,
                             QString defaultStr)
{
    bool openFile=false;
    QString tempName(defaultStr);
    QFile file(fileName);
    QDomDocument domDoc;
    openFile=file.open(QIODevice::ReadOnly);
    if(openFile==true)
    {
        bool readXML=false;
        readXML=domDoc.setContent(&file,true);
        if(readXML==true)
        {
            QDomElement ele1=domDoc.firstChildElement("data");
            QDomElement ele=ele1.firstChildElement(nameProg);
            QString tempName=ele.attribute(nameAttrib,defaultStr);
            return tempName;
        }
    }else qDebug("ReadParamFromXMLFile: File not find=%s\n nameProg=%s\n nameAttrib=%s\n",qPrintable(fileName),qPrintable(nameProg),qPrintable(nameAttrib));
    return tempName;
}
bool writeAttrParamToXMLFile(QString fileName,QString nameProg,QString nameAttrib,QString value)
{
    bool openFile=false;
    //QString tempName("");
    QFile file(fileName);
    QDomDocument domDoc;
    openFile=file.open(QIODevice::ReadWrite|QIODevice::Text);
    QTextStream out(&file);
    if(openFile==true)
    {
        bool readXML=false;
        readXML=domDoc.setContent(&file,true);
        if(readXML==true)
        {
            QDomElement ele1=domDoc.firstChildElement("data");
            QDomElement ele=ele1.firstChildElement(nameProg);
            ele.setAttribute("dasda","324");
            //domDoc.appendChild(ele1);
            domDoc.save(out,4);
            //return ele;
        }
    }else qDebug("ReadParamFromXMLFile: File not find=%s\n",qPrintable(fileName));

    return false;
    //return QDomElement();
}

QDomElement paramFromXMLFileWithAttrib(QString fileName,QString nameProg,QString nameAttrib)
{
    bool openFile=false;
    QString tempName("");
    QFile file(fileName);
    QDomDocument domDoc;
    openFile=file.open(QIODevice::ReadOnly);
    if(openFile==true)
    {
        bool readXML=false;
        readXML=domDoc.setContent(&file,true);
        if(readXML==true)
        {
            QDomElement ele1=domDoc.firstChildElement("data");
            QDomElement ele=ele1.firstChildElement(nameProg);

            return ele;
        }
    }else qDebug("ReadParamFromXMLFile: File not find=%s\n",qPrintable(fileName));

    return QDomElement();
}
