#ifndef INFOMSG_H
#define INFOMSG_H

#include <QWidget>

namespace Ui {
    class InfoMsg;
}

class InfoMsg : public QWidget
{
    Q_OBJECT

public:
    explicit InfoMsg(QWidget *parent = 0);
    void setMsg(QString);
    ~InfoMsg();
signals:
    void signalNextButtton();
private:
    Ui::InfoMsg *ui;
};

#endif // INFOMSG_H
