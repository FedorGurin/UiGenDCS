#ifndef FORMLAMP_H
#define FORMLAMP_H

#include <QWidget>
#include <QPixmap>
#include "trans/Parameter.h"
namespace Ui {
class FormLamp;
}

class FormLamp : public QWidget
{
    Q_OBJECT

public:
    explicit FormLamp(Parameter *param, QWidget *parent = 0);
    ~FormLamp();
    void switchOn();
    void switchOff();
    void refresh();
private:
    Ui::FormLamp *ui;
    //! иконки для лампочек
    QPixmap pixmapRed;
    QPixmap pixmapGreen;
    //! указатель на параметр со значением
    Parameter *param;
};

#endif // FORMLAMP_H
