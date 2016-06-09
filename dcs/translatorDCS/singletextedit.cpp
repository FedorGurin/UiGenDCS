#include "singletextedit.h"


SingleTextEdit::SingleTextEdit(QWidget *parent) :
    QTextEdit(parent)
{    
    completer = new QCompleter(this);
    modelCompleter=new ModelCompleter(completer);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    completer->setModel(modelCompleter);
    completer->popup();
    hightlighter=new  Highlighter(this->document());
}
void SingleTextEdit::selectLine(int line)
{
    qDebug("selected line=%d\n",line);
    int col=80;
    int nCol=1;
    int nLine=1;

    QTextCursor cur=this->textCursor();

    cur.setPosition(line-1);
    cur.select(QTextCursor::LineUnderCursor);
    cur.selectedTableCells(&line,&nLine,&col,&nCol);
    this->setTextCursor(cur);
}
