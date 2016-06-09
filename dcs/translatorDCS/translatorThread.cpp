#include "translatorThread.h"
#include <QTimer>
#include "../globalFunc/gl_func.h"

TranslatorThread::TranslatorThread(INodeTrans *root,CommonEngineData *engine_,QObject* parent):QThread(parent)
{
    engine=engine_;
    rootNodesTrans=root;
    currentNode=0;
    isStart=true;

    if(rootNodesTrans!=0)
    {
        if(rootNodesTrans->child.size()!=0)
            currentNode=rootNodesTrans->child[0];
    }
    //! счетчики успешных/неудачных операций
    success=0;
    fault=0;

    infoMsg=new InfoMsg;
    questionMsg=new InfoMsgQuestion;
    sound=new QSound(":/sound/rem");
    sound->setLoops(100);

    connect(questionMsg,SIGNAL(signalAnswer(bool)),this,SLOT(slotQMsg(bool)));
    connect(infoMsg,SIGNAL(signalNextButtton()),this,SLOT(slotMsg()));
    connect(engine,SIGNAL(signalEventsRequest(TRequestEvent)),this,SLOT(slotEventsRequest(TRequestEvent)));
}

void TranslatorThread::runScript()
{   
    qDebug("Run Script\n");
    if(isStart==false) return;

    if(currentNode!=0)
    {
        if(currentNode->type()==INodeTrans::DELAY)
        {
            qDebug("-----delay\n");
            INodeDelay *node=static_cast<INodeDelay* > (currentNode);
            QTimer::singleShot(node->sec*1000,this, SLOT(slotSingleShotTimer()));

            emit signalMessage(tr("Задержка в течении ")+QString::number(node->sec)+tr("сек"),0);
        }else if(currentNode->type()==INodeTrans::EQUAL)
        {
            qDebug("-----Run equal\n");
            INodeEqual *node=static_cast<INodeEqual* > (currentNode);

            emit signalMessage(tr("Присвоение\t")+node->valueLeft_+"="+node->valueRigth_,0);
            uint id;
            //uint id=engine->setValue(node->valueLeft_,node->valueRigth_);
            qDebug("SetValue\n");

            if(id==0)
            {
                emit signalMessage(tr("Присвоение не выполнено. Неизвестный идентификатор"),0);
                qDebug("Equal not \n");
            }
            nextCommand();

        }else if(currentNode->type()==INodeTrans::MESSAGE)
        {
            INodeMessage *node=static_cast<INodeMessage* >(currentNode);
            if(node->typeMessage==1)
            {
                emit signalMessage(node->message,1);
                nextCommand();
            }
            if(node->typeMessage==0)
            {
                emit signalMessage(tr("Погутарить хочу"),0);
                infoMsg->setMsg(node->message);
                sound->play();
                infoMsg->show();

            }
            if(node->typeMessage==2)
            {
                emit signalMessage(tr("Спросить хочу"),0);
                questionMsg->setMsg(node->message);
                questionMsg->show();
            }
        }else if(currentNode->type()==INodeTrans::SPECIAL)
        {
            qDebug("-----Run special\n");
            INodeSpecial *node=static_cast<INodeSpecial* >(currentNode);
            uint id;
            emit signalMessage(tr("Выполнение команды\t")+node->command,0);
            //uint id=engine->specialCommand(QStringList(node->command),QStringList(node->param));

            if(id==0)
            {
                emit signalMessage(tr("Команда не выполнена. Неизвестная команда"),0);
                qDebug("request not correct\n");
            }
            nextCommand();
        }else
        {
            qDebug("nextCommand\n");
            //! обработать следующую команду
            nextCommand();
        }

    }
    qDebug("Exit runScript\n");
}

void TranslatorThread::nextCommand()
{
    //qDebug("nextCommand\n");
    if(currentNode!=0)
    {
        //qDebug("nextCommand1\n");
        currentNode=currentNode->next;
    }
    if(currentNode==0)
    {
        emit signalMessage(tr("Все устал!Скрипт выполнен!"),0);
        if(fault!=0 || success!=0)
        {
            emit signalMessage(tr("_____________________________________________"),1);
            emit signalMessage(tr("Итог:"),1);
            emit signalMessage(tr("Выполнено успешно - ")+QString::number(success)+tr("Nстроки="),1);
            emit signalMessage(tr("Ошибок - ")+QString::number(fault)+tr("Nстроки="),1);
            emit signalMessage(tr("_____________________________________________"),1);
        }

        this->quit();
        emit finite(this);
    }
    if(currentNode!=0)
    {
        emit currentLine(currentNode->line);
        runScript();
    }
}
void TranslatorThread::run()
{
    exec();
}
void TranslatorThread::slotEventsRequest(TRequestEvent eventRequest)
{
    qDebug("Recive events slotEventsRequest()\n");

   /* if(eventRequest.result==true) emit signalMessage(tr("Успешно"),0);
    else emit signalMessage(tr("Ай ай сбой"),0);
    nextCommand();*/
}
void TranslatorThread::slotSingleShotTimer()
{
    emit signalMessage(tr("Продолжаю выполнять"),0);
    nextCommand();
}
void TranslatorThread::timerEvent(QTimerEvent* )
{

}
TranslatorThread::~TranslatorThread()
{
    delete infoMsg;
    delete questionMsg;
}
void TranslatorThread::resumeTest(bool value)
{
    isStart=value;
    if(isStart==true)
        nextCommand();
}
void TranslatorThread::slotMsg()
{
    sound->stop();
    infoMsg->close();

    slotSingleShotTimer();
}
void TranslatorThread::slotQMsg(bool flag)
{
    questionMsg->close();
    if(flag==true)
    {
        emit signalMessage(tr("Выполнено"),1);
        success++;
        qDebug("success+1\n");
    }else
    {
        emit signalMessage(tr("Не выполнено"),1);
        fault++;
        qDebug("fault+1\n");
    }
    slotSingleShotTimer();
}
