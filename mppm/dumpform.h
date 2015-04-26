#ifndef DUMPFORM_H
#define DUMPFORM_H

#include <QWidget>

namespace Ui {
class DumpForm;
}

class DumpForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit DumpForm(QWidget *parent = 0);
    ~DumpForm();
    void addValue(int addr,QString value, int cells);
    void clear();
    
private:
    Ui::DumpForm *ui;
    int gray_green;//0-gray
};

#endif // DUMPFORM_H
