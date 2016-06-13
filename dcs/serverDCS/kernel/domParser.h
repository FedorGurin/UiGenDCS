/*
 * DomParser.h
 *
 *  Created on: 27.08.2008
 *      Author: Fedor
 */

#ifndef DOMPARSER_H_
#define DOMPARSER_H_

//#include <QStandardItem>
//#include <QApplication>
#include <QDomElement>
#include <QDomDocument>
//#include <QMessageBox>
#include <QIODevice>
#include <QObject>
#include <QFile>

#include "../commonDCS/GenericNode.h"
#include "../commonDCS/variantNode.h"
#include "../commonDCS/variantState.h"
#include "../globalFunc/math_func.h"

//#include "formstatusexitprogram.h"

//XML файл с описанием данных
//#define	DATA_FILE "data.xml"
//XML файл с вариантами значений
#define VARIANT_FILE "variants.xml"
//XML файл с вариантами состояния
#define VARIANTSTATE_FILE "variantsState.xml"

class DomParser : public QObject {

public:
    DomParser(QObject *parent=0);
    //! DOM - дерево c  описанием данных
    //QDomDocument domDesData;
    //! DOM - дерево вариантов
    //QDomDocument domVariants;
    //! DOM - дерево вариантов состояния
    //QDomDocument domVariantsState;
    //! объект DOM дерева для сохранения вариантов
    //QDomDocument saveDomVariants;
    //QDomDocument saveDomVariantsState;

    //! дерево с описательной частью данных
    GenericNode *dataNodes;
    //! дерево с вариантами значений
    VariantNode *variantsNodes;
    //! дерево с вариантами состояния
    VariantState *variantsStateNodes;

    //! Корень для дерева с описанием данных
    GenericNode* rootItemData;
    //! Корень для дерева с вариантами
    VariantNode* rootItemVariant;
    //! Корень для дерева с вариантами состояний
    VariantState* rootItemVariantState;

    GenericNode* rootNodeData(){return rootItemData;}
    //! форма с статусом загрузки
    //FormStatusExitProgram *formStatusExit;
    //! сохранить варианты в XML файл
    void saveVariant();

    //! кол-во вариантов
    int sizeVariants();

    //! кол-во вариантов состояния
    int sizeVariantsState();

    //! сохранить варианты состояния в XML файл
    void saveStateVariant();

    //! деструктор
    virtual ~DomParser();
private:
    //! разбор XML файла, и формирование дерева с описанием данных
    void parseData(const QDomElement &element, GenericNode *parent);//рекурсивная

    //! открыть файл XML с описанием вариантов
    void openFileVariants(const QString &);

    //! открыть XML файл с описанием данных
    bool openFileDesData(const QString&);

    //! открыть файл XML с вариантами состояний
    void openFileVariantsState(const QString&);

    //! Разбор XML файла с вариантами
    void parseVariant(const QDomElement& element, VariantNode *parent);// рекурсивная

    //! Разбор XML файла с вариантами состояния
    void parseVariantState(const QDomElement& element, VariantState *parent);// рекурсивная

    //! Проврека хвостиков у VariantState и VariantPM(для доуточнения в случае совпадения имен VarinatPM)
    bool checkTailVariants(VariantNode* variantNodes,VariantState *variantState);

    //! Проверка вариантов состояния на согласованность с именами вариантов программных модулей
    void checkVariansState();

    //! Соединение двух деревьев(дерево с данными и с вариантами)
    void joiningTrees(GenericNode*,VariantNode*);// Стыковка двух деревьев

    //! Соединение двух деревьев(дерево с вариантами состояния и с вариантами программных модулей)
    void joiningVariantsTrees(VariantNode* variantNodes,VariantState *variantState);// рекурсивная
};

#endif /* DOMPARSER_H_ */
