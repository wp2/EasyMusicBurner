#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include"musicmodel.h"
#include "includeheaders.h"
#include "mainwindow.h"
class FileManager
{


    QString OutDIR;   
    QString ISOTargetDIR;
    vector<Music*> MusicFiles;
    QDir *Tmp;
    string UserName;
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

};

#endif // FILEMANAGER_H
