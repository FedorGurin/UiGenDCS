/*
 * ModelData.cpp
 *
 *  Created on: 27.08.2008
 *      Author: Fedor
 */

#include "ModelData.h"
#include "Parameter.h"

#include "../globalFunc/gl_func.h"

ModelData::ModelData(QObject *parent):QAbstractItemModel(parent)
{
    // TODO Auto-generated constructor stub
    rootNode=0;
    sizeFont=0;
}
Qt::ItemFlags ModelData::flags(const QModelIndex &index) const
 {
     if (!index.isValid())
         return 0;
     //! Первая колонка не подлежит изменению

     GenericNode *node = nodeFromIndex(index);
     if(node->isDisplay==false)
         return 0;

     if(index.column()>3)
     {
         if(node->type() == Node::PARAM)
         {
             Parameter *tempParam=static_cast<Parameter* > (node);
             if(tempParam->readOnly==0)
                 return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
         }
     }
     return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
 }
void ModelData::setRootNode(GenericNode* node)
{
    //delete rootNode;
    rootNode=node;
    //reset();
}
QModelIndex ModelData::index(int row,int column,const QModelIndex &parent)const
{
    if (!hasIndex(row, column, parent))
         return QModelIndex();

    GenericNode *parentNode=nodeFromIndex(parent);
    if(parentNode)
    {
        if(((GenericNode *)parentNode->childVision[row])->isDisplay==true)
        {
            QModelIndex tempModelIndex=createIndex(row,column,parentNode->childVision[row]);
            parentNode->childVision[row]->addModelIndex(tempModelIndex,column);
            return tempModelIndex;
        }
    }
    return QModelIndex();

}
void ModelData::resetData()
{
    //reset();
}
void ModelData::refreshItemData(QVector<GenericNode* > nodes)
{
    //emit layoutChanged();

    //! сигнал об обновлении данных
    emit dataChanged(nodes[0]->modelIndexByCol(4),
                     nodes[0]->modelIndexByCol(4));
}
GenericNode* ModelData::nodeFromIndex(const QModelIndex &index)const
{
    if(index.isValid())
    {
        return static_cast<GenericNode*>(index.internalPointer());
    }else
        return rootNode;
}
int ModelData::rowCount(const QModelIndex &parent)const
{
    GenericNode* parentNode=nodeFromIndex(parent);
    if(!parentNode)
        return 0;
    return parentNode->childVision.count();
}
int ModelData::columnCount(const QModelIndex &)const
{
    return 5;
}
QModelIndex ModelData::parent(const QModelIndex &child) const
{
    GenericNode *node = nodeFromIndex(child);
    if (!node)
        return QModelIndex();

    //if(node->isDisplay==false)  return QModelIndex();

    GenericNode *parentNode = (GenericNode *)node->parent;
    if (!parentNode)
        return QModelIndex();

    GenericNode *grandparentNode = (GenericNode *)parentNode->parent;
    if (!grandparentNode)
        return QModelIndex();

    int row = grandparentNode->childVision.indexOf(parentNode);

    QModelIndex tempModelIndex=createIndex(row,4, parentNode);
    parentNode->addModelIndex(tempModelIndex,4);
    return tempModelIndex;
}
QVariant ModelData::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())     return QVariant();

    GenericNode *node = nodeFromIndex(index);
    if (!node) return QVariant();

    if (role == Qt::DisplayRole)
    {
        if (index.column() == 0)
        {
            return node->displayName;
        }
        else if(index.column()==1)
        {
            if(node->isHaveHelps==true) return QString("Yes");
        }
        else if(index.column()==2)
        {
            if(node->type()==Node::PARAM)
            {
                Parameter* tempNode=static_cast<Parameter* >(node);
                return tempNode->messure;
            }
        }else if(index.column()==3)
        {
            if(node->type()==Node::PARAM)
            {
                Parameter* tempNode=static_cast<Parameter* >(node);
                return tempNode->condition;
            }
        }
        else if (index.column() == 4)
        {
            if(node->type()==Node::PARAM)
            {
                Parameter* tempNode=static_cast<Parameter* >(node);
                QString str=tempNode->value;
                bool ok=false;

                if(tempNode->typeP!=Parameter::BIT)
                {
                    if(tempNode->modeEdit==Parameter::HEX)   str=QString::number(str.toInt(&ok,10),16);
                    if(tempNode->modeEdit==Parameter::BIN)   str=QString::number(str.toInt(&ok,10),2);
                    if(tempNode->modeEdit==Parameter::OCT)   str=QString::number(str.toInt(&ok,10),8);
                    if(tempNode->modeIndication==Parameter::GRAD_MINUTE_SEC)
                    {
                        Tcordd coord=float_to_coord(str.toDouble());
                        str=QString::number(coord.grad)+tr("°")+
                                QString::number(coord.min)+tr("'")+
                                QString::number(coord.sec,'g',12)+tr("\"");
                    }
                }

                if(tempNode->testHaveEnumParam()==true)
                {
                    return tempNode->nameEnum(str);
                }

                return str;
            }
        }
    }else if(role==Qt::FontRole)
    {

        if (index.column() == 0)
        {
            if(node->type()==Node::GROUP)         return QFont("Times", sizeFont, QFont::Bold);
            else if(node->type()==Node::PM)       return QFont("Helvetica [Cronyx]", sizeFont, QFont::Light,true);
            else if(node->type()==Node::SIO)      return QFont("Times", sizeFont, QFont::Bold,true);

        }else if(index.column()== 4)
        {
            if(node->type()==Node::PARAM)
            {
                Parameter* tempNode=static_cast<Parameter* >(node);
                QString str=tempNode->value;

                if(str==tr("True") || str=="1")  return QFont("Times", sizeFont, QFont::Bold);
            }
        }
        return QFont("Times", sizeFont, QFont::Normal);
    }else if(role==Qt::BackgroundRole)
    {
        if(index.column()==0)
        {
            if(node->type()==Node::SIO)
            {
                QLinearGradient linearGrad(QPointF(0, 0), QPointF(1, 0));
                linearGrad.setColorAt(0, Qt::white);
                linearGrad.setColorAt(1, Qt::lightGray);
                return QBrush(linearGrad);
            }
        }
        if(node->type()==Node::PARAM)
        {
            Parameter *param=static_cast<Parameter* >(node);
            if(param->cycle_request==true)
            {
                return QBrush(QColor(Qt::darkGreen));
            }else if(param->modeEdit!=Parameter::DEC)
            {
                return QBrush(QColor(0, 0, 255, 127));
            }/*else
            {
                if(param->modifyValueLastStep==true)
                {
                    return QFont("Times", 10, QFont::Bold);
                }else
                {
                    return QFont("Times", 10, QFont::Bold);
                }
            }*/
        }

    }else if(role==Qt::TextColorRole)
    {
        if(index.column()== 4)
        {
            if(node->type()==Node::PARAM)
            {
                Parameter* tempNode=static_cast<Parameter* >(node);
                if(tempNode->modifyValueLastStep==true)
                {
                    return QColor(Qt::red);
                }else
                {
                    return QColor(Qt::black);
                }
            }
        }
    }else if(role==Qt::ToolTipRole)
    {
        if(node->type()==Node::PARAM)
        {
            Parameter* tempNode=static_cast<Parameter* >(node);
            return QString(tr("id:")+tempNode->idName);
        }
    }
    return QVariant();
}
bool ModelData::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role);
    if (!index.isValid())
        return false;

    GenericNode *node = nodeFromIndex(index);

    if (!node)
        return false;

    if (index.column() ==4)
    {
        if(node->type()==Node::PARAM)
        {
            QString tempValue=value.toString();

            bool ok;
            Parameter *param=static_cast<Parameter* >(node);
            if(param->typeP!=Parameter::BIT)
            {
                if(param->modeEdit==Parameter::HEX)    tempValue=QString::number(tempValue.toInt(&ok,16));
                if(param->modeEdit==Parameter::BIN)    tempValue=QString::number(tempValue.toInt(&ok,2));
                if(param->modeEdit==Parameter::OCT)    tempValue=QString::number(tempValue.toInt(&ok,8));
                if(param->modeIndication==Parameter::GRAD_MINUTE_SEC)
                {
                    QStringList list=tempValue.split(QRegExp(tr("[°'\"]")),QString::SkipEmptyParts);

                    int grad=0,min=0;
                    double sec=0;

                    if(list.size()==3)
                    {
                        grad=list[0].toInt();
                        min=list[1].toInt();
                        sec=list[2].toDouble();
                    }
                    double v=coord_to_float(grad,min,sec);

                    tempValue=QString::number(v,'g',12);
                }
            }
            param->value=tempValue;
            if(param->testHaveEnumParam()==true)
                param->value=param->valueEnum(tempValue);
        }

        emit refreshData(node); // сигнал о том, что данные поменялись
    }
    return true;
}
QVariant ModelData::headerData(int section,Qt::Orientation orientation, int role)const
{
    if(section==4)
    {
        if(role==Qt::SizeHintRole)
        {
            if(orientation == Qt::Horizontal)
            {
                QSize size(180,15);
                //size.scale(350,15);
                return size;
            }
        }
    }
    if(role==Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            if(section==0)return QString(tr("Название"));
            else if(section==1)return QString(tr("Справка"));
            else if(section==2)return QString(tr("Ед. измерения"));
            else if(section==3)return QString(tr("Условие"));
            else if(section==4)return QString(tr("Значение"));
        }
    }else if(role==Qt::FontRole)
    {
        if(sizeFont==0)    return QFont("Times", 10, QFont::Bold);
        else return QFont("Times", sizeFont, QFont::Bold);
    }
    return QVariant();
}
ModelData::~ModelData() {
    // TODO Auto-generated destructor stub
    delete rootNode;
}

