#ifndef KERNELMPPM_H
#define KERNELMPPM_H

#include "domParser.h"

//! класс ядро данного модуля, в котором работает разбор данных и сообщений
class KernelMPPM
{
public:
    KernelMPPM();
    ~KernelMPPM();
private:
    //! разбор файла вполне
    DomParser *domParser;

};

#endif // KERNELMPPM_H
