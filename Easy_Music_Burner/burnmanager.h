#ifndef BURNMANAGER_H
#define BURNMANAGER_H
#include "includeheaders.h"
#include "filemanager.h"

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
    QString toQString();
    QString toStringDevKey();    
    vector<int> getCDSupportedSpeeds() const;
    vector<int> getDVDSupportedSpeeds() const;
    void addCDSupportedSpeed(int val);
    void addDVDSupportedSpeed(int val);
private:
    vector<int> CDSupportedSpeeds;
    vector<int> DVDSupportedSpeeds;


};

struct BurnInfo
{
    int DiscType; // 0 - CD , 1 - CD-RW
    int BurnType; // 0- MP3 data , 1 - Audio CD
    int WriteSpeed; // 0 - AUTO , 1+ - Set by User
    WriterDevice *Destanation; // Writer Destanation
    bool Sao;
    bool Tao;
    QFileInfo Data;
};

class BurnManager
{

    QString CdRecordPath;
public:
    vector<WriterDevice*> CdWriters;    
    BurnInfo *BurnOptInfo;
    BurnManager();
    BurnManager(WriterDevice dev,BurnInfo Binfo);
    BurnManager(WriterDevice dev, BurnInfo Binfo,FileManager *FileCmd);
    ~BurnManager();
    void GetDiscWriters();
    bool BlankDisc(WriterDevice *dev = NULL,QPlainTextEdit *LogOutput = NULL); // By default use Binfo.Destanation
    bool IsErasable(WriterDevice *dev = NULL,QPlainTextEdit *LogOutput = NULL);
    bool IsWriteable(WriterDevice *dev = NULL,QPlainTextEdit *LogOutput = NULL);    
    void ConstructBurnInfo(int DiscType, int BurnType,int WriteSpeed,WriterDevice *Drive,bool SAO,bool TAO,QFileInfo Data);
    bool Burn();
private:
    FileManager *FileCmd;
    QProcess *Program;
    int* GetWriterMaxIOSpeed();


};

#endif // BURNMANAGER_H
