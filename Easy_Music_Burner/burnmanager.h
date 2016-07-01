#ifndef BURNMANAGER_H
#define BURNMANAGER_H
#include "includeheaders.h"

class BurnManager
{
    QString ProgramPath;
    struct WriterDevice
    {
    public:
        int B; // Key for cdrecord commands (dev=b,t,l)
        int T;
        int L;
        WriterDevice(int B,int T,int L);
        WriterDevice(){};
        QString toQString();

    };

public:
    vector<WriterDevice*> CdWriters;
    BurnManager();
    void GetDiscWriters();
    bool BlankDisc(int B,int T,int L);

};

#endif // BURNMANAGER_H
