#include "ItemDelegate.h"
#include "Parameter.h"
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QComboBox>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QCheckBox>

TreeItemDelegate::TreeItemDelegate(int indexColumn_,QObject *parent, int* sizeFont_)
:QItemDelegate(parent)
{
    indexColumn=indexColumn_;
    sizeFont=sizeFont_;
}
bool TreeItemDelegate::eventFilter(QObject *editor, QEvent *event)
{

    return QItemDelegate::eventFilter(editor,event);
}

QWidget* TreeItemDelegate::createEditor(QWidget *parent,
            const QStyleOptionViewItem &option,
            const QModelIndex &index)const
{
    if(index.column()==indexColumn)
    {
        GenericNode *node = static_cast<GenericNode*>(index.internalPointer());

        if(node->type()==Node::PARAM)
        {
            Parameter *nodeParam=static_cast<Parameter* >(node);
            if(nodeParam->typeP==Parameter::DOUBLE || nodeParam->typeP==Parameter::FLOAT)
            {
                if(nodeParam->modeIndication==Parameter::DIAL)
                {
                    return createEditorDial(parent,(GenericNode *)nodeParam);
                }else if(nodeParam->modeIndication==Parameter::SLIDER_H)
                {
                    return createEditorSliderH(parent,(GenericNode *)nodeParam);
                }else if(nodeParam->modeIndication==Parameter::SLIDER_V)
                {
                    return createEditorSliderV(parent,(GenericNode *)nodeParam);
                }else if(nodeParam->modeIndication==Parameter::GRAD_MINUTE_SEC)
                {
                    return createEditorGradMinSec(parent,(GenericNode *)nodeParam);
                }
                else
                {
                    QDoubleSpinBox *doubleSpinBox=new QDoubleSpinBox(parent);

                    doubleSpinBox->setMaximum(nodeParam->predValueMax.toDouble());//максимальное значение
                    doubleSpinBox->setMinimum(nodeParam->predValueMin.toDouble());//минимальное значение
                    doubleSpinBox->setSingleStep(1.0);//шаг изменения числа
                    doubleSpinBox->setDecimals(nodeParam->acc);//4 знака после запятой
                    QFont font=doubleSpinBox->font();
                    font.setPointSize(*sizeFont);
                    doubleSpinBox->setFont(font);

                    connect(doubleSpinBox,SIGNAL(editingFinished()),
                            this,SLOT(commitAndCloseEditorDouble()));
                    return doubleSpinBox;
                }
            }
            else if(nodeParam->typeP==Parameter::INT)
            {
                QLineEdit *line=new QLineEdit(parent);
                if(nodeParam->modeEdit==Parameter::DEC)
                {
                    if(nodeParam->modeIndication==Parameter::DIAL)
                    {
                        return createEditorDial(parent,(GenericNode *)nodeParam);
                    }else if(nodeParam->modeIndication==Parameter::SLIDER_H)
                    {
                        return createEditorSliderH(parent,(GenericNode *)nodeParam);
                    }else if(nodeParam->modeIndication==Parameter::SLIDER_V)
                    {
                        return createEditorSliderV(parent,(GenericNode *)nodeParam);
                    }else if(nodeParam->modeIndication==Parameter::CHECK_BOX)
                    {
                        QCheckBox *checkBox=new QCheckBox(parent);
                        QFont font=checkBox->font();
                        font.setPointSize(*sizeFont);
                        checkBox->setFont(font);
                        checkBox->setText("          ");

                        connect(checkBox,SIGNAL(stateChanged(int)),
                                this,SLOT(commitAndCloseCheckBox()));
                        return checkBox;
                    }else if(nodeParam->testHaveEnumParam()==true)
                    {
                        QComboBox *comboBox=new QComboBox(parent);
                        for(int i=0;i<nodeParam->listEnum.size();i++)
                        {
                            comboBox->addItem(nodeParam->listEnum[i].name);
                        }
                        connect(comboBox,SIGNAL(currentIndexChanged(int)),
                        this,SLOT(commitAndCloseEditorCombo()));
                        return comboBox;
                    }else
                    {
                        QSpinBox *spinBox=new QSpinBox(parent);
                        spinBox->setMaximum(nodeParam->predValueMax.toInt());
                        spinBox->setMinimum(nodeParam->predValueMin.toInt());

                        QFont font=spinBox->font();
                        font.setPointSize(*sizeFont);
                        spinBox->setFont(font);

                        connect(spinBox,SIGNAL(editingFinished()),
                            this,SLOT(commitAndCloseEditor()));
                        return spinBox;
                    }
                }else if(nodeParam->modeEdit==Parameter::BIN)
                {
                    line->setInputMask("BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB");
                    QFont font=line->font();
                    font.setPointSize(*sizeFont);
                    line->setFont(font);
                }else if(nodeParam->modeEdit==Parameter::OCT)
                {
                    //line->setInputMask("");
                }else if(nodeParam->modeEdit==Parameter::HEX)
                {
//                    *rx.setPattern("[0-9]\\d{0,9}");
//                    QRegExpValidator rev(rx,0);
//                    line->setValidator(&rev);

//                    const QRegExp rx("[A-F][0-9]");
//                    QValidator *validator = new QRegExpValidator(rx,0);
//                    line->setValidator(validator);
//                    line->setInputMask("HHHHHHHH");
                }
                connect(line,SIGNAL(editingFinished()),
                        this,SLOT(commitAndCloseEditorLine()));

                connect(line,SIGNAL(returnPressed()),
                        this,SLOT(commitAndCloseEditorLine()));

                return line;
            }
            else if(nodeParam->typeP==Parameter::UINT)
            {
                if(nodeParam->modeIndication==Parameter::DIAL)
                {
                    return createEditorDial(parent,(GenericNode *)nodeParam);
                }else if(nodeParam->modeIndication==Parameter::SLIDER_H)
                {
                    return createEditorSliderH(parent,(GenericNode *)nodeParam);
                }else if(nodeParam->modeIndication==Parameter::SLIDER_V)
                {
                    return createEditorSliderV(parent,(GenericNode *)nodeParam);
                }else if(nodeParam->modeIndication==Parameter::CHECK_BOX)
                {
                    QCheckBox *checkBox=new QCheckBox(parent);
                    QFont font=checkBox->font();
                    font.setPointSize(*sizeFont);
                    checkBox->setFont(font);
                    checkBox->setText("          ");

                    connect(checkBox,SIGNAL(editingFinished()),
                            this,SLOT(commitAndCloseCheckBox()));
                    return checkBox;
                }if(nodeParam->testHaveEnumParam()==true)
                {
                    QComboBox *comboBox=new QComboBox(parent);
                    for(int i=0;i<nodeParam->listEnum.size();i++)
                    {
                        comboBox->addItem(nodeParam->listEnum[i].name);
                    }
                    connect(comboBox,SIGNAL(currentIndexChanged(int)),
                            this,SLOT(commitAndCloseEditorCombo()));
                    return comboBox;
                }else
                {
                    QSpinBox *spinBox=new QSpinBox(parent);
                    spinBox->setMaximum(nodeParam->predValueMax.toUInt());
                    spinBox->setMinimum(nodeParam->predValueMin.toUInt());
                    QFont font=spinBox->font();
                    font.setPointSize(*sizeFont);
                    spinBox->setFont(font);

                    connect(spinBox,SIGNAL(editingFinished()),
                            this,SLOT(commitAndCloseEditor()));
                    return spinBox;
                }
            }
            else if(nodeParam->typeP==Parameter::UCHAR)
            {
                if(nodeParam->modeIndication==Parameter::DIAL)
                {
                    return createEditorDial(parent,(GenericNode *)nodeParam);
                }else if(nodeParam->modeIndication==Parameter::SLIDER_H)
                {
                    return createEditorSliderH(parent,(GenericNode *)nodeParam);
                }
                else if(nodeParam->modeIndication==Parameter::SLIDER_V)
                {
                    return createEditorSliderV(parent,(GenericNode *)nodeParam);
                }if(nodeParam->testHaveEnumParam()==true)
                {
                    QComboBox *comboBox=new QComboBox(parent);
                    for(int i=0;i<nodeParam->listEnum.size();i++)
                    {
                        comboBox->addItem(nodeParam->listEnum[i].name);
                    }
                    connect(comboBox,SIGNAL(currentIndexChanged(int)),
                            this,SLOT(commitAndCloseEditorCombo()));
                    return comboBox;
                }else
                {
                    QSpinBox *spinBox=new QSpinBox(parent);
                    spinBox->setMaximum(255);
                    spinBox->setMinimum(0);
                    QFont font=spinBox->font();
                    font.setPointSize(*sizeFont);
                    spinBox->setFont(font);

                    connect(spinBox,SIGNAL(editingFinished()),
                            this,SLOT(commitAndCloseEditor()));
                    return spinBox;
                }
            }
            else if(nodeParam->typeP==Parameter::MCHAR)
            {
                QLineEdit *lineEdit=new QLineEdit(parent);
                lineEdit->setMaxLength(nodeParam->lengthMCHAR-1);
                QFont font=lineEdit->font();
                font.setPointSize(*sizeFont);
                lineEdit->setFont(font);

                connect(lineEdit,SIGNAL(editingFinished()),
                        this,SLOT(commitAndCloseEditorLine()));

                connect(lineEdit,SIGNAL(returnPressed()),
                        this,SLOT(commitAndCloseEditorLine()));

                return lineEdit;
            }
            else if(nodeParam->typeP==Parameter::BOOL)
            {
                QComboBox *comboBox=new QComboBox(parent);
                comboBox->addItem(tr("True"));
                comboBox->addItem(tr("False"));
                QFont font=comboBox->font();
                font.setPointSize(*sizeFont);
                comboBox->setFont(font);
                connect(comboBox,SIGNAL(currentIndexChanged(int)),
                        this,SLOT(commitAndCloseEditorCombo()));
                return comboBox;
            }else if(nodeParam->typeP==Parameter::BIT)
            {
                Parameter *tempBit=(Parameter*)nodeParam;
                if(tempBit->complexBit==false)
                {
                    QComboBox *comboBox=new QComboBox(parent);
                    comboBox->addItem(tr("True"));
                    comboBox->addItem(tr("False"));
                    QFont font=comboBox->font();
                    font.setPointSize(*sizeFont);
                    comboBox->setFont(font);
                    connect(comboBox,SIGNAL(currentIndexChanged(int)),
                            //connect(comboBox,SIGNAL(editTextChanged(QString)),
                            this,SLOT(commitAndCloseEditorCombo()));
                    return comboBox;
                }else
                {
                    QLineEdit *line=new QLineEdit(parent);
                    if(tempBit->modeEdit==Parameter::DEC)
                    {
                        QSpinBox *spinBox=new QSpinBox(parent);
                        spinBox->setMaximum(tempBit->predValueMax.toInt());
                        spinBox->setMinimum(tempBit->predValueMin.toInt());

                        QFont font=spinBox->font();
                        font.setPointSize(*sizeFont);
                        spinBox->setFont(font);

                        connect(spinBox,SIGNAL(editingFinished()),
                                this,SLOT(commitAndCloseEditor()));
                        return spinBox;
                }else if(tempBit->modeEdit==Parameter::BIN)
                {
                        line->setInputMask("BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB");
                        QFont font=line->font();
                        font.setPointSize(*sizeFont);
                        line->setFont(font);
                    }else if(tempBit->modeEdit==Parameter::OCT)
                    {

                    }else if(tempBit->modeEdit==Parameter::HEX)
                    {
                        /*rx.setPattern("[0-9]\\d{0,9}");
                        QRegExpValidator rev(rx,0);
                        line->setValidator(&rev);*/

                        line->setInputMask("HHHHHHHH");
                        QFont font=line->font();
                        font.setPointSize(*sizeFont);
                        line->setFont(font);
                    }
                    connect(line,SIGNAL(editingFinished()),
                            this,SLOT(commitAndCloseEditorLine()));
                    connect(line,SIGNAL(returnPressed()),
                            this,SLOT(commitAndCloseEditorLine()));
                    return line;
                }
            }
            }
        }/*else if(node->type()==Node::BIT)
        {*/
//            Bit *tempBit=(Bit*)node;
//            if(tempBit->complexBit==false)
//            {
//                QComboBox *comboBox=new QComboBox(parent);
//                comboBox->addItem(tr("True"));
//                comboBox->addItem(tr("False"));
//                QFont font=comboBox->font();
//                font.setPointSize(*sizeFont);
//                comboBox->setFont(font);
//                connect(comboBox,SIGNAL(currentIndexChanged(int)),
//                        //connect(comboBox,SIGNAL(editTextChanged(QString)),
//                        this,SLOT(commitAndCloseEditorCombo()));
//                return comboBox;
//            }else
//            {
//                QLineEdit *line=new QLineEdit(parent);
//                if(tempBit->modeEdit==Bit::DEC)
//                {
//                    QSpinBox *spinBox=new QSpinBox(parent);
//                    spinBox->setMaximum(tempBit->predValueMax);
//                    spinBox->setMinimum(tempBit->predValueMin);

//                    QFont font=spinBox->font();
//                    font.setPointSize(*sizeFont);
//                    spinBox->setFont(font);

//                    connect(spinBox,SIGNAL(editingFinished()),
//                            this,SLOT(commitAndCloseEditor()));
//                    return spinBox;
//            }else if(tempBit->modeEdit==Bit::BIN)
//            {
//                    line->setInputMask("BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB");
//                    QFont font=line->font();
//                    font.setPointSize(*sizeFont);
//                    line->setFont(font);
//                }else if(tempBit->modeEdit==Bit::OCT)
//                {

//                }else if(tempBit->modeEdit==Bit::HEX)
//                {
//                    /*rx.setPattern("[0-9]\\d{0,9}");
//                    QRegExpValidator rev(rx,0);
//                    line->setValidator(&rev);*/

//                    line->setInputMask("HHHHHHHH");
//                    QFont font=line->font();
//                    font.setPointSize(*sizeFont);
//                    line->setFont(font);
//                }
//                connect(line,SIGNAL(editingFinished()),
//                        this,SLOT(commitAndCloseEditorLine()));
//                connect(line,SIGNAL(returnPressed()),
//                        this,SLOT(commitAndCloseEditorLine()));
//                return line;
//            }
//        }
//    }
    return QItemDelegate::createEditor(parent,option,index);
}
QWidget* TreeItemDelegate::createEditorSliderH(QWidget* parent,GenericNode *node)const
{
    Parameter *nodeParam=((Parameter*)node);
    SliderHForm* hslider=new SliderHForm(parent);
    hslider->setWindowFlags(Qt::Tool);
    hslider->setWindowOpacity(0.95);
    hslider->setMessure(nodeParam->messure);

    if(nodeParam->restriction==true)
    {
        hslider->setLimitMin(nodeParam->predValueMin.toInt());
        hslider->setLimitMax(nodeParam->predValueMax.toInt());
    }else
    {
        hslider->setLimitMin(-9999999);
        hslider->setLimitMax(9999999);
    }
    hslider->setFixedSize(QSize(150,310));


    connect(hslider->slider(),SIGNAL(valueChanged(int)),
            this,SLOT(commitAndCloseSliderHEditor()));
    return hslider;
}

QWidget* TreeItemDelegate::createEditorSliderV(QWidget* parent,GenericNode *node) const
{
    Parameter *nodeParam=((Parameter*)node);
    SliderVForm* vslider=new SliderVForm(parent);
    vslider->setWindowFlags(Qt::Tool);
    vslider->setWindowOpacity(0.95);
    vslider->setMessure(nodeParam->messure);

    if(nodeParam->restriction==true)
    {
        vslider->setLimitMin(nodeParam->predValueMin.toInt());
        vslider->setLimitMax(nodeParam->predValueMax.toInt());
    }else
    {
        vslider->setLimitMin(-9999999);
        vslider->setLimitMax(9999999);
    }
    vslider->setFixedSize(QSize(410,150));


    connect(vslider->slider(),SIGNAL(valueChanged(int)),
            this,SLOT(commitAndCloseSliderVEditor()));
    return vslider;
}
QWidget* TreeItemDelegate::createEditorGradMinSec(QWidget* parent,GenericNode *node)const
{
    Q_UNUSED(node);
    QLineEdit *line=new QLineEdit(parent);
    line->setInputMask(tr("000°00'00.000000\""));

    connect(line,SIGNAL(editingFinished()),
    this,SLOT(commitAndCloseEditorLineFiLamda()));
    return line;

}
QWidget* TreeItemDelegate::createEditorDial(QWidget* parent,GenericNode *node) const
{   
    Parameter *nodeParam=static_cast<Parameter* > (node);

    DialForm* dial=new DialForm(parent);
    dial->setWindowFlags(Qt::Tool);
    dial->setWindowOpacity(0.95);
    if(nodeParam->restriction==true)
    {
        dial->setLimitMin(nodeParam->predValueMin.toInt());
        dial->setLimitMax(nodeParam->predValueMax.toInt());
    }else
    {
        dial->setLimitMin(-9999999);
        dial->setLimitMax(9999999);
    }

    dial->setFixedSize(QSize(232,150));

    connect(dial->dial,SIGNAL(valueChanged(int)),
            this,SLOT(commitAndCloseDialEditor()));
    return dial;
}

void TreeItemDelegate::setEditorSliderH(QWidget *editor,const QModelIndex &index,GenericNode *node)const
{
    Parameter *nodeParam=((Parameter*)node);

    int value=index.model()->data(index,Qt::DisplayRole).toInt();
    SliderHForm* slider=qobject_cast<SliderHForm*>(editor);
    slider->setMessure(nodeParam->messure);
    slider->setValue(value);
}
void TreeItemDelegate::setEditorSliderV(QWidget *editor,const QModelIndex &index,GenericNode *node)const
{
    Parameter *nodeParam=((Parameter*)node);

    int value=index.model()->data(index,Qt::DisplayRole).toInt();
    SliderVForm* slider=qobject_cast<SliderVForm*>(editor);
    slider->setMessure(nodeParam->messure);
    slider->setValue(value);
}
void TreeItemDelegate::setEditorDial(QWidget *editor,const QModelIndex &index,GenericNode *node)const
{
    Q_UNUSED(node);
    int value=index.model()->data(index,Qt::DisplayRole).toInt();
    DialForm* dial=qobject_cast<DialForm*>(editor);
    dial->setValue(value);
}
void TreeItemDelegate::setEditorGradMinSec(QWidget *editor,const QModelIndex &index,GenericNode *node)const
{
    Q_UNUSED(node);
    QString value=index.model()->data(index,Qt::DisplayRole).toString();
    QLineEdit *line=qobject_cast<QLineEdit*>(editor);
    line->setInputMask(tr("000°00'00.000000\""));
    line->setText(value);
}
void TreeItemDelegate::commitAndCloseEditorLine()
{
    QLineEdit *editor=qobject_cast<QLineEdit *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}
void TreeItemDelegate::commitAndCloseEditor()
{
    QSpinBox *editor=qobject_cast<QSpinBox *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}
void TreeItemDelegate::commitAndCloseEditorCombo()
{
    QComboBox *editor=qobject_cast<QComboBox *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}
void TreeItemDelegate::commitAndCloseEditorDouble()
{
    QDoubleSpinBox *editor=qobject_cast<QDoubleSpinBox *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}
void TreeItemDelegate::commitAndCloseCheckBox()
{
    QCheckBox *editor=qobject_cast<QCheckBox *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}
void TreeItemDelegate::commitAndCloseEditorLineFiLamda()
{
    QLineEdit *editor=qobject_cast<QLineEdit *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}
void TreeItemDelegate::commitAndCloseDialEditor()
{
    DialForm *editor=qobject_cast<DialForm *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}

void TreeItemDelegate::commitAndCloseSliderHEditor()
{
    SliderHForm *editor=qobject_cast<SliderHForm *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}
void TreeItemDelegate::commitAndCloseSliderVEditor()
{
    SliderVForm *editor=qobject_cast<SliderVForm *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}

void TreeItemDelegate::setEditorData(QWidget *editor,
        const QModelIndex &index)const
{
    if(index.column()==indexColumn)
    {
        GenericNode *node = static_cast<GenericNode*>(index.internalPointer());
        if(node->type()==Node::PARAM)
        {
            Parameter *nodeParam=static_cast<Parameter* > (node);

            if(nodeParam->typeP==Parameter::DOUBLE || nodeParam->typeP==Parameter::FLOAT)
            {
                if(nodeParam->modeIndication==Parameter::DIAL)
                {
                    setEditorDial(editor,index,nodeParam);
                }else if(nodeParam->modeIndication==Parameter::SLIDER_H)
                {
                    setEditorSliderH(editor,index,nodeParam);
                }else if(nodeParam->modeIndication==Parameter::SLIDER_V)
                {
                    setEditorSliderV(editor,index,nodeParam);
                }else if(nodeParam->modeIndication==Parameter::GRAD_MINUTE_SEC)
                {
                    setEditorGradMinSec(editor,index,nodeParam);
                }else
                {
                    double value=index.model()->data(index,Qt::DisplayRole).toDouble();
                    QDoubleSpinBox *doubleSpinBox=qobject_cast<QDoubleSpinBox*>(editor);

                    doubleSpinBox->setMaximum(nodeParam->predValueMax.toDouble());//максимальное значение
                    doubleSpinBox->setMinimum(nodeParam->predValueMin.toDouble());//минимальное значение
                    doubleSpinBox->setSingleStep(1.0);                            //шаг изменения числа
                    doubleSpinBox->setDecimals(nodeParam->acc);                   //указанное кол-во знаков после запятой

                    doubleSpinBox->setValue(value);
                }
            }else if(nodeParam->typeP==Parameter::INT)
            {
                if(nodeParam->modeEdit!=Parameter::DEC)
                {
                    QString value=index.model()->data(index,Qt::DisplayRole).toString();
                    QLineEdit *line=qobject_cast<QLineEdit*>(editor);
                    line->setText(value);
                }else
                {
                    if(nodeParam->modeIndication==Parameter::DIAL)
                    {
                        setEditorDial(editor,index,nodeParam);
                    }else if(nodeParam->modeIndication==Parameter::SLIDER_H)
                    {
                        setEditorSliderH(editor,index,nodeParam);
                    }else if(nodeParam->modeIndication==Parameter::SLIDER_V)
                    {
                        setEditorSliderV(editor,index,nodeParam);
                    }else if(nodeParam->modeIndication==Parameter::CHECK_BOX)
                    {
                        bool bval=false;
                        QString value=index.model()->data(index,Qt::DisplayRole).toString();
                        if(nodeParam->testHaveEnumParam()==true)
                        {
                            bval=nodeParam->valueEnum(value).toInt();
                        }else
                            bval=index.model()->data(index,Qt::DisplayRole).toBool();
                        QCheckBox *checkBox=qobject_cast<QCheckBox*>(editor);
                        checkBox->setChecked(bval);
                    }else if(nodeParam->testHaveEnumParam()==true)
                    {
                        QString value=index.model()->data(index,Qt::DisplayRole).toString();
                        QComboBox *comboBox=qobject_cast<QComboBox*>(editor);
                        comboBox->setCurrentIndex(comboBox->findText(value));
                    }else
                    {
                        int value=index.model()->data(index,Qt::DisplayRole).toInt();
                        QSpinBox *spinBox=qobject_cast<QSpinBox*>(editor);
                        spinBox->setMaximum(nodeParam->predValueMax.toInt());
                        spinBox->setMinimum(nodeParam->predValueMin.toInt());
                        spinBox->setValue(value);
                    }
                }
            }
            else if(nodeParam->typeP==Parameter::UINT)
            {
                if(nodeParam->modeIndication==Parameter::DIAL)
                {
                    setEditorDial(editor,index,nodeParam);
                }else if(nodeParam->modeIndication==Parameter::SLIDER_H)
                {
                    setEditorSliderH(editor,index,nodeParam);
                }else if(nodeParam->modeIndication==Parameter::SLIDER_V)
                {
                    setEditorSliderV(editor,index,nodeParam);
                }else if(nodeParam->modeIndication==Parameter::CHECK_BOX)
                {
                    bool bval=false;
                    QString value=index.model()->data(index,Qt::DisplayRole).toString();
                    if(nodeParam->testHaveEnumParam()==true)
                    {
                        bval=nodeParam->valueEnum(value).toInt();
                    }else
                        bval=index.model()->data(index,Qt::DisplayRole).toBool();
                    QCheckBox *checkBox=qobject_cast<QCheckBox*>(editor);
                    checkBox->setChecked(bval);
                }else if(nodeParam->testHaveEnumParam()==true)
                {
                    QString value=index.model()->data(index,Qt::DisplayRole).toString();
                    QComboBox *comboBox=qobject_cast<QComboBox*>(editor);
                    comboBox->setCurrentIndex(comboBox->findText(value));
                }else
                {
                    int value=index.model()->data(index,Qt::DisplayRole).toUInt();
                    QSpinBox *spinBox=qobject_cast<QSpinBox*>(editor);
                    spinBox->setMaximum(nodeParam->predValueMax.toUInt());
                    spinBox->setMinimum(nodeParam->predValueMin.toUInt());
                    spinBox->setValue(value);
                }
            }
            else if(nodeParam->typeP==Parameter::UCHAR)
            {
                if(nodeParam->modeIndication==Parameter::DIAL)
                {
                    setEditorDial(editor,index,nodeParam);
                }else if(nodeParam->modeIndication==Parameter::SLIDER_H)
                {
                    setEditorSliderH(editor,index,nodeParam);
                }else if(nodeParam->modeIndication==Parameter::SLIDER_V)
                {
                    setEditorSliderV(editor,index,nodeParam);
                }else if(nodeParam->testHaveEnumParam()==true)
                {
                    QString value=index.model()->data(index,Qt::DisplayRole).toString();
                    QComboBox *comboBox=qobject_cast<QComboBox*>(editor);
                    comboBox->setCurrentIndex(comboBox->findText(value));
                }else
                {
                    int value=index.model()->data(index,Qt::DisplayRole).toUInt();
                    QSpinBox *spinBox=qobject_cast<QSpinBox*>(editor);
                    spinBox->setMaximum(255);
                    spinBox->setMinimum(0);
                    spinBox->setValue(value);
                }
            }
            else if(nodeParam->typeP==Parameter::BOOL)
            {
                QString value=index.model()->data(index,Qt::DisplayRole).toString();
                QComboBox *comboBox=qobject_cast<QComboBox*>(editor);
                comboBox->setCurrentIndex(comboBox->findText(value));
            }
            else if(nodeParam->typeP==Parameter::MCHAR)
            {
                QString value=index.model()->data(index,Qt::DisplayRole).toString();
                QLineEdit *lineEdit=qobject_cast<QLineEdit*>(editor);
                lineEdit->setText(value);
            }else if(nodeParam->typeP==Parameter::BIT)
            {
                Parameter *tempBit=(Parameter*)node;
                if(tempBit->complexBit==false)
                {
                    QString value=index.model()->data(index,Qt::DisplayRole).toString();
                    QComboBox *comboBox=qobject_cast<QComboBox*>(editor);
                    comboBox->setCurrentIndex(comboBox->findText(value));
                }else
                {
                    if(tempBit->modeEdit!=Parameter::DEC)
                    {
                        QString value=index.model()->data(index,Qt::DisplayRole).toString();
                        QLineEdit *line=qobject_cast<QLineEdit*>(editor);
                        line->setText(value);
                    }else
                    {
                        int value=index.model()->data(index,Qt::DisplayRole).toInt();
                        QSpinBox *spinBox=qobject_cast<QSpinBox*>(editor);
                        spinBox->setMaximum(tempBit->predValueMax.toInt());
                        spinBox->setMinimum(tempBit->predValueMin.toInt());
                        spinBox->setValue(value);
                    }
                }
            }
        }
    }else QItemDelegate::setEditorData(editor,index);
}
QVariant TreeItemDelegate::setModelGradMinSec(QWidget *editor,GenericNode *node)const
{
    Q_UNUSED(node);
    QLineEdit *line=qobject_cast<QLineEdit*>(editor);
    line->setInputMask(tr("000°00'00.000000\""));
    QString value=line->text();

    return QVariant(value);
}
QVariant TreeItemDelegate::setModelSliderH(QWidget *editor,GenericNode *node)const
{
    Parameter *nodeParam=((Parameter*)node);
    SliderHForm* slider=qobject_cast<SliderHForm*>(editor);
    slider->setMessure(nodeParam->messure);

    if(nodeParam->restriction==true)
    {
        slider->setLimitMin(nodeParam->predValueMin.toInt());
        slider->setLimitMax(nodeParam->predValueMax.toInt());
    }else
    {
        slider->setLimitMin(-9999999);
        slider->setLimitMax(9999999);
    }
    slider->setFixedSize(QSize(150,310));
    int value=slider->value();
    return QVariant(value);
}
QVariant TreeItemDelegate::setModelSliderV(QWidget *editor,GenericNode *node)const
{
    Parameter *nodeParam=((Parameter*)node);
    SliderVForm* slider=qobject_cast<SliderVForm*>(editor);
    slider->setMessure(nodeParam->messure);

    if(nodeParam->restriction==true)
    {
        slider->setLimitMin(nodeParam->predValueMin.toInt());
        slider->setLimitMax(nodeParam->predValueMax.toInt());
    }else
    {
        slider->setLimitMin(-9999999);
        slider->setLimitMax(9999999);
    }
    slider->setFixedSize(QSize(150,310));
    int value=slider->value();
    return QVariant(value);

}
QVariant TreeItemDelegate::setModelDial(QWidget *editor,GenericNode *node)const
{
    Parameter *nodeParam=((Parameter*)node);

    DialForm* dial=qobject_cast<DialForm*>(editor);

    if(nodeParam->restriction==true)
    {
        dial->setLimitMin(nodeParam->predValueMin.toInt());
        dial->setLimitMax(nodeParam->predValueMax.toInt());
    }else
    {
        dial->setLimitMin(-9999999);
        dial->setLimitMax(9999999);
    }

    dial->setFixedSize(QSize(232,150));

    int value=dial->dial->value();
    return QVariant(value);
}

void TreeItemDelegate::setModelData(QWidget *editor,QAbstractItemModel *model,
            const QModelIndex &index) const
{
    if(index.column()==indexColumn)
    {
        GenericNode *node = static_cast<GenericNode*>(index.internalPointer());
        //if(node->isDisplay==true)
        //{
        if(node->type()==Node::PARAM)
        {
            Parameter *nodeParam=static_cast<Parameter* >(node);
            /*if(nodeParam->typeP==Parameter::FLOAT && nodeParam->fiLamda==true)
            {
                QLineEdit *line=qobject_cast<QLineEdit*>(editor);
                line->setInputMask(tr("000°00'00.000000\""));
                QString value=line->text();
                printf("Find filambda\n");
                model->setData(index,value);

            }
            else if(nodeParam->typeP==Parameter::DOUBLE && nodeParam->fiLamda==true)
            {
                QLineEdit *line=qobject_cast<QLineEdit*>(editor);
                line->setInputMask(tr("000°00'00.000000\""));
                QString value=line->text();
                printf("Find filambda\n");
                model->setData(index,value);
            }else*/ if(nodeParam->typeP==Parameter::DOUBLE || nodeParam->typeP==Parameter::FLOAT)
            {
                if(nodeParam->modeIndication==Parameter::DIAL)
                {
                    model->setData(index,setModelDial(editor,nodeParam));
                }else if(nodeParam->modeIndication==Parameter::SLIDER_H)
                {
                    model->setData(index,setModelSliderH(editor,nodeParam));
                }else if(nodeParam->modeIndication==Parameter::SLIDER_V)
                {
                    model->setData(index,setModelSliderV(editor,nodeParam));
                }else if(nodeParam->modeIndication==Parameter::GRAD_MINUTE_SEC)
                {
                    model->setData(index,setModelGradMinSec(editor,nodeParam));
                }else
                {
                    QDoubleSpinBox *doubleSpinBox=qobject_cast<QDoubleSpinBox*>(editor);

                    doubleSpinBox->setMaximum(nodeParam->predValueMax.toDouble());//максимальное значение
                    doubleSpinBox->setMinimum(nodeParam->predValueMin.toDouble());//минимальное значение
                    doubleSpinBox->setSingleStep(1.0);//шаг изменения числа
                    doubleSpinBox->setDecimals(nodeParam->acc);//4 знака после запятой

                    double value=doubleSpinBox->value();
                    model->setData(index,value);
                }
            }
            else if(nodeParam->typeP==Parameter::INT)
            {
                if(nodeParam->modeEdit!=Parameter::DEC)
                {
                    QLineEdit *lineEdit=qobject_cast<QLineEdit*>(editor);
                    QString value=lineEdit->text();
                    model->setData(index,value);
                }else
                {
                    if(nodeParam->modeIndication==Parameter::DIAL)
                    {
                        model->setData(index,setModelDial(editor,nodeParam));
                    }else if(nodeParam->modeIndication==Parameter::SLIDER_H)
                    {
                        model->setData(index,setModelSliderH(editor,nodeParam));
                    }else if(nodeParam->modeIndication==Parameter::SLIDER_V)
                    {
                        model->setData(index,setModelSliderV(editor,nodeParam));
                    }else if(nodeParam->modeIndication==Parameter::CHECK_BOX)
                    {
                        QCheckBox *checkBox=qobject_cast<QCheckBox*>(editor);

                        QString value=QString::number(checkBox->isChecked());
                        //QString strValue=QString::number(value;
                        if(nodeParam->testHaveEnumParam()==true)
                        {
                            value=nodeParam->nameEnum(value);
                        }
                        model->setData(index,value);
                    }else if(nodeParam->testHaveEnumParam()==true)
                    {
                        QComboBox *comboBox=qobject_cast<QComboBox*>(editor);

                        QString value=comboBox->currentText();
                        model->setData(index,value);
                    }else
                    {
                        QSpinBox *spinBox=qobject_cast<QSpinBox*>(editor);

                        spinBox->setMaximum(nodeParam->predValueMax.toInt());
                        spinBox->setMinimum(nodeParam->predValueMin.toInt());

                        int value=spinBox->value();

                        model->setData(index,value);
                    }
                }
            }
            else if(nodeParam->typeP==Parameter::UINT)
            {
                if(nodeParam->modeIndication==Parameter::DIAL)
                {
                    model->setData(index,setModelDial(editor,nodeParam));
                }else if(nodeParam->modeIndication==Parameter::SLIDER_H)
                {
                    model->setData(index,setModelSliderH(editor,nodeParam));
                }else if(nodeParam->modeIndication==Parameter::SLIDER_V)
                {
                    model->setData(index,setModelSliderV(editor,nodeParam));
                }else if(nodeParam->modeIndication==Parameter::CHECK_BOX)
                {
                    QCheckBox *checkBox=qobject_cast<QCheckBox*>(editor);

                    QString value=QString::number(checkBox->isChecked());
                    //QString strValue=QString::number(value;
                    if(nodeParam->testHaveEnumParam()==true)
                    {
                        value=nodeParam->nameEnum(value);
                    }
                    model->setData(index,value);
                }else if(nodeParam->testHaveEnumParam()==true)
                {
                    QComboBox *comboBox=qobject_cast<QComboBox*>(editor);

                    QString value=comboBox->currentText();
                    model->setData(index,value);
                }else
                {
                    QSpinBox *spinBox=qobject_cast<QSpinBox*>(editor);

                    spinBox->setMaximum(nodeParam->predValueMax.toUInt());
                    spinBox->setMinimum(nodeParam->predValueMin.toUInt());

                    int value=spinBox->value();
                    model->setData(index,value);
                }
            }
            else if(nodeParam->typeP==Parameter::BOOL)
            {
                QComboBox *comboBox=qobject_cast<QComboBox*>(editor);

                QString value=comboBox->currentText();
                model->setData(index,value);
            }
            else if(nodeParam->typeP==Parameter::UCHAR)
            {
                if(nodeParam->modeIndication==Parameter::DIAL)
                {
                    model->setData(index,setModelDial(editor,nodeParam));
                }else if(nodeParam->modeIndication==Parameter::SLIDER_H)
                {
                    model->setData(index,setModelSliderH(editor,nodeParam));
                }else if(nodeParam->modeIndication==Parameter::SLIDER_V)
                {
                    model->setData(index,setModelSliderV(editor,nodeParam));
                }else if(nodeParam->testHaveEnumParam()==true)
                {
                    QComboBox *comboBox=qobject_cast<QComboBox*>(editor);

                    QString value=comboBox->currentText();
                    model->setData(index,value);
                }else
                {
                    QSpinBox *spinBox=qobject_cast<QSpinBox*>(editor);

                    spinBox->setMaximum(255);
                    spinBox->setMinimum(0);

                    int value=spinBox->value();
                    model->setData(index,value);
                }
            }
            else if(nodeParam->typeP==Parameter::MCHAR)
            {
                QLineEdit* lineEdit=qobject_cast<QLineEdit*>(editor);

                QString value=lineEdit->text();
                model->setData(index,value);
            }
            else if(nodeParam->typeP==Parameter::BIT)
            {
                Parameter *tempBit=(Parameter*)nodeParam;
                if(tempBit->complexBit==false)
                {
                    QComboBox *comboBox=qobject_cast<QComboBox*>(editor);

                    QString value=comboBox->currentText();
                    model->setData(index,value);
                }else
                {
                    if(tempBit->modeEdit!=Parameter::DEC)
                    {
                        QLineEdit *lineEdit=qobject_cast<QLineEdit*>(editor);
                        QString value=lineEdit->text();
                        model->setData(index,value);
                    }else
                    {
                        QSpinBox *spinBox=qobject_cast<QSpinBox*>(editor);

                        spinBox->setMaximum(tempBit->predValueMax.toInt());
                        spinBox->setMinimum(tempBit->predValueMin.toInt());

                        int value=spinBox->value();

                        model->setData(index,value);
                    }
                }
            }
        }
    }else QItemDelegate::setModelData(editor,model,index);
}
