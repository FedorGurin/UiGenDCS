

#ifndef XMLMODELVIEW_H
#define XMLMODELVIEW_H

#include <QWidget>

#include "ui_xmlmodelview.h"
#include "formstatusexitprogram.h"
#include "DomParser.h"
#include "ModelData.h"
#include "BinaryPresent.h"
#include "formsetname.h"
#include "formRenameVariant.h"
#include "formsetting.h"
#include "extendedsearhform.h"
#include "enginedata.h"
#include "ListRequest.h"
#include "SettingXML.h"
#include "QCompleter"


class cl_MouseFilter:public QObject
{
    Q_OBJECT
protected:
    virtual bool eventFilter(QObject*,QEvent*);
public:
    cl_MouseFilter(QObject* pobj=0,QWidget *slotForm_=0);
    QWidget *slotForm;
};
class xmlmodelview : public QWidget
{
    Q_OBJECT

public:
    //! конструктор
    xmlmodelview(QWidget *parent = 0);
    //! окно поиска параметров
    ExtendedSearhForm       *exSearchForm;
    //! задать имя
    FormSetName             *formSetName;
    //! переименование варианта
    FormRenameVariant       *renameVariant;
    //! настройки варианта
    FormSetting             *formSetting;
    //! форма выхода из программы
    FormStatusExitProgram   *formStatusExit;
    //! движок обработки запросов
    EngineData              *engineData;
    //! модель
    ModelData               *modelData;
    //! чтение и разбор данных
    DomParser               *domParser;
    //! завершение строки поиска
    QCompleter              *completer;
    //! список запросов необходимых для циклического опроса данных
    ListRequest             *listRequest;
    //! указатель на движок с данными
    CommonEngineData        *commonEngine;
    //! файл с настройками
    SettingXML              *settingsData;
    //! признак того, что данные в модели данных изменились, представлению их нужно обновить
    void resetModeData();

    //! обход дерева для расскрытия списка
    void recTreeForExpanded(GenericNode* node);

    //! блокировка автоматического чтения данных при расскрытии узла
    void blockAutoRead(bool pr);

    //! текущий вариант состояния
    VariantState* currentVariantState;

    //! рабочая переменная для хранения текущего имени варианта
    QString workingNameMenu;

    //! обновить все данные
    void refreshAllData();

    //! показать справку
    void showHelps();

    //! признак того, что данная копия является ведущей
    void setMainProg(bool f)
    {
        mainProg=f;
    }
    //! признак главной программы
    bool mainProg;
    //! блокировка окна для редактирования
    void setEnabledAll(bool f)
    {
        if(removeFormBlock!=true)
            this->setEnabled(f);
    }
    //! получение обобщенного движка
    void setCommonEngine(CommonEngineData *cE)
    {
        commonEngine=cE;
    }

    //! обработка событий
    virtual bool event(QEvent *event);

    //! меню при нажатиии на правую клавишу мыши
    QMenu *menu;
    //! запрет на формирование запросов
    bool requestBlock;
    //! убрать блокировку формы в режиме "Пуск" и "Исходное"
    bool removeFormBlock;
    ~xmlmodelview();
public slots:
    //! обновить список вариантов состояния
    void refreshComboBox();

    //! метод выделяющий заданный элемент структуры
    void selectedGenericNode(GenericNode *node);

    //! реакция на разворачивание пункта    
    void slotForExpanded(const QModelIndex & index);

    //! реакция на выбор Варианта состояния
    void slotComboBox(int);
    //! реакция на нажатие правой кнопки
    void slotSubMenu(QAction*);
    //! задать имя варианта состояния
    void slot_formSetNameStateVariant(QString,QString);
    void slot_formSetName(QString nameVariant,QString comment);
    void slot_formSetName(SIO* sio, QString name,QString comment = "");
    //! реакция на нажатие кнопки "Создать"
    void slotButtonCreate();
    //! расширенный поиск
    void slotExtendedSearchButton();
    //! свернуть все элементы
    void slotPushButtonCollapse();
    //! раскрыть все элементы
    void slotPushButtonExpand();
    //! реакция на обновление данных
    void slotRefreshData(GenericNode *node);
    //! реакция на нажатие кнопки "Сохранить"
    void slot_pushButtonSave();
    //! реакция на нажатие кнопки "Переименовать" вариант состояния
    void slotButtonRename();
    //! реакция на нажатие кнопки "Удалить" вариант состояния
    void slotButtonDelete();
    //! реакция на нажатие левой кнопки мыши, выбор какого -то элемента в TreeView
    void slot_tableView(const QModelIndex &indexCur,const QModelIndex &indexPrev);
    //! реакция на расскрытие элемента
    void slotExpandedItem(const QModelIndex&);
    //! реакция на свора элемента
    void slotCollapsedItem(const QModelIndex&);
    //! обновление расскрытых элементов
    void refreshExpandedItem();
    //! реакция на нажатие правой кнопки мыши на объекте TreeView
    void rightButtonMouseClicked();
    //! реакция на выбор пункта в меню при нажатии правой кнопки
    void slotPressButtonMouse(QAction*);
    //! статус выполнения последнего запроса
    void statusRequest(bool);
    //! сохранение в файл вариантов состояния и вариантов программных модулей
    void slot_SaveVariants();
    //! вызов окна с настрйоками для варианта состояния
    void slot_pushButtonSettings();
    //! реакция на выбор окна с поиском
    void slot_searchButon(void);
    //! блокировка запросов
    void slot_toolButtonRequestBlock(bool);
    //! активация команды "обновить"
    void slotActiveRefreshCommand(GenericNode *node);
    //! увеличение масштаба
    void slotPlusFont();
    //! уменьшение масштаба
    void slotMinusFont();
    //! сброс циклического опроса
    void slotFlushCycParam();
    //! слот на сигнал о восстановлении обмена
    void slotConnectionFind();
    //! слот при потери соединения
    void slotConnectionLost();
private:
    Ui::xmlmodelviewClass ui;
    //! размер шрифта
    int sizeFont;
    //! список узлов для обновления
    QVector<GenericNode* > listNodes;
};

#endif // XMLMODELVIEW_H
