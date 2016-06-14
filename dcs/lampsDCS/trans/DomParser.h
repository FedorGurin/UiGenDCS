#ifndef DOMPARSER_H_
#define DOMPARSER_H_

#include <QDomElement>
#include <QDomDocument>

#include <QObject>

#include "GenericNode.h"

//XML файл с описанием данных
#define	DATA_FILE "data.xml"

class DomParser : public QObject {

public:
    DomParser(QObject *parent=0);

    //! вернуть указатель на корень
    GenericNode* rootNodeData(){return rootItemData;}

    //! деструктор
    virtual ~DomParser();
private:

    //! Корень для дерева с описанием данных
    GenericNode* rootItemData;

    //! разбор XML файла, и формирование дерева с описанием данных
    void parseData(const QDomElement &element, GenericNode *parent);//рекурсивная

    //! открыть XML файл с описанием данных
    bool openFileDesData(const QString&);
};

#endif /* DOMPARSER_H_ */
