
#ifndef DOMPARSER_H_
#define DOMPARSER_H_

#include <QDomElement>
#include <QDomDocument>
#include <QObject>
#include "Node.h"

class DomParser : public QObject
{
public:
    //! дерево с описательной частью данных
    //Node *dataNodes;
    //! Корень для дерева с описанием данных
    Node* rootItemData;

    //! открыть XML файл с описанием данных
    bool openFileDesData(const QString&);

    static DomParser *obj()
    {
        if(parser == 0)
            parser = new DomParser();
        return parser;
    }
    //! деструктор
    virtual ~DomParser();
private:
    DomParser(QObject *parent=0);

    //! разбор XML файла, и формирование дерева с описанием данных
    void parseData(const QDomElement &element, Node *parent);//рекурсивная
    static DomParser *parser;
};

#endif /* DOMPARSER_H_ */
