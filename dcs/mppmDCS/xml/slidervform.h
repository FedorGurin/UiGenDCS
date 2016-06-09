#ifndef SLIDERVFORM_H
#define SLIDERVFORM_H

#include <QWidget>
#include <QSlider>

namespace Ui {
    class SliderVForm;
}

class SliderVForm : public QWidget
{
    Q_OBJECT

public:
    explicit SliderVForm(QWidget *parent = 0);
    ~SliderVForm();

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
    Ui::SliderVForm *ui;
    QString messure;
};

#endif // SLIDERVFORM_H
