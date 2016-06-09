#include "translator.h"
#include "translatorThread.h"

#include <string>
/////BOOST
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <cstdlib>


//using boost::spirit::qi::standard_wide;
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;

using boost::spirit::utf8_string;
using boost::spirit::qi::double_;
using boost::spirit::qi::_1;
using boost::spirit::qi::phrase_parse;

//using boost::spirit::ascii::space;
using boost::phoenix::ref;

//class Translator::rootNodesTrans=0;

Translator::Translator(QObject *parent) :
    QObject(parent)
{
    test.clear();
    listThreads.clear();
    rootNodesTrans=new INodeTrans;
    currentNodes=rootNodesTrans;
}
void Translator::executeTest()
{
    qDebug("run executeTest()\n");
    qDebug("Size=%d\n",rootNodesTrans->child.size());
    TranslatorThread *thread=new TranslatorThread(rootNodesTrans,commonEngineData);
    listThreads.push_back(thread);
    connect(thread,SIGNAL(signalMessage(QString,int)),this,SIGNAL(signalMessage(QString,int)));
    connect(thread,SIGNAL(currentLine(int)),this,SIGNAL(currentLine(int)));
    connect(thread,SIGNAL(finite(TranslatorThread*)),this,SLOT(finiteThread(TranslatorThread*)));

    emit signalMessage(tr("Запуск теста"),0);

    thread->start();
    thread->runScript();
}
void Translator::finiteThread(TranslatorThread *finThread)
{
    listThreads.remove(listThreads.indexOf(finThread));
    delete finThread;
}

void Translator::startTest()
{
    for(int i=0;i<listThreads.size();i++)
    {
        listThreads[i]->resumeTest(true);
    }
}

void Translator::pauseTest()
{
    for(int i=0;i<listThreads.size();i++)
    {
        listThreads[i]->resumeTest(false);
    }
}

void Translator::validate()
{
    qDebug("Validate\n");
    if(test.length()==0) return;

    //! разобъем весь код на подстроки
    //QStringList lines = test.split("\n", QString::KeepEmptyParts);
    QStringList lines = test.split("\n",QString::KeepEmptyParts);

    int sum=0;
    rootNodesTrans->child.clear();
    for(int i=0;i<lines.size();i++)
    {
        qDebug("analysisLine()\n");
        sum=lines[i].length()+sum+1;
        QString tempLine=lines[i];//.remove(QChar(' '));
        if(tempLine.length()!=0)
        {
            if(analysisLine(tempLine,sum)==true)//формирование дерева с узлами
            {
                qDebug("Good line\n");
            }
            else
            {
                emit signalMessage(tr("Ошибка в строке line=")+QString::number(i)+1,2);
            }
        }
    }
}


bool Translator::analysisLine(QString& line,int numLine)
{
    using qi::double_;
    using boost::spirit::standard_wide::char_;
    using boost::spirit::standard_wide::space;
    using boost::spirit::standard_wide::string;

    using qi::int_;
    using qi::phrase_parse;
    using qi::lit;
    using qi::double_;
    using qi::_1;
    using qi::lexeme;


    using phoenix::push_back;
    using phoenix::ref;

    //! обнуление всех параметров
    clear();

    //! очистка внутренних структур
    std::wstring tempString=line.toStdWString();

    //quoted_string %= lexeme['"' >> +(char_ - '"') >> '"'];


//    bool r = phrase_parse(tempString.begin(),tempString.end(),
//    //  Begin grammar
//    (
//        lit("delay")>>'('>>int_[ref(sec_)=_1]>>')'>>';' |
//        lit("iMsg")>>'('>>*(char_[push_back(ref(vShowMessage),_1)]-';'-')'-'(')>>')'>>';'|
//        lit("cMsg")>>'('>>*(char_[push_back(ref(vConsoleMessage),_1)]-';'-')'-'(')>>')'>>';'|
//        lit("qMsg")>>'('>>*(char_[push_back(ref(vQuestionMessage),_1)]-';'-')'-'(')>>')'>>';'|
//        lit("specialCommand")>>'('>>*(char_[push_back(ref(vSpecialCommand),_1)]-';'-')'-'('-',')>>','>>*(char_[push_back(ref(vSpecialParam),_1)]-'='-')'-'('-';'-',')>>')'>>';'|
//        lit("set")>>'('>>*(char_[push_back(ref(vSpecialCommand),_1)]-';'-')'-'(')>>')'>>';'|
//        lit("get")>>'('>>*(char_[push_back(ref(vSpecialParam),_1)]-';'-')'-'(')>>')'>>';'|
//        lit("loadVariant")>>'('>>*(char_[push_back(ref(vLoadVariant),_1)]-';'-')'-'(')>>')'>>';'|
//        lit("setNumSubVariant")>>'('>>int_[ref(numSubVar_)=_1]>>')'>>';' |
//        *(char_[push_back(ref(vValue1),_1)]-'='-';')>>'='>>*(char_[push_back(ref(vValue2),_1)]-'='-';')>>';' |
//        lit("/*")>>*(char_-'*'-'/')>>lit("*/")
//    ),
//    space
//    );

    bool r = phrase_parse(tempString.begin(),tempString.end(),
    //  Begin grammar
    (
        lit("var")>>*(char_[push_back(ref(vVariable),_1)]-'='-';')>>';' |
        lit("delay")>>'('>>int_[ref(sec_)=_1]>>')'>>';' |
        lit("iMsg")>>'('>>lexeme['"' >> +(char_[push_back(ref(vShowMessage),_1)] - '"') >> '"']>>')'>>';'|
        lit("cMsg")>>'('>>lexeme['"' >> +(char_[push_back(ref(vConsoleMessage),_1)] - '"') >> '"']>>')'>>';'|
        lit("qMsg")>>'('>>lexeme['"' >> +(char_[push_back(ref(vQuestionMessage),_1)] - '"') >> '"']>>')'>>';'|
        lit("specialCommand")>>'('>>*(char_[push_back(ref(vSpecialCommand),_1)]-';'-')'-'('-',')>>','>>*(char_[push_back(ref(vSpecialParam),_1)]-'='-')'-'('-';'-',')>>')'>>';'|
        lit("set")>>'('>>*(char_[push_back(ref(vSpecialCommand),_1)]-';'-')'-'(')>>')'>>';'|
        lit("get")>>'('>>*(char_[push_back(ref(vSpecialParam),_1)]-';'-')'-'(')>>')'>>';'|
        lit("loadVariant")>>'('>>*(char_[push_back(ref(vLoadVariant),_1)]-';'-')'-'(')>>')'>>';'|
        lit("setNumSubVariant")>>'('>>int_[ref(numSubVar_)=_1]>>')'>>';' |
        *(char_[push_back(ref(vValue1),_1)]-'='-';')>>'='>>*(char_[push_back(ref(vValue2),_1)]-'='-';')>>';' |
        lit("/*")>>*(char_-'*'-'/')>>lit("*/")
    ),
    space
    );

    createNodes(numLine);
    //! проверка какие узлы нужно создать
    return r;
}
void Translator::createNodes(int numLine)
{
    //qDebug("Create Nodes\n");
    if(sec_!=0)
    {
        //qDebug("Create Delay Node\n");
        INodeDelay *node=new INodeDelay;
        node->sec=sec_;
        node->line=numLine;
        rootNodesTrans->addChild(node);
    }

    if(vVariable.length() !=0)
    {
        table.append();
    }
    if(vShowMessage.length()!=0)
    {
        //qDebug("Create Message Node\n");
        INodeMessage *node=new INodeMessage;
        node->message=vShowMessage;
        node->typeMessage=0;
        node->line=numLine;
        rootNodesTrans->addChild(node);
    }
    if(vConsoleMessage.length()!=0)
    {
        //qDebug("Create Message Node\n");
        INodeMessage *node=new INodeMessage;
        node->message=vConsoleMessage;
        node->typeMessage=1;
        node->line=numLine;
        rootNodesTrans->addChild(node);
    }
    if(vQuestionMessage.length()!=0)
    {
        //qDebug("Create Message Node\n");
        INodeMessage *node=new INodeMessage;
        node->message=vQuestionMessage;
        node->typeMessage=2;
        node->line=numLine;
        rootNodesTrans->addChild(node);
    }
    if(vValue1.length()!=0 && vValue2.length()!=0)
    {

//        bool r = phrase_parse(vValue1.begin(),vValue1.end(),
//        //  Begin grammar
//        (
//            *(char_[push_back(ref(vValue1),_1)]-'='-';')>>'='>>*(char_[push_back(ref(vValue2),_1)]-'='-';')>>';' |
//        ),
//        space
//        );


        //qDebug("Create Equal Node\n");
        INodeEqual *node=new INodeEqual;
        node->setValueLeft(vValue1);
        node->setValueRight(vValue2);
        node->line=numLine;
        rootNodesTrans->addChild(node);
    }
    if(vSpecialCommand.length()!=0 && vSpecialParam.length()!=0)
    {
        INodeSpecial *node=new INodeSpecial;
        node->command=vSpecialCommand;
        node->param=vSpecialParam;
        rootNodesTrans->addChild(node);
        node->line=numLine;
    }else if(vSpecialCommand.length()!=0)
    {
        INodeSpecial *node=new INodeSpecial;
        node->command=QString("MPPM.")+QString("Set");
        node->param=vSpecialCommand;
        node->line=numLine;
        rootNodesTrans->addChild(node);

    }else if(vSpecialParam.length()!=0)
    {
        INodeSpecial *node=new INodeSpecial;
        node->command=QString("MPPM.")+QString("Get");
        node->param=vSpecialParam;
        node->line=numLine;
        rootNodesTrans->addChild(node);
    }else if(vLoadVariant.length()!=0)
    {
        INodeSpecial *node=new INodeSpecial;
        node->command=QString("VisV.")+QString("Set");
        node->param=vLoadVariant;
        node->line=numLine;
        rootNodesTrans->addChild(node);
    }
}

void Translator::clear()
{
    sec_=0;
    numSubVar_=0;
    vShowMessage.clear();
    vValue1.clear();
    vValue2.clear();
    vSpecialCommand.clear();
    vSpecialParam.clear();
    vConsoleMessage.clear();
    vQuestionMessage.clear();
    vLoadVariant.clear();
    vVariable.claet();
    //rootNodesTrans->child.clear();
}
