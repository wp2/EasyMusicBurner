#include "filemanager.h"






QFileInfo* FileManager::getGeneratedIso() const
{
    return GeneratedIso;
}

void FileManager::setGeneratedIso(QFileInfo *value)
{
    GeneratedIso = value;
}

QString FileManager::getISOTargetDIR() const
{
    return ISOTargetDIR;
}

FileManager::FileManager()
{

}

FileManager::FileManager(QString Output)
{
#ifdef _WIN32
    // Get UserName under windows
    wchar_t username[256 + 1];
    DWORD size = 256 + 1;
    GetUserNameW(username, &size);
    wstring conv(username);
    string UserName(conv.begin(),conv.end()); // We now have username rest is easy
    this->UserName = UserName;
    QString isotgt = "C:\\Users\\";
    QString IsoRandName = "Cd_";
    time_t Time = time(NULL);
    localtime(&Time);
    IsoRandName.append(QDateTime::currentDateTime().toString());
    isotgt.append(UserName.c_str()).append("\\Documents\\CD_Compilation_").append(IsoRandName).append(".iso");
    this->ISOTargetDIR = isotgt;
    #endif

    #ifdef linux
    #endif
    // Call this if you want to use only SetMusicFiles function    
    Tmp = new QDir(QDir::temp());
    QString DirName = "EMB_";
    DirName.append(QString::number(QCoreApplication::applicationPid()));
    if(Tmp->mkdir(DirName))
    {

        Tmp->cd(DirName);
        OutDIR = Tmp->path();

    }

}

FileManager::FileManager(QString Output, vector<Music *> files)
{
    #ifdef _WIN32

    // Get UserName under windows
    wchar_t username[256 + 1];
    DWORD size = 256 + 1;
    GetUserNameW(username, &size);
    wstring conv(username);
    string UserName(conv.begin(),conv.end()); // We now have username rest is easy
    this->UserName = UserName;
    QString isotgt = "C:\\Users\\";
    QString IsoRandName = "Cd_";
    time_t Time = time(NULL);
    localtime(&Time);
    IsoRandName.append(QDateTime::currentDateTime().toString());
    isotgt.append(UserName.c_str()).append("\\Documents\\CD_Compilation_").append(IsoRandName).append(".iso");
    this->ISOTargetDIR = isotgt;
    #endif

    #ifdef linux
    #endif

    Tmp = new QDir(QDir::temp());
    QString DirName = "EMB_";
    DirName.append(QString::number(QCoreApplication::applicationPid()));
    if(Tmp->mkdir(DirName))
    {

        Tmp->cd(DirName);
        OutDIR = Tmp->path();

    }
    this->MusicFiles = files;
}



FileManager::~FileManager()
{
    Tmp->removeRecursively(); // Delete Temp
    delete Tmp; // delete Tmp on Heap
    MusicFiles.clear(); // Clear Music Vector
    if(this->GeneratedIso != NULL)delete this->GeneratedIso;
}

void FileManager::SetMusicFiles(vector<Music *> files)
{
    // Helper function that can set/reset MusicFiles vector
    // Use only if you need it !
    if(!this->MusicFiles.empty()) MusicFiles.clear();
    this->MusicFiles = files;
}

bool FileManager::CreateISO()
{
    if( MusicFiles.size() > 0)
    {
        // Ok Copy Files to temp and run mkisofs
        for(int i=0; i<MusicFiles.size();i++)
        {
            QFile::copy(MusicFiles.at(i)->getPath(),Tmp->path().append("/").append(QString::number(i)).append(".").append(MusicFiles.at(i)->getFileName()));
        }
        QString Param1("-o=");
        Param1.append(this->ISOTargetDIR);

        QStringList Params;
        Params<<"-J"<<Param1<<this->OutDIR;        
        if(RunMKISOFSProgram(Params))
        {
            this->GeneratedIso = new QFileInfo(this->ISOTargetDIR);
            return true;
        }
        return false;

    }
    else
    {
        // Temp dir failed to create
        return false;
    }
}



bool FileManager::RunMKISOFSProgram(QStringList Args)
{
    #ifdef _WIN32

    QString ProgramPath = QCoreApplication::applicationDirPath().append("\\Tools\\mkisofs.exe");
    //QStringList Argss;
    //Argss<<"-o=C:\\Users\\Wojtek\\Desktop\\HELLO.iso"<<"C:\\Users\\Wojtek\\Desktop\\tst";


    #endif
    #ifdef linux

    #endif

    QProcess *mkisofs = new QProcess();
    mkisofs->start(ProgramPath,Args);
    if(mkisofs->waitForStarted(-1))
    {

        qInfo("OK!");

    }
    else
    {
        qInfo("Not Started");
    }
    string output = mkisofs->readAllStandardError().toStdString();
    string output2 = mkisofs->readAll().toStdString();
    if(mkisofs->waitForFinished(-1))
    {
        qInfo("OK!");
        qInfo(output.c_str());
        qInfo(output2.c_str());
        this->GeneratedIso = new QFileInfo(Args[1]);
        return true;
    }
    else
    {
        int ErrCode = mkisofs->error();
        for(int i=0;i<mkisofs->arguments().size();i++)
        {
            qInfo(mkisofs->arguments().at(i).toStdString().c_str());

        }

        qInfo("Failed ERR CODE = ");
        QString g = QString::number(ErrCode);
        qInfo(g.toStdString().c_str());
        return false;
    }

    return true;
}

