#include <QStringList>

#include "nodeTrans.h"


INodeTrans::INodeTrans()
{
    prev=0;
    next=0;
    parent=0;
    child.clear();
}
INodeEqual::INodeEqual()
{
    valueL=0;
    valueR=0;
}
void INodeEqual::setValueLeft(QString value)
{
    valueLeft_=value;
    valueL=new INodeValue(value);

}
void INodeEqual::setValueRight(QString value)
{
    valueRigth_=value;
    valueR=new INodeValue(value);
}
INodeValue::INodeValue(QString value)
{
    index=-1;
}

void INodeValue::analysis(QString value)
{
    QString     tempStr="";
    QStringList tempList = value.split(".", QString::SkipEmptyParts);

    if(tempList.size()!=0)
        tempStr=tempList[0];
    else
        return;

    if(tempStr.contains("[") && tempStr.contains("]"))
    {
        int posL=tempStr.indexOf("[");
        int posR=tempStr.indexOf("]");
        if(tempStr.size()>posL)
        {
            index=(tempStr.mid(posL,posR-posL)).toInt();
        }
    }else index=-1;

    name=tempList[0];

    for(int i=1;i<tempList.size();i++)
    {
        INodeValue* temp=new INodeValue(tempList[i]);
        addChild(temp);
    }
}
