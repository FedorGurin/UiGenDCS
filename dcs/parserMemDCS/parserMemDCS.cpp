#include "parserMemDCS.h"
#include "domParser.h"
#include "binaryPresent.h"
#include "parameter.h"
//! иницализация сериализации XML
void initXmlSerialLib()
{
    DomParser::obj();
    BinaryPresent::obj();
}
//! загрузка файла XML для сериализации
Node* loadFileXmlSerialLib(QString nameFile)
{
    DomParser::obj()->openFileDesData(nameFile);
    return DomParser::obj()->rootItemData;
}
//! копирование памяти в узлы дерева
void cpyMemToTreeSerialLib(Node* toNode, QByteArray *fromMem)
{
    BinaryPresent::obj()->getData(toNode,fromMem);
}
//! копирование данных из узлов в память
void cpyTreeToMemSerialLib(Node* fromNode, QByteArray *toMem)
{
    BinaryPresent::obj()->getData(fromNode,toMem);
}
//! преобразование дерева в список строк
QStringList convertValueTreeToStrings(Node* root)
{
    QStringList list;
    for(int i=0;i<root->child.size();i++)
    {
        if(root->child[i]->type() == Node::PARAM)
        {
            Parameter *param = static_cast<Parameter* >(root->child[i]);
            list<<param->value;
        }else
        {
            list<<convertValueTreeToStrings(root->child[i]);
        }
    }
    return list;
}
void convertTitleTreeToStrings(Node* root,QStringList& listName,QStringList& listMes)
{
    //QStringList list;
    if(root == 0)
        return;
    for(int i=0;i<root->child.size();i++)
    {
        if(root->child[i]->type() == Node::PARAM)
        {
            Parameter *param = static_cast<Parameter* >(root->child[i]);
            listName<<param->displayName;
            listMes<<param->messure;

        }else
        {
            /*QStringList childList =*/ convertTitleTreeToStrings(root->child[i],listName,listMes);

//            for(int j=0;j<childList.size();j++)
//            {
//                listName<<(root->child[i]->displayName+"." + childList[j]);
//            }
        }
    }
   // return list;
}
//! очистка узлов дерева
void clearTreeSerialLib()
{

}
