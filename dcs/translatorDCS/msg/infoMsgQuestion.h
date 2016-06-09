#ifndef INFOMSGQUESTION_H
#define INFOMSGQUESTION_H

#include <QWidget>

namespace Ui {
    class InfoMsgQuestion;
}

class InfoMsgQuestion : public QWidget
{
    Q_OBJECT

public:
    explicit InfoMsgQuestion(QWidget *parent = 0);
    ~InfoMsgQuestion();
    void setMsg(QString str);
signals:
    void signalAnswer(bool answer);
public slots:
    void slotButtonYes();
    void slotButtonNo();
private:
    Ui::InfoMsgQuestion *ui;
};

#endif // INFOMSGQUESTION_H
