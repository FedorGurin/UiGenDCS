#include "editorScript.h"
#include "ui_editorScript.h"
#include <QTextStream>
#include <QMdiSubWindow>

EditorScript::EditorScript(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditorScript)
{
    ui->setupUi(this);
    translator=new Translator;

    mdiArea=new QMdiArea;
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);    
    this->setCentralWidget(mdiArea);

    dialog=new QFileDialog(this,tr("Открыть скрипт"),qApp->applicationDirPath());
    dialog->setFileMode(QFileDialog::AnyFile);
    dialog->setNameFilter(("File TEST Script (*.test)"));
    connect(dialog,SIGNAL(accepted()),this,SLOT(slotAcceptedDialog()));

    void slotPause(bool);
    void slotPlay(bool);

    startButton=new QPushButton;
    startButton->setIcon(QIcon(":/png/play"));
    startButton->setCheckable(true);
    ui->toolBar_2->addWidget(startButton);
    connect(startButton,SIGNAL(toggled(bool)),this,SLOT(slotPlay(bool)));

    pauseButton=new QPushButton;
    pauseButton->setIcon(QIcon(":/png/pause"));
    pauseButton->setCheckable(true);
    ui->toolBar_2->addWidget(pauseButton);
    connect(pauseButton,SIGNAL(toggled(bool)),this,SLOT(slotPause(bool)));

    //QPushButton *pauseButton;

    logScript=new LogScriptEditor;
    ui->toolBar->addWidget(logScript);
    connect(translator,SIGNAL(signalMessage(QString,int)),logScript,SLOT(slotMessageRun(QString,int)));
    connect(translator,SIGNAL(currentLine(int)),this,SLOT(slotCurrentLine(int)));


    connect(ui->actionCreate,   SIGNAL(triggered()),this,SLOT(slotCreate()));
    connect(ui->actionOpen,     SIGNAL(triggered()),this,SLOT(slotOpen()));
    connect(ui->actionSaveAs,   SIGNAL(triggered()),this,SLOT(slotSaveAs()));
    connect(ui->actionSave,     SIGNAL(triggered()),this,SLOT(slotSave()));
    connect(ui->actionClose,    SIGNAL(triggered()),this,SLOT(slotClose()));
    connect(ui->actionRun,      SIGNAL(triggered()),this,SLOT(slotRun()));
    connect(ui->actionTest,     SIGNAL(triggered()),this,SLOT(slotTest()));

}
void EditorScript::slotPlay(bool value)
{
    if(translator->sizeThreads()!=0)
    {
        if(value==true)
        {
            pauseButton->setChecked(false);
            translator->startTest();
        }else
        {
            pauseButton->setChecked(true);
            translator->pauseTest();
        }
    }
    pauseButton->setChecked(false);
    pauseButton->setChecked(false);
}

void EditorScript::slotPause(bool value)
{
    if(translator->sizeThreads()!=0)
    {
        if(value==true)
        {
            startButton->setChecked(false);
            translator->pauseTest();
        }else
        {
            startButton->setChecked(true);
            translator->startTest();
        }
    }
    pauseButton->setChecked(false);
    pauseButton->setChecked(false);
}

EditorScript::~EditorScript()
{
    delete ui;
}

void EditorScript::slotAcceptedDialog()
{
    if(dialog->acceptMode()==QFileDialog::AcceptOpen)
    {
        QStringList list=dialog->selectedFiles();
        QFile file;

        for(int i=0;i<list.size();i++)
        {
            file.setFileName(list[i]);
            file.open(QIODevice::ReadOnly | QIODevice::Text);
            QTextStream out(&file);

            SingleTextEdit *tempEdit=new SingleTextEdit();
            //tempEdit->setRootNode(rootNode);
            tempEdit->setWindowTitle(list[i]);
            edit.push_back(tempEdit);

            do
            {
                QString fileData=out.readLine();
                tempEdit->append(fileData);
            }while(out.atEnd()==false);
            tempEdit->moveCursor(QTextCursor::Start);

            mdiArea->addSubWindow(tempEdit);
            tempEdit->show();
        }
    }else
    {
        QMdiSubWindow* subWindow=mdiArea->currentSubWindow();
        SingleTextEdit* tempText=(SingleTextEdit* )(subWindow->widget());
        QStringList list=dialog->selectedFiles();
        QFile file;
        for(int i=0;i<list.size();i++)
        {
            file.setFileName(list[i]);
            file.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream in(&file);

            in<<tempText->toPlainText();
            in.flush();
            file.flush();
        }
    }
}

void EditorScript::slotCreate()
{
    SingleTextEdit *tempEdit=new SingleTextEdit;
    //tempEdit->setRootNode(rootNode);
    tempEdit->setWindowTitle("Unnamed");

    /*tempEdit->append("main()");
    tempEdit->append("{");
    tempEdit->append("  ");
    tempEdit->append("}");*/

    edit.push_back(tempEdit);

    mdiArea->addSubWindow(tempEdit);
    tempEdit->show();
}
void EditorScript::slotOpen()
{
    dialog->setAcceptMode(QFileDialog::AcceptOpen);
    dialog->show();
}

void EditorScript::slotSave()
{
    QMdiSubWindow* subWindow=mdiArea->currentSubWindow();
    SingleTextEdit* tempText=(SingleTextEdit* )(subWindow->widget());
    QFile file;

    file.setFileName(tempText->windowTitle());
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream in(&file);

    in<<tempText->toPlainText();
    in.flush();
    file.flush();
}

void EditorScript::slotSaveAs()
{
    dialog->setAcceptMode(QFileDialog::AcceptSave);
    dialog->show();
}

void EditorScript::slotClose()
{
    QMdiSubWindow* subWindow=mdiArea->currentSubWindow();
    if(subWindow==0) return;
    SingleTextEdit* tempText=(SingleTextEdit* )(subWindow->widget());
    tempText->close();
    subWindow->close();
    edit.removeAt(edit.indexOf(tempText));
}

void EditorScript::slotExit()
{

}

void EditorScript::slotTest()
{
    QMdiSubWindow* subWindow=mdiArea->currentSubWindow();
    if(subWindow==0) return;
    SingleTextEdit* tempText=(SingleTextEdit* )(subWindow->widget());

    translator->setSourceCode(tempText->toPlainText());
    translator->validate();
}

void EditorScript::slotRun()
{
    QMdiSubWindow* subWindow=mdiArea->currentSubWindow();
    if(subWindow==0) return;

    startButton->setChecked(true);

    translator->executeTest();
}
void EditorScript::slotCurrentLine(int line)
{
    QMdiSubWindow* subWindow=mdiArea->currentSubWindow();
    if(subWindow==0) return;
    SingleTextEdit* tempText=(SingleTextEdit* )(subWindow->widget());
    tempText->selectLine(line);

}

void EditorScript::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
