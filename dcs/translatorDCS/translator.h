#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QObject>
#include <QTimer>
#include <QStringList>
#include <QVector>

#include "../CommonEngineData/CommonEngineData.h"
#include "nodeTrans.h"
#include "translatorThread.h"

class TVaribale
{
public:
    TVariable(QString var_,QString value_)
    {
        var     =   var_;
        value   =   value_;
    }

    void setVar(int index,QString var)
    {

    }
    void setValue(int index,QString val)
    {

    }

    void setVar(int index,QString var,QString val)
    {

    }

    QString var(int index)
    {
        return table[index][0];
    }
    QString value(int index)
    {
        return table[index][1];
    }
    QString findValueByVar(QString var)
    {

    }

    QVector<QStringList> table;
};
class Translator : public QObject
{
    Q_OBJECT
public:
    explicit Translator(QObject *parent = 0);

    //! установить источник теста
    void setSourceCode(QString str)
    {
        qDebug("str.size()=%d\n",str.size());
        test=str;
    }
    //! указатель на обобщенный движок
    CommonEngineData *commonEngineData;

    void executeTest();
    bool analysisLine(QString&,int numLine);
    void startTest();
    void pauseTest();

    //! трансляционные единицы
    INodeTrans *rootNodesTrans;
    INodeTrans *currentNodes;

    void clear();
    void createNodes(int);
    int sizeThreads(){return listThreads.size();}
    /*bool valideThreads(int i)
    {
        if(i>=listThreads.size()) return false;

        return
    }*/

signals:
    //! сигнал того, что обнаружена ошибка в файле под номером строки numLine
    void signalMessage(QString,int);
    void currentLine(int);
public slots:
    //! проверка программы на синтаксические ошибки
    void validate();
    void finiteThread(TranslatorThread*);
private:
    QVector<TranslatorThread* > listThreads;
    //! исходный код
    QString test;

    //Промежуточные данные
    QString vShowMessage;//сообщение с подтверждением
    //! операнды
    QString vValue1;
    QString vValue2;
    //! комментарий
    QString vComment;
    //! специальный тип команд
    QString vSpecialCommand;
    QString vSpecialParam;
    QString vConsoleMessage;
    QString vQuestionMessage;
    //! имя загружаемого варианта
    QString vLoadVariant;
    //! переменная
    QString vVariable;
    //! список переменных
    QVector<TVariable> table;
    //! секунды
    int sec_;
    //! номер подварианта
    int numSubVar_;
};

#endif // TRANSLATOR_H
