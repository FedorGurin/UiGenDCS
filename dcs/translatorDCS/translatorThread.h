#ifndef TRANSLATORTHREAD_H
#define TRANSLATORTHREAD_H

#include <QThread>
#include <QWaitCondition>
#include <QMutex>
#include <QSound>

#include "../CommonEngineData/CommonEngineData.h"
#include "nodeTrans.h"
#include "msg/infoMsg.h"
#include "msg/infoMsgQuestion.h"

class TranslatorThread : public QThread
{
    Q_OBJECT
public:
    TranslatorThread(INodeTrans *root,CommonEngineData *engine_,QObject* parent=0);

    void nextCommand();
    void runScript();

    //! указатель на обобщенный движок
    CommonEngineData *engine;
    //! трансляционные единицы
    INodeTrans *rootNodesTrans;
    INodeTrans *currentNode;

    InfoMsg *infoMsg;
    InfoMsgQuestion *questionMsg;
    QSound *sound;

    void resumeTest(bool);

    ~TranslatorThread();
signals:
    void signalMessage(QString,int);
    void currentLine(int);
    //! сигнал о том,ч то поток закончил работу и его можно убрать
    void finite(TranslatorThread*);
protected:
    void timerEvent(QTimerEvent *event);
public slots:
    void slotEventsRequest(TRequestEvent eventRequest);
    void slotSingleShotTimer();
    void slotMsg();
    void slotQMsg(bool flag);
protected:
    virtual void run();
public:
    int success;
    int fault;
    bool isStart;
};

#endif // TRANSLATORTHREAD_H
