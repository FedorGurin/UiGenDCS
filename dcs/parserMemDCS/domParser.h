
#ifndef DOMPARSER_H_
#define DOMPARSER_H_

#include <QDomElement>
#include <QDomDocument>
#include <QObject>


#include "Node.h"

class DomParser : public QObject {

public:
    DomParser(QObject *parent=0);
    //! дерево с описательной частью данных
    Node *dataNodes;
    //! Корень для дерева с описанием данных
    Node* rootItemData;
    //! деструктор
    virtual ~DomParser();
private:
    //! разбор XML файла, и формирование дерева с описанием данных
    void parseData(const QDomElement &element, Node *parent);//рекурсивная

    //! открыть XML файл с описанием данных
    bool openFileDesData(const QString&);

};

#endif /* DOMPARSER_H_ */
