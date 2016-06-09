#ifndef ENGINEDATAUI_H
#define ENGINEDATAUI_H

#include "../CommonEngineData/CommonEngineData.h"
#include "GenericData.h"

class EngineDataUI : public IEngineData
{
    Q_OBJECT
public:
    EngineDataUI(GenericData* data_,QObject *parent=0);

    //! задать данные
    virtual uint setValue(QString idName,QString value, TYPE_REQUEST type=ASYNCH_ENGINE);
    //! выполнение специальной команды
    //virtual uint specialCommand(QStringList str1,QStringList str2,TYPE_REQUEST type=ASYNCH_ENGINE);
    //! получить данные
    virtual uint getValue(QString idName,QString& value,TYPE_REQUEST type=ASYNCH_ENGINE);

    GenericData *data;
signals:
    void refreshCommand();

};

#endif // ENGINEDATAUI_H
