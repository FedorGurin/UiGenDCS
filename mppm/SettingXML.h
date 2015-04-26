#ifndef SETTINGXML_H
#define SETTINGXML_H
#include <QString>

class SettingXML
{
public:
    SettingXML();
    QString ip;
    QString ip_main_prog;

    //! название файла с данными
    QString fileData;

    //! принак того, что программа всегда запускается в режиме ведущая
    bool main_always;

    int send_port;
    int recive_port;
    int recive_port_slave;
    int send_port_slave;
    int sizeFont;

    //! выравнивание по кол-ву байт
    int allign;
    //! получить указатель на статический объект
    static SettingXML* getInstance();
private:
    static SettingXML *setting;
};

#endif // SETTINGXML_H
