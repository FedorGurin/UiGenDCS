#ifndef DIALFORM_H
#define DIALFORM_H

#include <QWidget>
#include <QDial>

namespace Ui {
    class DialForm;
}

class DialForm : public QWidget {
    Q_OBJECT
public:
    DialForm(QWidget *parent = 0);
    ~DialForm();
    void setValue(int);
    void setLimitMax(int);
    void setLimitMin(int);
    int value();

    QDial* dial;
protected:
    void changeEvent(QEvent *e);

private:
    Ui::DialForm *m_ui;
};

#endif // DIALFORM_H
