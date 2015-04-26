#ifndef FORMWAIT_H
#define FORMWAIT_H

#include <QWidget>

namespace Ui {
    class FormWait;
}

class FormWait : public QWidget {
    Q_OBJECT
public:
    FormWait(QWidget *parent = 0);
    ~FormWait();

    void setValue(int);
    void setMessage(const QString&);
    void clearMessages();
protected:
    void changeEvent(QEvent *e);
public slots:
    void slot_pushButton();
private:
    Ui::FormWait *m_ui;
};

#endif // FORMWAIT_H
