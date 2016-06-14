#ifndef MAINWINDOWLAMPS_H
#define MAINWINDOWLAMPS_H

#include <QMainWindow>

#include "./trans/DomParser.h"
#include "./trans/BinaryPresent.h"

#include "formlamps.h"
namespace Ui {
class MainWindowLamps;
}

//! окно с лампочками
class MainWindowLamps : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowLamps(QWidget *parent = 0);
    ~MainWindowLamps();
    //! ПРОСТО ПРИМЕР ФОРМЫ, ПОТОМ НУЖНО УДАЛИТЬ///////
    FormLamps *exampleLamps;
    ///////////////////////////////////////////////////

    //! по данным из xml создать формы с битами
    void createFormBits();
public slots:
    //! слот свидетельствующий об обновлении данных
    //void slotRefresh(uint uid);
    void slotRefresh(GenericNode *);
private:
    //! чтение и разбор данных из xml файла
    DomParser       *domParser;
    //! объект для приема UDP пакетов
    BinaryPresent   *binaryData;
    //! форма
    Ui::MainWindowLamps *ui;
    //! список созданных форм с битами
    QVector<FormLamps* > formsBits;
};

#endif // MAINWINDOWLAMPS_H
