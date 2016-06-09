#include "enginedata.h"
#include "Parameter.h"

#include <QCoreApplication>
#include <QTimerEvent>

//! буфер запросов
#define BUFFER_REQUEST 50

EngineData::EngineData(QObject *parent):IEngineData(parent)
{
    setSenderName(tr("MPPM"));
    userEvent=QEvent::User+1000;

    listRequestLow.clear();
    listRequestMiddle.clear();
    listRequestHigh.clear();
    fragments.clear();

    dataNodes=0;
    processRequest=false;

    hashTree.clear();
    binaryPresent=new BinaryPresent(this);

    listSelectedItems.clear();
    listSelectedNodes.clear();
    listSNodes.clear();

    treeWidget=new QTreeWidget;
    treeWidget->setWindowTitle(tr("Укажите область поиска..."));

    connect(treeWidget,
            SIGNAL(itemChanged(QTreeWidgetItem*,int)),
            this,
            SLOT(slotItemChanged(QTreeWidgetItem*,int)));
    treeWidget->setWindowFlags(Qt::Tool);

    connect(binaryPresent,SIGNAL(statusR(bool,uint)),this,SLOT(slotStatusAnswer(bool,uint)));
    connect(binaryPresent,SIGNAL(statusR(bool,uint)),this,SLOT(checkTransmit()));
    //! таймер для активации обработки циклических запросов
    connect(&timer,SIGNAL(timeout()),this,SLOT(slotCheckCyclicRequest()));

    timer.start(2000);
    start(QThread::NormalPriority);
}
//! генерация дерева
void EngineData::generateTree(GenericNode* rootNode ,QTreeWidgetItem* rootItem)
{
    for(int i=0;i<rootNode->child.size();i++)
    {
        QStringList listTemp;
        listTemp<<rootNode->child[i]->displayName;
        QTreeWidgetItem *itemTemp=new QTreeWidgetItem(listTemp);
        itemTemp->setCheckState(0,Qt::Unchecked);

        itemTemp->setToolTip(0,listTemp[0]);
        rootItem->addChild(itemTemp);
        GenericNode* tempNode=(GenericNode*)rootNode->child[i];

        hashTree.insert(itemTemp,tempNode);
        GenericNode *temp=(GenericNode*)rootNode->child[i];
        generateTree(temp,itemTemp);
    }
}
void EngineData::setRootData(GenericNode* node)
{   
    if(node!=0)
    {
        if(dataNodes!=node)
        {
            hashTree.clear();
            treeWidget->clear();

            listSelectedItems.clear();
            listSelectedNodes.clear();
            listSNodes.clear();

            rootTreeWidget=new QTreeWidgetItem(QStringList(tr("Данные")));
            hashTree.insert(rootTreeWidget,node);
            treeWidget->insertTopLevelItem(0,rootTreeWidget);
            treeWidget->setHeaderLabel("");

            dataNodes=node;

            generateTree(dataNodes,rootTreeWidget);
        }

    }
}
GenericNode* EngineData::isRootData()
{
    return dataNodes;
}
GenericNode* EngineData::recFindNodeWithIdName(QString &idName,GenericNode *startNode)
{
    GenericNode *lStartNode=startNode;

    int i=0;
    if(startNode==0)
    {
        if(dataNodes==0) return 0;
        startNode=dataNodes;
        lStartNode=dataNodes;
    }

    if(idName==startNode->idName)
        return startNode;

    for(i=0;i<lStartNode->child.size();i++)
    {
        if(lStartNode->child[i]->idName == idName )
        {
            return (GenericNode*) (lStartNode->child[i]);
        }

    }
    for(i=0;i<lStartNode->child.size();i++)
    {
        GenericNode* tempNode=recFindNodeWithIdName(idName,(GenericNode*)(lStartNode->child[i]));
        if(tempNode!=0)
            return tempNode;
    }
    return 0;
}
GenericNode* EngineData::recFindNodeWithDisplayName(QString &displayName,GenericNode *startNode)
{
    if(startNode == 0)
        startNode=dataNodes;

    if(displayName == startNode->displayName)
        return startNode;

    for(int i=0;i<startNode->child.size();i++)
    {
        GenericNode* tempNode=recFindNodeWithDisplayName(displayName,static_cast<GenericNode* > (startNode->child[i]));
        if(tempNode!=0)
            return tempNode;
    }
    return 0;
}

void EngineData::selectAllElements()
{
    rootTreeWidget->setCheckState(0,Qt::Checked);   
}
void EngineData::unselectAllElements()
{
}

void EngineData::unselectIndexSIO()
{
    recIndexFlush(dataNodes);
}
void EngineData::recIndexFlush(GenericNode *node)
{
    if(node->type()==Node::GROUP || node->type()==Node::PM)
    {
        for(int i=0;i<node->child.size();i++)
        {
            recIndexFlush(static_cast<GenericNode* >(node->child[i]));
        }
    }else
    {
        if(node->type()==Node::SIO)
        {
            SIO *sio=static_cast<SIO* >(node);
            sio->indexInTable=-1;
        }
    }
}
GenericNode* EngineData::recFindParentSIO(GenericNode *node)
{
    if(node == 0)
        return 0;

    if(node->type() == Node::SIO)
        return node;

    if(node->parent == 0)
        return 0;

    if(node->parent->type() == Node::SIO)
        return (static_cast<GenericNode* >(node->parent));

    return  recFindParentSIO(static_cast<GenericNode* >(node->parent));
}
GenericNode* EngineData::recFindParentPM(GenericNode *node)
{
    if(node == 0)
        return 0;
    if(node->parent == 0)
        return 0;
    if(node->parent->type() == Node::PM)
        return static_cast<GenericNode* > (node->parent);
    return   recFindParentPM(static_cast<GenericNode* >(node->parent));
}
//! нисходящий обход для пометки элементов
void EngineData::recSetChecked(QTreeWidgetItem* item,Qt::CheckState checked)
{
    for(int i=0;i<item->childCount();i++)
    {
        QTreeWidgetItem *tempItem=item->child(i);
        tempItem->setCheckState(0,checked);
        recSetChecked(tempItem,checked);
    }
}
Parameter* EngineData::findParamOnDisplayName(QString nameItem,QString path)
{
    GenericNode *tempNode=recFindNodeWithDisplayName(nameItem);
    if(tempNode!=0)
    {
        if(tempNode->type()==Node::PARAM)
        {
             return (static_cast<Parameter* > (tempNode));

        }else return 0;
    }else return 0;
}
Parameter* EngineData::findParamOnIdName(QString nameItem,QString path)
{
    GenericNode *tempNode=recFindNodeWithIdName(nameItem);
    if(tempNode!=0)
    {
        if(tempNode->type()==Node::PARAM)
        {
             return (static_cast<Parameter* > (tempNode));

        }else return 0;
    }else return 0;
}
GenericNode* EngineData::findNodeOnIdName(QStringList list)
{
    GenericNode *result=0;
    for(int i=0; i<list.size();i++)
    {
        result=recFindNodeWithIdName(list[i],result);
    }
    return result;
}
GenericNode* EngineData::findNodeOnIdName(QString nameItem,QString path)
{
    return recFindNodeWithIdName(nameItem);
}
GenericNode* EngineData::findNodeOnDisplayName(QString nameItem,QString path)
{
    return recFindNodeWithDisplayName(nameItem);
}

//! восходящий обход для пометки элементов
void EngineData::recSetCheckedForParent(QTreeWidgetItem* item,Qt::CheckState checked)
{
    //! берем родительский элемент
    QTreeWidgetItem *tempItem=item->parent();
    if(tempItem!=0)
    {
        int checkCount=0;//кол-во помеченных дочерних элементов
        bool haveOneParChecked=false;//признак того, что есть хотя бы один дочерний элемент помеченный как Qt::PartiallyChecked
        for(int i=0;i<tempItem->childCount();i++)
        {
            if(tempItem->child(i)->checkState(0)==Qt::Checked) checkCount++;
            if(tempItem->child(i)->checkState(0)==Qt::PartiallyChecked) haveOneParChecked=true;
        }
        if(tempItem->childCount()==checkCount)//проверяем все ли элементы выбраны
        {
            tempItem->setCheckState(0,Qt::Checked);
        }else if(checkCount!=0 || haveOneParChecked==true)
        {
            tempItem->setCheckState(0,Qt::PartiallyChecked);
            deleteNode(item);
        }else
        {
            tempItem->setCheckState(0,Qt::Unchecked);
            deleteNode(item);
        }
        recSetCheckedForParent(tempItem,checked);//рекурсия
    }
}
//! восходящий обход
void EngineData::slotItemChanged(QTreeWidgetItem* item,int column)
{
    //блокируем события для данного окна
    disconnect(treeWidget,
               SIGNAL(itemChanged(QTreeWidgetItem*,int)),
               this,
               SLOT(slotItemChanged(QTreeWidgetItem*,int)));

    /////////////пометка узлов//////////////////////////////////////////////////////////
    recSetChecked(item,item->checkState(column));//рекурсия-запуск нисходящего обхода для пометки узлов
    recSetCheckedForParent(item,item->checkState(column));//рекурсия-запуск восходящего обхода для пометки узлов
    ////////////////////////////////////////////////////////////////////////////////////
    ////////////Добавление/удаление узлов в/из таблицы//////////////////////////////////
    bool pr1=false,pr2=false;

    recDownSearchItem(item,false,pr1);
    recUpSearchItem(item,pr2);
    /*if(pr1==true || pr2==true)*/ emit selectedItems(listSelectedNodes);
    ////////////////////////////////////////////////////////////////////////////////////
    //разблокируем события для данного окна
    connect(treeWidget,
            SIGNAL(itemChanged(QTreeWidgetItem*,int)),
            this,
            SLOT(slotItemChanged(QTreeWidgetItem*,int)));
}
//! нисходящий обход
void EngineData::recDownSearchItem(QTreeWidgetItem* item,bool IGNORERItem, bool& activateSignal)
{
    bool aS=false;
    QString tempName=item->text(0);
    if(item->checkState(0)==Qt::Checked && IGNORERItem==false)
    {
        aS=addNode(item);
        IGNORERItem=true;
    }
    if(aS==true || activateSignal==true) activateSignal=true;
    for(int i=0;i<item->childCount();i++)
    {
        if(IGNORERItem==true)
        {
            deleteNode(item->child(i));
            QString tempName1=item->child(i)->text(0);
            recDownSearchItem(item->child(i),IGNORERItem,activateSignal);
        }
    }
}
void EngineData::recUpSearchItem(QTreeWidgetItem* item,bool &activateSignal)
{
    bool pr=false;
    //! берем родительский элемент

    QTreeWidgetItem *tempItem=item->parent();

    if(tempItem!=0)
    {
        QString tempName=tempItem->text(0);
        if(tempItem->checkState(0)==Qt::Checked)
        {
            for(int i=0;i<item->childCount();i++)
            {
                pr=deleteNode(tempItem);
                if(pr==true) activateSignal=true;
            }
        }else if(tempItem->checkState(0)==Qt::PartiallyChecked)
        {
            for(int i=0;i<tempItem->childCount();i++)
            {
                if(tempItem->child(i)->checkState(0)==Qt::Checked) addNode(tempItem->child(i));
            }
            deleteNode(tempItem);
            recUpSearchItem(tempItem,activateSignal);
        }
    }
}
bool EngineData::addNode(QTreeWidgetItem *item)
{
    //! проверка того есть ли данный узел в списке
    int res=listSelectedItems.indexOf(item);
     QString tempName=item->text(0);
    if(res==-1)
    {
        GenericNode* tempNode=hashTree.value(item,0);
        if(tempNode!=0)
        {
            listSelectedItems.push_back(item);
            listSelectedNodes.push_back(hashTree.value(item));
            listSNodes.push_back(((Node*)(hashTree.value(item))));

            return true;
        }else
        {
            return false;
        }
    }
    return false;
}

bool EngineData::deleteNode(QTreeWidgetItem *item)
{
    //! проверка того есть ли данный узел в списке
    int res=listSelectedItems.indexOf(item);
    if(res!=-1)
    {
        listSelectedItems.removeAt(res);
        listSelectedNodes.removeOne(hashTree.value(item));
        listSNodes.removeOne(((Node*)hashTree.value(item)));
        return true;
    }
    return false;
}
TRequestEvent EngineData::command(TCommonRequest request,TYPE_REQUEST type)
{
    //! и соответсвующие им идентификаторы
    QStringList commands;
    QStringList values;

    TRequestEvent answer;
    answer.sender=tr("MPPM");
    answer.reciver=request.isSender();
    answer.status=TRequestEvent::IGNORER;

    //! если запрос не предназначается приемнику, то игнорируем
    if(request.isReciver()!=tr("MPPM") || request.size() == 0)
        return answer;

    if(type == IEngineData::ASYNCH_ENGINE)
        answer.status = TRequestEvent::ADDED_TO_QUEUE;
    else
        answer.status = TRequestEvent::PROCESSED;

    for(int i=0;i<request.size();i++)
    {
        QStringList tempList = request.nameAt(i).split(".", QString::SkipEmptyParts);

        //! проверка формата команды
        if(tempList.size() == 0)
        {
            answer.name.append(tr("unknown"));
            answer.value.append(tr("unknown"));
            answer.sub_status.append(TRequestEvent::WRONG_REQUEST);
            answer.sub_uid.append(request.uidAt(i));
        }else
        {
            if(testCommand(request.nameAt(i)) == true)
            {
                commands.append(request.nameAt(i));
                values.append(request.valueAt(i));

                answer.name.append(request.nameAt(i));
                answer.value.append(request.valueAt(i));
                if(type == IEngineData::ASYNCH_ENGINE)
                    answer.sub_status.append(TRequestEvent::ADDED_TO_QUEUE);
                else
                    answer.sub_status.append(TRequestEvent::PROCESSED);

                answer.sub_uid.append(request.uidAt(i));
            }else
            {
                answer.name.append(tr("unknown"));
                answer.value.append(tr("unknown"));
                answer.sub_status.append(TRequestEvent::WRONG_REQUEST);
                answer.sub_uid.append(request.uidAt(i));
            }
        }
    }

    if(type == IEngineData::ASYNCH_ENGINE)
    {
        //! вернуть результат асинхронно
        addToPriorList(new RequestToDataPresent(commands,
                                                values,
                                                RequestToDataPresent::COMMAND,
                                                request.guid()));

    }else if(type == IEngineData::SYNCH_ENGINE)
    {
        processingCommand(new RequestToDataPresent(commands,
                                                   values,
                                                   RequestToDataPresent::COMMAND,
                                                   request.guid()));
    }

    return answer;
}
bool EngineData::testCommand(QString value)
{
    if(value == "RemoveCyclic" || value == "RemoveAllCyclic" || value == "SetDtCyclic")
        return true;
    else
        return false;
}

bool EngineData::processingCommand(RequestToDataPresent *request)
{
    for(int i=0;i<request->command.size();i++)
    {
        QStringList tempList = request->command[i].split(".", QString::SkipEmptyParts);

        //! обноление тех параметров, которые открыты пользователем
        if(tempList[0] == "RefreshOpenedData")
        {

        }
        if(tempList[0] == "RemoveCyclic")//удаление конкрентных циклических данных
        {
            return true;
        }else if(tempList[0] == "RemoveAllCyclic")//удаление всех циклических данных
        {
            for(int i=0;i<listRequestLow.size();i++)
            {
                if(listRequestLow[i]->cyclic == true)
                {
                    listRequestLow[i]->clearCyclic();
                    listRequestLow.removeAt(i);
                }
            }
            return true;
        }else if(tempList[0] == "SetDtCyclic")
        {
            timer.start((request[i].value[0]).toInt());
        }
    }
    return false;
}

TRequestEvent EngineData::setValue(TCommonRequest request,TYPE_REQUEST type)
{
    TRequestEvent answer;

    answer.sender=tr("MPPM");
    answer.reciver=request.isSender();
    answer.status=TRequestEvent::IGNORER;
    answer.uid=request.guid();

    if(request.isReciver() != tr("MPPM") || request.size() == 0)
        return answer;
    //! статус по умолчанию: добавлен в очередь
    answer.status=TRequestEvent::ADDED_TO_QUEUE;

    //! спиcок результата поиска
    QVector<GenericNode *> listParam;listParam.clear();
    //! и соответсвующие им идентификаторы
    QVector<int> listParamID;listParamID.clear();

    //! цикл по подзапросам(записываем сами параметры)
    for(int i = 0;i < request.size();i++)
    {
        //! разобъем команду на элементы
        QStringList tempList = request.nameAt(i).split(".", QString::SkipEmptyParts);

        //! проверка формата команды
        if(tempList.size()<=1)
        {
            answer.name.push_back(tr("unknown"));
            answer.value.push_back(tr("unknown"));
            answer.sub_status.push_back(TRequestEvent::WRONG_REQUEST);
            answer.sub_uid.push_back(request.uidAt(i));
            continue;//запускаем цикл дальше
        }
        //! уберем название модуля из списка
        //tempList.removeFirst();
        //! поиск соответсвующего узла
        GenericNode *findNode=findNodeOnIdName(tempList);
        if(findNode!=0)
        {
            //! сохраняем найденный узел в списке
            listParam.push_back(findNode);
            listParamID.push_back(request.uidAt(i));
            answer.name.push_back(request.nameAt(i));
            answer.sub_status.push_back(TRequestEvent::ADDED_TO_QUEUE);
            answer.sub_uid.push_back(request.uidAt(i));
            if(findNode->type() == Node::PARAM)
            {
                //! значение
                answer.value.push_back(request.valueAt(i));
                //! преобразуем в параметр
                Parameter *param=static_cast<Parameter* >(findNode);
                //! сохраняем значение
                param->setValue(request.valueAt(i));
            }else
                answer.value.append(tr("unknown"));
        }else
        {
             answer.name.push_back(tr("unknown"));
             answer.value.push_back(tr("unknown"));
             answer.sub_status.push_back(TRequestEvent::WRONG_REQUEST);
             answer.sub_uid.push_back(request.uidAt(i));
             continue;
        }
    }
    //! список узлов SIO(нужно для сокращения запросов ADDR)
    QVector<SIO* > listSIO;listSIO.clear();
    //! цикл для определения индексов в таблице(если это нужно)
    if(listParam.size()!=0)
    {
       for(int i = 0; i<listParam.size();i++)
       {
           //! нужно найти sio, что бы выяснить индекс участка памяти
           SIO *sio=static_cast<SIO* > (binaryPresent->recursSIONode(listParam[i]));

           //! добавляем запрос на получение индекса в таблице
           if(sio->indexInTable == -1)
           {
               //! добавляем найденный узел SIO в список
               if(listSIO.contains(sio) == false)
               {
                   listSIO.push_back(sio);

                   addToPriorList(new RequestToDataPresent(listParam[i],listParamID[i],
                                                           RequestToDataPresent::ADDR,
                                                           request.guid()+i+1));
               }
           }
       }
    }
    if(listParam.size()!=0)
    {
        int fragments=((int)(listParam.size()/64));
        for(int i = 0;i<=fragments;i++)
        {
            int len=listParam.size()-64*i;
            if(len>64) len=64;
            QVector<GenericNode *> subList  =listParam.mid(64*i,len);
            QVector<int> subId              =listParamID.mid(64*i,len);
            addToPriorList(new RequestToDataPresent(subList,subId,
                                                    RequestToDataPresent::SET,
                                                    request.guid(),i));

        }
    }
    //! отправка события
    QCoreApplication::postEvent(this,new QEvent(static_cast<QEvent::Type>(userEvent)),Qt::LowEventPriority);
    return answer;
}

uint EngineData::setValue(GenericNode* node)
{
    uint uid=0;
    QVector<GenericNode *> list;
    QVector<int> id;
    list.clear();
    id.clear();
    list.append(node);
    id.append(qrand());
    if(node!=0)
    {
        if(node->type() == Node::GROUP || node->type() == Node::PM)
        {
            for(int i=0;i<node->child.size();i++)
                setValue(static_cast<GenericNode* >(node->child[i]));
        }else
        {
            //! нужно найти sio, что бы выяснить индекс участка памяти
            SIO *sio=static_cast<SIO* > (binaryPresent->recursSIONode(node));

            //! формируем уникальный идентификатор
            uid=qrand();

            //! добавляем запрос на получение индекса в таблице
            if(sio->indexInTable == -1)
                addToPriorList(new RequestToDataPresent(list,id,RequestToDataPresent::ADDR,uid));

            //! добавляем в список новый запрос на запись
            addToPriorList(new RequestToDataPresent(list,id,RequestToDataPresent::SET_MODULE,uid));

            //! отправка события
            QCoreApplication::postEvent(this,new QEvent(static_cast<QEvent::Type>(userEvent)),Qt::LowEventPriority);
        }
    }
    return uid;
}

uint EngineData::getValue(GenericNode* node)
{
    uint uid=0;
    QVector<GenericNode *> list;
    QVector<int> id;
    list.clear();
    id.clear();
    list.append(node);
    id.append(qrand());

    if(node!=0)
    {
        if(node->type() == Node::GROUP || node->type() == Node::PM)
        {
            for(int i=0;i<node->child.size();i++)
            {
                getValue(static_cast<GenericNode* >(node->child[i]));

                /*if(node->child[i]->type()==Node::GROUP || node->child[i]->type()==Node::PM)
                {
                    getValue(static_cast<GenericNode* >(node->child[i]));
                }else
                    getValue(static_cast<GenericNode* >(node->child[i]));*/
            }
        }else
        {
            //! нужно найти sio, что бы выяснить индекс участка памяти
            SIO *sio=static_cast<SIO* > (binaryPresent->recursSIONode(node));

            //! формируем уникальный идентификатор
            uid=qrand();

            //! добавляем запрос на получение индекса в таблице
            if(sio->indexInTable == -1)
                addToPriorList(new RequestToDataPresent(list,id,RequestToDataPresent::ADDR,uid));

            //! добавляем в список новый запрос
            addToPriorList(new RequestToDataPresent(list,id,RequestToDataPresent::GET_MODULE,uid));

            //! отправка события
            QCoreApplication::postEvent(this,new QEvent(static_cast<QEvent::Type>(userEvent)),Qt::LowEventPriority);
        }
    }
    return uid;
}
//! получить данные
TRequestEvent EngineData::getValue(TCommonRequest request,TYPE_REQUEST type)
{
    TRequestEvent answer;

    answer.sender=tr("MPPM");
    answer.reciver=request.isSender();
    answer.status=TRequestEvent::IGNORER;
    answer.uid=request.guid();

    if(request.isReciver() != tr("MPPM"))
        return answer;

    //! статус по умолчанию: добавлен в очередь
    answer.status=TRequestEvent::ADDED_TO_QUEUE;

    //! спиcок результата поиска
    QVector<GenericNode *> listParam;listParam.clear();
    //! и соответсвующие им идентификаторы
    QVector<int> listParamID;listParamID.clear();

    //! цикл по подзапросам(записываем сами параметры)
    for(int i = 0;i < request.size();i++)
    {
        //! разобъем команду на элементы
        QStringList tempList = request.nameAt(i).split(".", QString::SkipEmptyParts);

        //! проверка формата команды
        if(tempList.size()<=1)
        {
            answer.name.push_back(tr("unknown"));
            answer.value.push_back(tr("unknown"));
            answer.sub_status.push_back(TRequestEvent::WRONG_REQUEST);
            answer.sub_uid.push_back(request.uidAt(i));
            continue;//запускаем цикл дальше
        }
        //! уберем название модуля из списка
        //tempList.removeFirst();
        //! поиск соответсвующего узла
        GenericNode *findNode=findNodeOnIdName(tempList);
        if(findNode!=0)
        {
            //! сохраняем найденный узел в списке
            listParam.push_back(findNode);
            listParamID.push_back(request.uidAt(i));
            answer.name.push_back(request.nameAt(i));
            answer.sub_status.push_back(TRequestEvent::ADDED_TO_QUEUE);
            answer.sub_uid.push_back(request.uidAt(i));
            if(findNode->type() == Node::PARAM)
            {
                //! преобразуем в параметр
                Parameter *param=static_cast<Parameter* >(findNode);
                //! значение
                answer.value.push_back(param->value);
            }
        }else
        {
             answer.name.push_back(tr("unknown"));
             answer.value.push_back(tr("unknown"));
             answer.sub_status.push_back(TRequestEvent::WRONG_REQUEST);
             answer.sub_uid.push_back(request.uidAt(i));
             continue;
        }
    }

    if(type == IEngineData::ASYNCH_ENGINE || type == IEngineData::CYCLIC_ENGINE)
    {
        bool cyclic = (type == CYCLIC_ENGINE);
        //! список узлов SIO(нужно для сокращения запросов ADDR)
        QVector<SIO* > listSIO;listSIO.clear();
        //! цикл для определения индексов в таблице(если это нужно)
        if(listParam.size()!=0)
        {
            for(int i = 0; i<listParam.size();i++)
            {
                //! нужно найти sio, что бы выяснить индекс участка памяти
                SIO *sio=static_cast<SIO* > (binaryPresent->recursSIONode(listParam[i]));

                //! добавляем запрос на получение индекса в таблице
                if(sio->indexInTable == -1)
                {
                    //! добавляем найденный узел SIO в список
                    if(listSIO.contains(sio) == false)
                    {
                        listSIO.push_back(sio);
                        addToPriorList(new RequestToDataPresent(listParam[i],listParamID[i],
                                                                RequestToDataPresent::ADDR,
                                                                request.guid()+i+1,0,false));
                    }
                }
            }
        }
        if(listParam.size()!=0)
        {
            int fragments=((int)(listParam.size()/64));
            for(int i = 0;i<=fragments;i++)
            {
                int len=listParam.size()-64*i;
                if(len>64) len=64;
                QVector<GenericNode *> subList  =listParam.mid(64*i,len);
                QVector<int> subId    =listParamID.mid(64*i,len);

                addToPriorList(new RequestToDataPresent(subList,subId,
                                                        RequestToDataPresent::GET,
                                                        request.guid(),fragments,cyclic));
            }
        }
    }
    //! отправка события
    QCoreApplication::postEvent(this,new QEvent(static_cast<QEvent::Type>(userEvent)),Qt::LowEventPriority);
    return answer;
}
//! обработка события
bool EngineData::event(QEvent *e)
{
    if(binaryPresent!=0)
    {
        if(e->type() == userEvent)
        {
            checkTransmit();
        }
    }
    return QThread::event(e);
}
TCommonRequest* EngineData::findCommonRequest(RequestToDataPresent *lowerRequest)
{
    for(int i = 0;i<requestMem.size(); i++)
    {
        if(requestMem[i].guid() == lowerRequest->uid)
            return &requestMem[i];
    }
    return 0;
}
//! процесс обработки запросов типа GET, SET
void EngineData::processingStatus(QQueue<RequestToDataPresent*>& listRequest,/*список обработанных запросов*/
                                  bool result,/*признак результата*/
                                  uint iuid/*локальный идентификатор*/)
{
    //! ответ
    TRequestEvent answer;
    answer.sender = tr("MPPM");
    //QList<RequestToDataPresent* >::iterator iter;

    //! цикл по всем ранее созданным низкоуровневым запросам
    for (int i=0; i<listRequest.size();i++)
    {
        RequestToDataPresent* request =listRequest[i];
        if(request->iuid == iuid)
        {
            //! удаляем запрос из списка
            //listRequest.removeOne(request);
            RequestToDataPresent* findReq=listRequest[i];
            if(findReq->fragment == 0)
            {
                //! то тогда формируем результат немедленно
                answer.uid=findReq->uid;//! идентификатор глобального индекса(связь через идентифкаторы запросов TCommonRequest и RequestToDataPresent)
                if(result == true)
                    answer.status=TRequestEvent::PROCESSED;
                else
                    answer.status=TRequestEvent::PROCESSED_FAULT;

                for(int j = 0; j<findReq->node.size();j++)
                {
                    if(findReq->node[j]->type() == Node::PARAM && findReq->type == RequestToDataPresent::GET)
                    {
                        Parameter *param=static_cast<Parameter* >(findReq->node[j]);
                        answer.value.append(param->value);
                    }
                    answer.sub_uid.append(findReq->idNode[j]);
                    if(result == true)
                        answer.sub_status.append(TRequestEvent::PROCESSED);
                    else
                        answer.sub_status.append(TRequestEvent::PROCESSED_FAULT);
                }
                //! обработка завершена
                processRequest=false;
                //! выдача сигналов о результате
                emit signalEventsRequest(answer);
                //! оповещение UI
                emit signalUI();
            }else //если запрос фрагментирован
            {
                TRequestEvent answerFrag;
                //! признак того, что надйен фрагмент
                bool prFindFrag=false;
                //! фрагменты
                for(int i = 0;i<fragments.size();i++)
                {
                    if(fragments[i].uid == findReq->uid) //fragments хранит список объектов для каждого uid запроса TCommonRequest)
                    {
                        prFindFrag=true;

                        for(int j = 0; j<findReq->node.size();j++)
                        {
                            if(findReq->node[j]->type() == Node::PARAM )
                            {
                                Parameter *param=static_cast<Parameter* >(findReq->node[j]);
                                fragments[i].value.append(param->value);
                            }
                            fragments[i].sub_uid.append(findReq->idNode[j]);
                        }

                        //! формирование статуса
                        TRequestEvent::TYPE_STATUS getStatus=TRequestEvent::PROCESSED;
                        if(result == false)
                            getStatus=TRequestEvent::PROCESSED_FAULT;
                        answerFrag.sub_status.push_back(getStatus);
                        if(result == false)
                            answerFrag.status=TRequestEvent::PROCESSED_FAULT;

                        if(fragments[i].sub_uid.size() == findReq->fragment) //фрагменты все собраны
                        {
                            //! обработка завершена
                            processRequest=false;

                            //! скидываем все пакеты в
                            for(int j=0;j<fragments[i].sub_uid.size();i++)
                            {
                                answer.sub_uid.append(fragments[i].sub_uid[j]);
                                answer.sub_status.append(fragments[i].sub_status[j]);
                            }
                            fragments.removeAt(i);
                            //! выдача сигналов о результате
                            emit signalEventsRequest(answer);
                            //! оповещение UI
                            emit signalUI();
                        }
                    }
                }
                if(prFindFrag == false)//то добавляем новый фрагмент
                {

                    for(int j = 0; j<findReq->node.size();j++)
                    {
                        if(findReq->node[j]->type() == Node::PARAM && findReq->type == RequestToDataPresent::GET)
                        {
                            Parameter *param=static_cast<Parameter* >(findReq->node[j]);
                            answerFrag.value.push_back(param->value);
                        }
                        answerFrag.sub_uid.push_back(findReq->idNode[j]);
                    }
                    //! формирование статуса
                    TRequestEvent::TYPE_STATUS getStatus=TRequestEvent::PROCESSED;
                    if(result == false)
                        getStatus = TRequestEvent::PROCESSED_FAULT;
                    answerFrag.sub_status.push_back(getStatus);

                    //! общие признаки
                    answerFrag.uid = findReq->uid;
                    answerFrag.status=TRequestEvent::PROCESSED;
                    if(result == false)
                        answerFrag.status=TRequestEvent::PROCESSED_FAULT;
                    //! добавление фрагмента
                    fragments.append(answerFrag);
                }
            }
            //! удаляем запрос из списка
            if(findReq->cyclic == false)
                listRequest.removeOne(findReq);
        }
    }
}
void EngineData::slotRefreshData()
{

}
//! результат обработки завпроса(обратная связь)
void EngineData::slotStatusAnswer(bool result/*результат обработки*/,uint iuid/*идентификатор*/)
{
    if(listRequestHigh.size()!=0)
        processingStatus(listRequestHigh,result,iuid);
    else if(listRequestMiddle.size()!=0)
        processingStatus(listRequestMiddle,result,iuid);
    else if(listRequestLow.size()!=0)
        processingStatus(listRequestLow,result,iuid);
}
//! обработка списка запросов
void EngineData::processingRequest(RequestToDataPresent* request)
{
    //! определяем тип запроса
    if(request->type == RequestToDataPresent::SET)
    {
        binaryPresent->setData(&(request->node),request->iuid);
    }else if(request->type == RequestToDataPresent::SET_MODULE)
    {
        binaryPresent->setData(request->node[0],request->iuid);
    }
    else if(request->type == RequestToDataPresent::GET_MODULE)
    {
        binaryPresent->getData(request->node[0],request->iuid);
    }else if(request->type == RequestToDataPresent::GET)
    {
        binaryPresent->getData(&(request->node),request->iuid);
    }
    else if(request->type == RequestToDataPresent::ADDR)
    {
        binaryPresent->getMemIndex(request->node[0],request->iuid);
    }
    else if(request->type == RequestToDataPresent::COMMAND)
    {
        //! обрабатываем запрос команда
        processingCommand(request);
        //! проверка выполнения других запросов
        checkTransmit();
    }
}
//! обработка запросов
void EngineData::startProcessing()
{   
    RequestToDataPresent* tempRequest=0;
    processRequest = true;
    if(listRequestHigh.size()!=0)
    {
        tempRequest=listRequestHigh.first();
        if(tempRequest->cyclic == false)
            processingRequest(tempRequest);
    }else if(listRequestMiddle.size()!=0)
    {
        tempRequest=listRequestMiddle.first();
        if(tempRequest->cyclic == false)
            processingRequest(tempRequest);
    }else if(listRequestLow.size()!=0)
    {
        tempRequest=listRequestLow.first();
        if(tempRequest->cyclic == false)
            processingRequest(tempRequest);
    }
    processRequest = false;
}
//! проверка передачи
void EngineData::checkTransmit()
{
    if(binaryPresent->transferUDP->processRequest == false)//если процесс обработки завершен
    {
        startProcessing();
    }
}
void EngineData::addToPriorList(RequestToDataPresent* item)
{
    if(item->prio==RequestToDataPresent::LOW && (listRequestLow.size()<BUFFER_REQUEST))
        listRequestLow.enqueue(item);
    else if(item->prio == RequestToDataPresent::MIDDLE && (listRequestMiddle.size()<BUFFER_REQUEST))
        listRequestMiddle.enqueue(item);
    else if(item->prio == RequestToDataPresent::HIGH && (listRequestHigh.size()<BUFFER_REQUEST))
        listRequestHigh.enqueue(item);
}
//! обработка циклических запросов
void EngineData::slotCheckCyclicRequest()
{
    int i=0;
    for(i = 0;i<listRequestLow.size();i++)
    {
        //qDebug()<<"sending request";
        if(listRequestLow[i]->cyclic == true)
        {
            processingRequest(listRequestLow[i]);
        }
    }
}
void EngineData::run()
{
    exec();
}
