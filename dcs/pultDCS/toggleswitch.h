#ifndef TOGGLESWITCH_H
#define TOGGLESWITCH_H
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

#include "qtsvgtoggleswitch.h"
#include "../xml/Parameter.h"
#include "../xml/enginedata.h"

class ToggleSwitch:public QWidget
{
    Q_OBJECT
public:
    explicit ToggleSwitch(QDomElement *ele,QWidget *parent=0);
    void setToggle();
    //! вернуть узел
    Parameter *curNode(){return node;}
    //! задать номер страницы
    void setPage(int page);
    //! номер страницы
    int page(){return numPage;}
    //! инвертировать или нет
    void setInv(bool inv_);
    //! имя узла для отображения на странице пульта
    QString name()
    {
        if(node!=0) return node->displayName;
        return QString(tr("нет имени"));
    }
    void setNode(Parameter *node_);
    //! группировка
    QVBoxLayout *layoutV;
    void setEngine(EngineData* );
signals:
    void signalSetValue(Parameter*);
public slots:
    //! реакция на переключение
    void slotToggleSwitch(bool);
private:
    //! указатель на параметр
    Parameter* node;
    //! номер страницы на пульте, где будет располагаться переключатель
    int numPage;
    //! признак инвертирования
    bool inv;
    //! движок для выполнения запросов
    EngineData *engine;
    //! объект переключателя
    QtSvgToggleSwitch *toggle;
    //! название
    QLabel *label;
    //! группировка
//    QVBoxLayout *layoutV;
    //! идентификатор
    QString idName;
    //! имя для отображения
    //QString name;
    //! выдавать как бит
    bool valueIsBool;
};

#endif // TOGGLESWITCH_H
