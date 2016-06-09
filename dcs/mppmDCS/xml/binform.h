#ifndef BINFORM_H
#define BINFORM_H

#include <QWidget>

namespace Ui {
    class BinForm;
}

class BinForm : public QWidget
{
    Q_OBJECT

public:
    explicit BinForm(QWidget *parent = 0);
    ~BinForm();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::BinForm *ui;
};

#endif // BINFORM_H
