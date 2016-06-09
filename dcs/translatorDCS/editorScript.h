#ifndef EDITORSCRIPT_H
#define EDITORSCRIPT_H

#include <QMainWindow>
#include <QMdiArea>
#include <QTextEdit>
#include <QFileDialog>
#include <QPushButton>

#include "singletextedit.h"
#include "translator.h"
#include "logScriptEditor.h"

namespace Ui {
    class EditorScript;
}

class EditorScript : public QMainWindow
{
    Q_OBJECT
public:
    explicit EditorScript(QWidget *parent = 0);
    ~EditorScript();

    QMdiArea *mdiArea;
    /*void setRootNode(GenericNode* node)
    {
        rootNode=node;
    }*/
     Translator *translator;

public slots:
    void slotCreate();
    void slotOpen();
    void slotSave();
    void slotSaveAs();
    void slotClose();
    void slotExit();
    void slotTest();
    void slotRun();
    void slotAcceptedDialog();
    void slotCurrentLine(int);
    void slotPause(bool);
    void slotPlay(bool);
protected:
    void changeEvent(QEvent *e);
private:
    //Translator *translator;
    QPushButton *startButton;
    QPushButton *pauseButton;

    QList<SingleTextEdit* > edit;
    QFileDialog *dialog;
    LogScriptEditor *logScript;
    //GenericNode *rootNode;
    Ui::EditorScript *ui;
};

#endif // EDITORSCRIPT_H
