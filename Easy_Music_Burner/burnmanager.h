#ifndef BURNMANAGER_H
#define BURNMANAGER_H
#include "includeheaders.h"
class WriterItemModel : QAbstractItemModel
{

};

struct WriterDevice
{
public:
    int B; // Writer Key for cdrecord commands (dev=b,t,l)
    int T;
    int L;
    QString VendorInfo;
    QString Id;
    QString Revision;
    WriterDevice(int B, int T, int L);
    WriterDevice(int B,int T,int L,QString Vendor,QString Id,QString Revision);
    WriterDevice(){};
    QString toQString();
    QString toStringDevKey();

};

struct BurnInfo
{
    int DiscType; // 0 - CD , 1 - CD-RW
    int BurnType; // 0- MP3 data , 1 - Audio CD
    int WriteSpeed; // 0 - AUTO , 1+ - Set by User
    WriterDevice Destanation; // Writer Destanation
    bool Sao;
    bool Tao;
};

class BurnManager
{

    QString ProgramPath;
public:
    vector<WriterDevice*> CdWriters;    
    BurnInfo *BurnOptInfo;
    BurnManager();
    BurnManager(WriterDevice dev,BurnInfo Binfo);
    void GetDiscWriters();
    bool BlankDisc(WriterDevice *dev = NULL,QPlainTextEdit *LogOutput = NULL); // By default use Binfo.Destanation
    bool IsErasable(WriterDevice *dev = NULL,QPlainTextEdit *LogOutput = NULL);
    bool IsWriteable(WriterDevice *dev = NULL,QPlainTextEdit *LogOutput = NULL);

    bool Burn();

};

#endif // BURNMANAGER_H
