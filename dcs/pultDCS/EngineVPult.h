#ifndef ENGINEVPULT_H
#define ENGINEVPULT_H
#include "../CommonEngineData/CommonEngineData.h"


class EngineVPult : public IEngineData
{
    Q_OBJECT
public:
    EngineVPult(QObject *parent=0);

    //! задать данные
    virtual TRequestEvent setValue(TCommonRequest request, TYPE_REQUEST type);
    //virtual uint setValue(QString idName,QString value, TYPE_REQUEST type=ASYNCH_ENGINE);
    //! выполнение специальной команды
   // virtual uint specialCommand(QStringList str1,QStringList str2,TYPE_REQUEST type=ASYNCH_ENGINE){return 0;}
    //! получить данные
    //virtual uint getValue(QString idName,QString& value,TYPE_REQUEST type=ASYNCH_ENGINE);


signals:
    void pushStart();
    void releasedStart();
    void pushStop();
    void releasedStop();
    void pushRestart();
    void releasedRestart();

    void pushOn(bool);
    void pushSlideKupr(bool);
    void pushSlideRegime12(bool);
    void pushSlideLockWrite(bool);

    void readStart(QString &value);
    void readStop(QString &value);
    void readRestart(QString &value);

};

#endif // ENGINEVPULT_H
