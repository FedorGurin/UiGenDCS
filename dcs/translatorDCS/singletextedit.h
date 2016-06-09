#ifndef SINGLETEXTEDIT_H
#define SINGLETEXTEDIT_H

#include <QTextEdit>
#include <QCompleter>
#include "modelcompleter.h"
#include "highlighter.h"

class SingleTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit SingleTextEdit(QWidget *parent = 0);

    void setRootNode(GenericNode *node)
    {
        modelCompleter->setRootNode(node);
    }
    void selectLine(int);

private:
   ModelCompleter *modelCompleter;
   QCompleter *completer ;
   Highlighter *hightlighter;


signals:

public slots:

};

#endif // SINGLETEXTEDIT_H
