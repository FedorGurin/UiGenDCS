#ifndef PARSERXMLPULT_H
#define PARSERXMLPULT_H
#include <QDomElement>

#include "toggleswitch.h"

//! разбор файла с кнопками
class ParserXMLPult: public QObject
{
public:
    ParserXMLPult(EngineData *engine_);

    //! открыть файл XML с описанием вариантов
    void openXMLFile(const QString &);

    //! Разбор XML файла с вариантами
    void parse(const QDomElement& element);

//    void setEngine(EngineData *engine_)
//    {
//        engine=engine_;
//    }
    QVector<ToggleSwitch* > *retList()
    {
        return &list;
    }
    QStringList names(){return namePages;}
private:
    QVector<ToggleSwitch* > list;
    QStringList namePages;
    EngineData *engine;

};

#endif // PARSERXMLPULT_H
