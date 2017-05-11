#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "../../proxyDCS/proxyDCS.h"
namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
ProxyDCS *proxyDCS;
public slots:
void send(bool value);
private:
    Ui::Form *ui;
};

#endif // FORM_H
