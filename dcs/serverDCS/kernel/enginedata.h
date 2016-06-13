#ifndef ENGINEDATA_H
#define ENGINEDATA_H

#include "../commonDCS/genericNode.h"
#include "BinaryPresent.h"
#include "../commonDCS/Parameter.h"
#include "../commonDCS/sio.h"
//#include "../CommonEngineData/CommonEngineData.h"

//#include <QTreeWidgetItem>
//#include <QTreeWidget>
#include <QThread>
#include <QWaitCondition>
#include <QMutex>
#include <QTimer>
#include <QQueue>


//! вид запроса к системе доступа данных
class RequestToDataPresent
{
public:
    enum EPrio
    {
        LOW,        /*низкий*/
        HIGH,       /*высокий*/
        MIDDLE      /*средний*/
    };
    enum EType
    {
        GET     = 0,    /*запрос на получение данных*/
        SET     = 1,    /*запрос на запись данных*/
        ADDR    = 2,    /*запрос адреса структуры*/
        COMMAND = 3,    /*запрос на выполнение команды*/
        SET_MODULE=4,   /*запрос на запись всей структуры*/
        GET_MODULE=5    /*запрос на получение всей структуры*/
    };
    //! cформировать запрос из списка узлов
    RequestToDataPresent(QVector<GenericNode *> node_,QVector<int> idNode_,EType type_,uint uid_=0,int frag=0,bool cyc=false)
    {
        node    = node_;
        idNode  = idNode_;
        type    = type_;
        uid     = uid_;
        prio    = HIGH;
        cyclic  = cyc;
        iuid    = qrand();
        fragment= frag;
        tics_wait=0;
        if(cyclic == true)
            prio = LOW;


        for(int i = 0;i<node.size();i++)
        {
            if(node[i]->type() == Node::PARAM)
            {
                Parameter *param=static_cast<Parameter* > (node[i]);
                param->cycle_request = cyclic;
            }
        }
    }
    //! сформировать запрос из одного узла
    RequestToDataPresent(GenericNode * node_,int idNode_,EType type_,uint uid_=0,int frag=0,bool cyc=false)
    {
        node.clear();
        idNode.clear();

        node.push_back(node_);
        idNode.push_back(idNode_);

        type    = type_;
        uid     = uid_;
        prio    = HIGH;
        cyclic  = cyc;
        iuid    = qrand();
        fragment= frag;
        tics_wait=0;

        for(int i = 0;i<node.size();i++)
        {
            if(node[i]->type() == Node::PARAM)
            {
                Parameter *param=static_cast<Parameter* > (node[i]);
                param->cycle_request = cyclic;
            }
        }

    }
    //! сформировать запрос из одного узла
    RequestToDataPresent(QStringList command_,QStringList value_,EType type_,uint uid_=0,int frag=0,bool cyc=false)
    {
        value   = value_;
        type    = type_;
        uid     = uid_;
        prio    = HIGH;
        cyclic  = cyc;
        command = command_;
        iuid    = qrand();
        fragment= frag;
        tics_wait=0;
    }

    //! задать приоритет запроса
    void setPrio(EPrio value)
    {
        prio=value;
    }
    //! убрать циклический признак из всех nodes
    void clearCyclic()
    {
        for(int i = 0;i<node.size();i++)
        {
            if(node[i]->type() == Node::PARAM)
            {
                Parameter *tempParam=static_cast<Parameter* > (node[i]);
                tempParam->cycle_request = false;
            }
        }
    }
    //! приоритет запроса
    EPrio prio;
    //! узлы которые нужно прочитать или записать
    QVector<GenericNode *> node;
    //! идентифиактор узла
    QVector<int> idNode;
    //! некоторый параметр
    //QVariant param;
    //! тип операции (1- записать, 2 -прочитать, 3 - запросить маску)
    EType type;
    //! циклическое выполнение операций
    bool cyclic;
    //! уникальный идентификатор(характеризующий связь с высокоуровневым запросом)
    uint uid;
    //! название команды, код команды
    QStringList command;
    //! операнд команды
    QStringList value;
    //! внтуренний идентификатор(характеризующий данный запрос)
    uint iuid;
    //! время ожидания обработки(в тиках при превышении нужно запрос уничтожить и сообщить всем системам об этом)
    unsigned long tics_wait;
    //! признак фрагментированности
    int fragment;//0- запрос не фрагментрован или общее кол-во фрагментов
};

//! Механизм доступа к произвольным данным представленным в иерархической структуре
class EngineData:public IEngineData
{
    Q_OBJECT
public:
    EngineData(QObject *parent=0);

    //! отправить данные
    virtual TRequestEvent setValue(TCommonRequest request,TYPE_REQUEST type=ASYNCH_ENGINE);
    //! выполнение команды для записи данных
    virtual TRequestEvent command(TCommonRequest request,TYPE_REQUEST type=ASYNCH_ENGINE);
    //! получить данные
    virtual TRequestEvent getValue(TCommonRequest request,TYPE_REQUEST type=ASYNCH_ENGINE);

    bool processingCommand(RequestToDataPresent *request);
    uint setValue(GenericNode* node);
    uint getValue(GenericNode* node);

    //! хешированные данные по элементам
    QHash <QTreeWidgetItem *,GenericNode* > hashTree;

    //! список узлов GenericNode* выбранных пользователем
    QList <GenericNode* >   listSelectedNodes;
    QList <Node* >          listSNodes;

    //! список графических узлов QTreeWidgetItem* выбранных пользователем
    //QList <QTreeWidgetItem* > listSelectedItems;

    //QTreeWidgetItem     *rootTreeWidget;
    //QTreeWidget         *treeWidget;

    //! проверка формата команды
    bool testCommand(QString value);
    //! выбрать все элементы
    void selectAllElements();
    //! снять выбор всех элементов
    void unselectAllElements();     //! пустая функция
    //! сбросить индексы в sio(при потере соединения)
    void unselectIndexSIO();
    //! рекурсия для сброса индекса памяти(при потере соединения)
    void recIndexFlush(GenericNode *node);

    //! добавить в список выбранных элементов
    bool addNode(QTreeWidgetItem *);
    //! удалить из списка выбранный элемент
    bool deleteNode(QTreeWidgetItem *);
    //! объект с операцями записи/чтения данных
    BinaryPresent *binaryPresent;
    //! отобразить дамп памяти
    void showDump(){binaryPresent->showDump();}
    //! спрятать дамп памяти
    void hideDump(){binaryPresent->hideDump();}

    //! задать указать узел с данными
    void setRootData(GenericNode* node);
    //! вернуть указатель на узел с данными
    GenericNode *isRootData();
    //! поиск среди родителей элемент типа SIO(восходящий поиск относительно node)
    GenericNode* recFindParentSIO(GenericNode *node);
    //! поиск среди родителей элемент типа SIO(восходящий поиск относительно node)
    GenericNode* recFindParentPM(GenericNode *node);


    //! поиск узла с указанным идентификационным именем idName
    GenericNode* recFindNodeWithIdName(QString &idName,GenericNode *startNode=0);
    //! поиск узла по указанному пути (т.е набор displayName)
    void generateTree(GenericNode* rootNode ,QTreeWidgetItem* rootItem);
    //рекурсия-запуск нисходящего обхода для пометки узлов
    void recSetChecked(QTreeWidgetItem* item,Qt::CheckState);
    //рекурсия-запуск восходящего обхода для пометки узлов
    void recSetCheckedForParent(QTreeWidgetItem* item,Qt::CheckState checked);
    //!
    void recDownSearchItem(QTreeWidgetItem* item,bool ignoreItem,bool &activateSignal);
    //!
    void recUpSearchItem(QTreeWidgetItem* item,bool &activateSignal);

    //! глобальный поиск первого элемента с displayNamе равным аргументу displayName данной функции
    GenericNode* findNodeOnDisplayName(QString displayName,QString path="");
    //! глобальный поиск первого элемента с idName равным аргументу idName  данной функции
    GenericNode* findNodeOnIdName(QString idName,QString path="");
    //! последовательный поиск узлов с idName`ами указанными в списке list
    GenericNode* findNodeOnIdName(QStringList list);

    //! аналогичны функциям приведенным выше, но отличающиеся возвращаемым типом
    Parameter* findParamOnDisplayName(QString nameItem,QString path="");
    Parameter* findParamOnIdName(QString nameItem,QString path="");
    //! поиск узла с указанным идентификационным именем idName
    GenericNode* recFindNodeWithDisplayName(QString &displayName,GenericNode *startNode=0);

    //! поиск высокоуровненвого запроса(по низкоуровневому запросу)
    TCommonRequest* findCommonRequest(RequestToDataPresent *lowerRequest);
    //! запустить обработку запроса
    void startProcessing();

    //! признак отработки запроса(на это время обработка других запросов запрещается)
    bool processRequest;

    //! обработка событий для текущего потока
    virtual bool event(QEvent *e);

    //! добавить в список
    void addToPriorList(RequestToDataPresent* item);
    //! размер самого большого из списка приоритетов
    int sizePriorList();
    //! обработка статуса результата
    void processingStatus(QQueue<RequestToDataPresent*>& listRequest,bool result,uint uid);
    //! обработка списка запросов
    void processingRequest(RequestToDataPresent* request);
    //! циклическая обработка запросов
    //void processingCyclicStatus(QQueue<RequestToDataPresent*>& listRequest,bool result,uint uid);
    //!
    void set();
public slots:
    //! пустой слот
    void slotCheckCyclicRequest();
    //! слот на изменение элемента
    void slotItemChanged(QTreeWidgetItem * item, int column);
    //! слот на результат обработки
    void slotStatusAnswer(bool resultCode,uint uid);
    //! проверить процесс обработки запросов
    void checkTransmit();
    //! обработка сигнала об обновлении данных
    void slotRefreshData();
private:
    //! список запомненных и требующих обработки запросов
    QList<TCommonRequest> requestMem;
    //! сбор результатов фрагментированных пакетов
    QList<TRequestEvent> fragments;
    //bool transModule;
    //int transList;
    //указатель на все данные
    GenericNode *dataNodes;
    //временная переменная
    QVector<GenericNode* > temp;
    //список запросов с учетом приоритетов
    QQueue<RequestToDataPresent*> listRequestLow;
    QQueue<RequestToDataPresent*> listRequestMiddle;
    QQueue<RequestToDataPresent*> listRequestHigh;
    //список циклических запросов
    //QQueue<RequestToDataPresent*> cyclicRequest;
    //! таймер для обеспечения обработки циклических запросов
    QTimer timer;
    //! номер события для пользовательского события
    int userEvent;
protected:
    //! точка входа в поток
    void run();
signals:
    //! сигнал со списком выбранных элементов
    void selectedItems(QList<GenericNode* > &);
    //! сигнал с элементом по которому пользователь произвел запрос
    void signalFinOperation(QVector<GenericNode *>);
    //! сигнал для модуля UI
    void signalUI();
};

#endif // ENGINEDATA_H
