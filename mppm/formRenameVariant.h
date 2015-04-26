#ifndef FORMRENAMEVARIANT_H
#define FORMRENAMEVARIANT_H

#include <QWidget>
#include "Node.h"


namespace Ui {
    class FormRenameVariant;
}

class FormRenameVariant : public QWidget {
    Q_OBJECT
public:
    FormRenameVariant(QWidget *parent = 0);
    void setVariant(Node* node_);

    ~FormRenameVariant();
public slots:
    void slotPushButton();
signals:
    void acpect(bool);


protected:
    void changeEvent(QEvent *e);

private:
    Node* node;

    Ui::FormRenameVariant *ui;
};

#endif // FORMRENAMEVARIANT_H
