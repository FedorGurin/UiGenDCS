#ifndef FORMLAMPS_H
#define FORMLAMPS_H

#include <QWidget>
#include <QVector>
#include <QLabel>

#include "formlamp.h"

#include "./trans/Structure.h"
namespace Ui {
class FormLamps;
}


class FormLamps : public QWidget
{
    Q_OBJECT

public:
    FormLamps(Structure * str_,QWidget *parent = 0);
    ~FormLamps();


    void create(int size);
    void remove(int index);
    void removeAll();
    void refresh();

private:
    Ui::FormLamps *ui;
    //! указатель на структуру
    Structure *str;
    //! спсиок битов
    QVector<FormLamp* > bits;
};

#endif // FORMLAMPS_H
