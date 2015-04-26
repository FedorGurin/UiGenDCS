#ifndef SLIDERHFORM_H
#define SLIDERHFORM_H

#include <QWidget>
#include <QSlider>

namespace Ui {
    class SliderHForm;
}

class SliderHForm : public QWidget
{
    Q_OBJECT

public:
    explicit SliderHForm(QWidget *parent = 0);
    ~SliderHForm();

    void setValue(int);
    void setLimitMax(int);
    void setLimitMin(int);
    int value();
    void setMessure(const QString& str)
    {
        messure=str;
    }
     QSlider* slider();
protected:
    void changeEvent(QEvent *e);

private:
    QString messure;
    Ui::SliderHForm *ui;
};

#endif // SLIDERHFORM_H
