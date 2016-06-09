#ifndef COMPLETERCOMMAND_H
#define COMPLETERCOMMAND_H

#include <QObject>
#include <QCompleter>
#include "../xml/GenericNode.h"
class CompleterCommand : public QObject
{
    Q_OBJECT
public:
    explicit CompleterCommand(QObject *parent = 0);
    void setString(QString&);

signals:

private:
    QCompleter *completer;
    GenericNode *rootNode;

public slots:

};

#endif // COMPLETERCOMMAND_H
