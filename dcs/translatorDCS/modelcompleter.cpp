#include "modelcompleter.h"
#include <QFont>
ModelCompleter::ModelCompleter(QCompleter *completer_,QObject *parent) :
    QAbstractItemModel(parent)
{
    rootNode=0;
    completer=completer_;
}
Qt::ItemFlags ModelCompleter::flags(const QModelIndex &index) const
 {
     if (!index.isValid())  return 0;
     return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
 }
void ModelCompleter::setRootNode(GenericNode* node){

    //delete rootNode;
    rootNode=node;
    //reset();
}
QModelIndex ModelCompleter::index(int row,int column,const QModelIndex &parent)const
{
    if (!hasIndex(row, column, parent))
         return QModelIndex();

    GenericNode *parentNode=nodeFromIndex(parent);
    if(parentNode)
    {
        QModelIndex tempModelIndex=createIndex(row,column,parentNode->child[row]);
        //parentNode->child[row]->index=tempModelIndex;
        return tempModelIndex;
    }
    return QModelIndex();
}
GenericNode* ModelCompleter::nodeFromIndex(const QModelIndex &index)const{
    if(index.isValid()){
        return static_cast<GenericNode*>(index.internalPointer());
        }else return rootNode;
}
int ModelCompleter::rowCount(const QModelIndex &parent)const{

    GenericNode* parentNode=nodeFromIndex(parent);

    if(!parentNode)return 0;

    return parentNode->child.count();
}
int ModelCompleter::columnCount(const QModelIndex&)const
{
    return 1;
}
QModelIndex ModelCompleter::parent(const QModelIndex &child) const
{
    GenericNode *node = nodeFromIndex(child);
    if (!node)  return QModelIndex();

    GenericNode *parentNode = (GenericNode *)node->parent;
    if (!parentNode)    return QModelIndex();

    GenericNode *grandparentNode = (GenericNode *)parentNode->parent;
    if (!grandparentNode)   return QModelIndex();

    int row = grandparentNode->child.indexOf(parentNode);

    QModelIndex tempModelIndex=createIndex(row,2, parentNode);

    return tempModelIndex;
}
QVariant ModelCompleter::data(const QModelIndex &index, int role) const
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
    }
    return QVariant();
}
bool ModelCompleter::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(value);
    Q_UNUSED(role);
    if (!index.isValid())
        return false;

    GenericNode *node = nodeFromIndex(index);

    if (!node)
        return false;

    return true;
}
QVariant ModelCompleter::headerData(int section,Qt::Orientation orientation, int role)const
{
    if(role==Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            if(section==0)return QString(tr("Название"));
        }
    }else if(role==Qt::FontRole)
    {
        return QFont("Times", 10, QFont::Bold);
    }
    return QVariant();
}


