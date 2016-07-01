#ifndef ISOCEATOR_H
#define ISOCEATOR_H
#include <filemanager.h>
#include "includeheaders.h"
class ISOCeator
{
    QString OutPath;
    FileManager *FileCommander;
public:
    ISOCeator();
    bool RunProgram(QStringList Args);
    bool CreateISO();
};

#endif // ISOCEATOR_H
