#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include"musicmodel.h"
#include "includeheaders.h"

class FileManager
{


    QString OutDIR;   
    QString ISOTargetDIR;
    vector<Music*> MusicFiles;
    QDir *Tmp;
    string UserName;
    QFileInfo *GeneratedIso;
public:
    FileManager(QString Output);
    FileManager(QString Output,vector<Music*>files);

    ~FileManager();

    void PopulateDIR();
    bool CleanDIR();
    bool CreateTempDir();
    bool CheckIfEmptyAndDeleteFiles(string dir);
    bool RunMKISOFSProgram(QStringList Args);
    void SetMusicFiles(vector<Music*>files);
    vector<Music*> SetMusicFileOrder();
    bool CreateISO();

    QFileInfo* getGeneratedIso() const;
    void setGeneratedIso(QFileInfo *value);
};

#endif // FILEMANAGER_H
