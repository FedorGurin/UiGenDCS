#include "completercommand.h"

CompleterCommand::CompleterCommand(QObject *parent) :
    QObject(parent)
{
    completer=new QCompleter();
}
