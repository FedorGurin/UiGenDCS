#ifndef UTILS_FUNC_H
#define UTILS_FUNC_H

#include <QString>
#include <QDomElement>

//! чтение данных из XML файла
QString readParamFromXMLFile(QString fileName,
                             QString nameProg,
                             QString nameAttrib,
                             QString defaultStr);
//! запись данных в XML файл
bool writeAttrParamToXMLFile(QString fileName,
                             QString nameProg,
                             QString nameAttrib,
                             QString value);

QDomElement paramFromXMLFileWithAttrib(QString fileName,
                                       QString nameProg,
                                       QString nameAttrib);

#endif
