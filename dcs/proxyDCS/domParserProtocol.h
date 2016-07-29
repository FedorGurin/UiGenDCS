#ifndef DOMPARSER_PROTOCOL_H_
#define DOMPARSER_PROTOCOL_H_

#include <QDomElement>
#include <QDomDocument>
#include <QObject>

#include "nodeProtocol.h"


//XML файл с описанием данных
#define DATA_FILE "protocol.xml"

class DomParser : public QObject {

public:
    DomParser(QObject *parent=0);

    //! дерево с описательной частью данных
    NodeProtocol *dataNodes;

    //! Корень для дерева с описанием данных
    NodeProtocol* rootItemData;

    //NodeProtocol* rootNodeData(){return rootItemData;}

    //! форма с статусом загрузки
    //FormStatusExitProgram *formStatusExit;

    //! деструктор
    virtual ~DomParser();
private:
    //! разбор XML файла, и формирование дерева с описанием данных
    void parseData(const QDomElement &element, NodeProtocol *parent);//рекурсивная

    //! открыть XML файл с описанием данных
    bool openFileDesData(const QString&);

};

#endif /* DOMPARSER_H_ */
