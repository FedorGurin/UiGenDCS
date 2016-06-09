#include "logScriptEditor.h"
#include "ui_logscripteditor.h"
#include <QTime>
LogScriptEditor::LogScriptEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogScriptEditor)
{
    ui->setupUi(this);
}
void LogScriptEditor::slotMessageRun(QString msg,int index)
{

    QString hour=QString::number(QTime::currentTime().hour());
    QString minutes=QString::number(QTime::currentTime().minute());
    QString seconds=QString::number(QTime::currentTime().second());

    if(index==0)  ui->textEditRun->append(hour+":"+minutes+":"+seconds+"\t\t"+msg);
    if(index==1)  ui->textEditConsole->append(hour+":"+minutes+":"+seconds+"\t\t"+msg);
    if(index==2)  ui->textEditError->append(hour+":"+minutes+":"+seconds+"\t\t"+msg);

}

LogScriptEditor::~LogScriptEditor()
{
    delete ui;
}
