#include "mainwindowlamps.h"
#include "ui_mainwindowlamps.h"

MainWindowLamps::MainWindowLamps(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindowLamps)
{
    ui->setupUi(this);
    //! запуск разбора файла с данными
    domParser = new DomParser();
    //! бинарное представление данных
    binaryData= new BinaryPresent(domParser->rootNodeData());

    //! создаем форму по внтуреннему представлению данных
    createFormBits();
    // ловим сигнал о том, что получены данные
    connect(binaryData,SIGNAL(reciveData(GenericNode *)),this,SLOT(slotRefresh(GenericNode *)));
}
//! по данным из xml создать формы с битами, и каждой форме сопоставить параметр и структуру
void MainWindowLamps::createFormBits()
{
    GenericNode* root = domParser->rootNodeData() ;
    for(int i=0;i<root->child.size(); i++)
    {
        if(root->child[i]->type() == GenericNode::STRUCT)
        {
            formsBits.append(new FormLamps((Structure*)root->child[i]));
        }
    }
}
//! слот свидетельствующий об обновлении данных

void MainWindowLamps::slotRefresh(GenericNode *node)
//void MainWindowLamps::slotRefresh(uint uid)
{
    //! по uid определяем какая структура обновилась,
    //! далее ищем соответствующую структуру и для нее вызываем метод refresh
    for(int i=0;i<formsBits.size(); i++)
    {

    }
}
//! деструктор
MainWindowLamps::~MainWindowLamps()
{
    delete ui;
}
