/*
 * DomParser.cpp
 *
 *  Created on: 27.08.2008
 *      Author: Fedor Gurin
 */

#include "DomParser.h"


#include "PModule.h"
#include "SIO.h"
#include "Structure.h"
#include "Parameter.h"
#include "GroupLabel.h"
#include "SettingXML.h"

#include <QFile>
#include <QTextStream>
//#define PRINT_WARNING_LOAD_FILE

DomParser::DomParser(QObject *parent):QObject(parent)
{
    //! дерево с описательной частью данных
    dataNodes=0;
    //! дерево с вариантами значений
    variantsNodes=0;
    //! дерево с вариантами состояния
    variantsStateNodes=0;

    //! корень для дерева с описанием данных
    rootItemData=0;
    //! корень для дерева с вариантами
    rootItemVariant=0;
    //! корень для дерева с вариантами состояний
    rootItemVariantState=0;

    //! открываем файл с содержимым описывающим данные
    bool okDesData=openFileDesData(qApp->applicationDirPath()+"/xml/"+SettingXML::getInstance()->fileData);
    if(okDesData==false)
    {
        rootItemData=0;
        return;
    }
    //! открываем файл с вариантами
    openFileVariants(qApp->applicationDirPath()+"/xml/"+QString(VARIANT_FILE));
    openFileVariantsState(qApp->applicationDirPath()+"/xml/"+QString(VARIANTSTATE_FILE));

    //! в случае если вариантов нет, то не нужно сливать деревья
    if(rootItemVariant!=0)
    {
        if(rootItemVariant->child.isEmpty()==false)
        {
            joiningTrees(rootItemData,(VariantNode*)(rootItemVariant));
            joiningVariantsTrees(rootItemVariant,rootItemVariantState);
            checkVariansState();
        }else
            variantsStateNodes=0;
    }
}
//! кол-во вариантов
int DomParser::sizeVariants()
{
    if(rootItemVariant==0)
        return 0;
    return rootItemVariant->child.size();
}
//! кол-во вариантов состояния
int DomParser::sizeVariantsState()
{
    if(rootItemVariantState==0)
        return 0;
    return rootItemVariantState->child.size();
}
bool DomParser::checkTailVariants(VariantNode* variantNodes,VariantState *variantState)
{
    if(variantNodes==0 || variantState==0)
        return false;

    if(variantNodes->child.size()!=1
       && variantState->child.size()!=1)
        return false;

    Node *varNodes=variantNodes->child[0];
    Node *varSNodes=variantState->child[0];

    if(varNodes->type()==Node::PM && varSNodes->type()==Node::PM)
    {
        if(varNodes->idName==varSNodes->idName)
        {
            varNodes=varNodes->child[0];
            varSNodes=varSNodes->child[0];
            if(varNodes->idName==varSNodes->idName)
                return true;
            else
                return false;
        }else
            return false;
    }else
        return false;
}
void DomParser::parseData(const QDomElement &element, GenericNode *parent)
{
    GenericNode *item=0;
    QDomElement ele=element.firstChildElement();
    while(!ele.isNull())
    {
        if(ele.tagName()=="pmodule")    {item=new PModule   (ele,parent);}
        else if(ele.tagName()=="sio")   {item=new SIO       (ele,parent);}
        else if(ele.tagName()=="param") {item=new Parameter (ele,parent);}
        else if(ele.tagName()=="group") {item=new GroupLabel(ele,parent);}

        if(item!=0) parseData(ele,item);
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
void DomParser::parseVariantState(const QDomElement& element, VariantState *parent)
{
    VariantState *item=0;
    QDomElement ele=element.firstChildElement();

    while(!ele.isNull())
    {
        item=new VariantState(ele,parent);

        if(item!=0) parseVariantState(ele,item);
        item=0;
        ele=ele.nextSiblingElement();
    }
}

void DomParser::parseVariant(const QDomElement& element, VariantNode *parent)
{
    VariantNode *item=0;//Узел варианта

    QDomElement ele=element.firstChildElement();

    while(!ele.isNull())
    {
        item=new VariantNode(ele,parent);
        if(item!=0) parseVariant(ele,item);
        item=0;
        ele=ele.nextSiblingElement();
    }
}

void DomParser::openFileVariants(const QString &nameFile)
{
    //! DOM - дерево вариантов
    QDomDocument domVariants;

    bool openFile=false;
    QFile file(nameFile);

    openFile=file.open(QIODevice::ReadOnly);
    rootItemVariant=new VariantNode;
    if(openFile==true)
    {
        bool readXML=false;
        QString errMsg="";
        int errLine=0;
        int errColumn=0;
        readXML=domVariants.setContent(&file,true,&errMsg,&errLine,&errColumn);

        if(readXML==true)
        {
            QDomElement root=domVariants.documentElement();
            parseVariant(root.toElement(),rootItemVariant);
        }
        else
        {
            QMessageBox::warning(0,tr("Внимание"),
                                 tr("Ошибка в структуре XML файла \n = ")+QString(VARIANT_FILE)+"\nError msg="
                                 +errMsg+"\nLine="+errLine+"\nColumn="+errColumn);
        }
    }
#ifdef PRINT_WARNING_LOAD_FILE
    else
    {
        QMessageBox::warning(0,tr("Внимание"),
                             tr("Файл не найден = ")+QString(VARIANT_FILE));
    }
#endif
}
void DomParser::openFileVariantsState(const QString &nameFile)
{
    //! DOM - дерево вариантов состояния
    QDomDocument domVariantsState;

    bool openFile=false;
    QFile file(nameFile);

    //! создаем корень
    rootItemVariantState=new VariantState;

    openFile=file.open(QIODevice::ReadOnly);

    if(openFile==true)
    {
        bool readXML=false;

        QString errMsg="";
        int errLine=0;
        int errColumn=0;

        readXML=domVariantsState.setContent(&file,true);
        if(readXML==true)
        {
            QDomElement root=domVariantsState.documentElement();
            parseVariantState(root.toElement(),rootItemVariantState);
        }
        else
        {
            QMessageBox::warning(0,tr("Внимание"),
                                 tr("Ошибка в структуре XML файла \n = ")+QString(VARIANTSTATE_FILE)+"\nError msg="
                                 +errMsg+"\nLine="+errLine+"\nColumn="+errColumn);
        }
    }
#ifdef PRINT_WARNING_LOAD_FILE
    else
    {
        QMessageBox::warning(0,tr("Внимание"),
                             tr("Файл не найден = ")+QString(VARIANTSTATE_FILE));
    }
#endif
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
//! Соединение двух деревьев: варианты состояния и варинаты программных модулей
void DomParser::joiningVariantsTrees(VariantNode* variantNodes,VariantState *variantState)
{
    QString nameVar;
    QString nameVarState;

    for(int i=0;i<variantState->child.size();i++)
    {
        nameVarState=((Node*)variantState->child[i])->idName;
        if(variantState->child[i]->type()!=Node::VARIANTSTATE)
        {
            for(int j=0;j<variantNodes->child.size();j++)
            {
                nameVar=((VariantNode*)variantNodes->child[j])->idName;
                if(nameVarState==nameVar)
                {
                    //проводим проверку хвостиков(pmodule & sio)
                    bool flag=checkTailVariants(((VariantNode*)variantNodes->child[j]),((VariantState*)variantState->child[i]));
                    if(flag==true)
                    {
                        ((VariantState*)variantState->child[i])->variant=(VariantNode*)variantNodes->child[j];
                        ((VariantNode*)variantNodes->child[j])->variantState.push_back(variantState->child[i]);
                    }
                }
            }
        }else joiningVariantsTrees(variantNodes,(VariantState*)(variantState->child[i]));
    }
}
void DomParser::checkVariansState()
{
    for(int i=0;i<rootItemVariantState->child.size();i++)
    {
        VariantState *tempNode=(VariantState *)(rootItemVariantState->child[i]);
        if(tempNode->child.size()!=0)
        {
            if(((VariantState *)tempNode->child[0])->variant==0 && ((VariantState *)tempNode->child[0])->type()==Node::VARIANTPM)
            {
                ((VariantState *)tempNode->child[0])->deleteVariantState();
            }
        }
    }
}
//! Соединение двух деревьев: данные и варианты.
void DomParser::joiningTrees(GenericNode* dataNodes,VariantNode* variantNodes)
{
    QString nameVar;
    QString nameD;
    for(int i=0;i<variantNodes->child.size();i++)
    {
        if(variantNodes->child[i]->type()!=Node::VARIANTPM)
        {
            nameVar=((Node*)variantNodes->child[i])->idName;

            for(int j=0;j<dataNodes->child.size();j++)
            {
                if(dataNodes->child[j]->type()!=Node::GROUP)
                {
                    nameD=((Node*)dataNodes->child[j])->idName;
                    if(nameD.compare(nameVar)==0)
                    {
                        if((dataNodes->child[j])->type()==Node::SIO)
                        {
                            SIO* sio=(SIO*)dataNodes->child[j];
                            //! Раскручиваем дерево с вариантами обратно
                            VariantNode* tempVariant=variantNodes;
                            do
                            {
                                tempVariant=(VariantNode*)tempVariant->parent;
                            }while(tempVariant->type()!=Node::VARIANTPM);

                            tempVariant->dataNode=sio;
                            sio->variants.push_back(tempVariant);
                        }
                        if((dataNodes->child[j])->type()==Node::PARAM)
                        {
                            Parameter* param=(Parameter*)dataNodes->child[j];

                            ((VariantNode*)variantNodes->child[i])->valueParam=&param->value;
                            ((VariantNode*)variantNodes->child[i])->dataNode=param;

                        }else joiningTrees((GenericNode*)dataNodes->child[j],(VariantNode*)variantNodes->child[i]);
                    }
                }else joiningTrees((GenericNode*)dataNodes->child[j],variantNodes);
            }
        }else
        {
            joiningTrees((GenericNode*)dataNodes,(VariantNode*)variantNodes->child[i]);
        }
    }
}
//! сохранить варианты программных модулей
void DomParser::saveVariant()
{
    //! объект DOM дерева для сохранения вариантов
    QDomDocument saveDomVariants;

    bool fileOpen=false;
    saveDomVariants.clear();
    VariantNode *node=0;
    if(rootItemVariant==0)
        return ;
    if(rootItemVariant->child.isEmpty()==false)
    {
        QDomElement eleParent=saveDomVariants.createElement("data");
        eleParent.setAttribute("module","MPPM");
        eleParent.setAttribute("type","variant");
        for(int i=0;i<rootItemVariant->child.size();i++)
        {
            node= static_cast<VariantNode* > (rootItemVariant->child[i]);

            formStatusExit->setSecondMsg(node->displayName);
            formStatusExit->count_signal();

            QDomElement elementChild=saveDomVariants.createElement("variantPM");

            elementChild.setAttribute("displayName",node->displayName);
            elementChild.setAttribute("idName",node->idName);

            elementChild.setAttribute("comment",node->comment);
            eleParent.appendChild(elementChild);
            node->save(saveDomVariants,elementChild,node);
        }
        saveDomVariants.appendChild(eleParent);
        QFile file("./xml/variants.xml");
        fileOpen=file.open(QIODevice::WriteOnly|QIODevice::Text);
        QTextStream out(&file);
        QDomNode xmlNode=saveDomVariants.createProcessingInstruction("xml","version=\"1.0\" encoding=\"windows-1251\"");
        saveDomVariants.insertBefore(xmlNode,saveDomVariants.firstChild());
        saveDomVariants.save(out,4);
    }
}
//! сохранить варианты состояний
void DomParser::saveStateVariant()
{
    //! объект DOM дерева для сохранения вариантов
    QDomDocument saveDomVariantsState;

    bool fileOpen=false;
    saveDomVariantsState.clear();
    VariantState *node=0;
    if(rootItemVariantState==0)
        return ;
    if(rootItemVariantState->child.isEmpty()==false)
    {
        QDomElement eleParent=saveDomVariantsState.createElement("data");
        eleParent.setAttribute("module","MPPM");
        eleParent.setAttribute("type","variantState");
        for(int i=0;i<rootItemVariantState->child.size();i++)
        {
            node= static_cast<VariantState* > (rootItemVariantState->child[i]);
            formStatusExit->setSecondMsg(node->displayName);
            formStatusExit->count_signal();

            QDomElement elementChild=saveDomVariantsState.createElement("variantState");
            elementChild.setAttribute("displayName",node->displayName);
            elementChild.setAttribute("idName",node->idName);
            elementChild.setAttribute("comment",node->comment);
            eleParent.appendChild(elementChild);
            node->save(saveDomVariantsState,elementChild,node);
        }
        saveDomVariantsState.appendChild(eleParent);
        QFile file("./xml/variantsState.xml");
        fileOpen=file.open(QIODevice::WriteOnly|QIODevice::Text);
        QTextStream out(&file);
        QDomNode xmlNode=saveDomVariantsState.createProcessingInstruction("xml","version=\"1.0\" encoding=\"windows-1251\"");
        saveDomVariantsState.insertBefore(xmlNode,saveDomVariantsState.firstChild());
        saveDomVariantsState.save(out,4);
    }else
    {
        //то удалим файл
        QFile file("./xml/variantsState.xml");
        file.remove();
    }
}
DomParser::~DomParser() {
        // TODO Auto-generated destructor stub
}
