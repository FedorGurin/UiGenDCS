#ifndef LOGSCRIPTEDITOR_H
#define LOGSCRIPTEDITOR_H

#include <QWidget>

namespace Ui {
    class LogScriptEditor;
}

class LogScriptEditor : public QWidget
{
    Q_OBJECT

public:
    explicit LogScriptEditor(QWidget *parent = 0);

    ~LogScriptEditor();
public slots:
    void slotMessageRun(QString,int);
private:
    Ui::LogScriptEditor *ui;
};

#endif // LOGSCRIPTEDITOR_H
