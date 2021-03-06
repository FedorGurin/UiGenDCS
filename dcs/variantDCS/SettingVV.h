#ifndef SETTINGVV_H
#define SETTINGVV_H

#include <QString>
#include <QObject>

class SettingVV:public QObject
{
public:
    SettingVV(QObject* parent=0);

    QString fileName;
    QString hostAddress;
    QString userName;
    QString password;
    QString pathCD;
    //! директория по умолчанию, куда обычно сохраняются варианты
    QString dirSaveVar;
    //! директория с картой
    QString pathWithMap;

    //! начальная точка старта на карте
    double startLat;
    double startLon;
    //! уровень детализации
    int zoom;
    //! время ожидания по ftp
    int FTPWait;
    //! разрешение отрисовки двигующихся объектов
    int moveObjects;
    //! не использовать FTP
    int noFTP;
    //! тип используемой по умолчанию карты
    QString typeMap;
    //! тип используемого по умолчанию слоя
    QString typeLayer;
};

#endif // SETTINGVV_H
