#include "burnmanager.h"

BurnManager::BurnManager()
{
    CdRecordPath = QCoreApplication::applicationDirPath().append("\\Tools\\cdrecord.exe");

}

BurnManager::BurnManager(WriterDevice dev, BurnInfo Binfo)
{
    CdRecordPath = QCoreApplication::applicationDirPath().append("\\Tools\\cdrecord.exe");
    this->BurnOptInfo = &Binfo;
    Binfo.Destanation = &dev;

}

BurnManager::BurnManager(WriterDevice dev, BurnInfo Binfo, FileManager *FileCmd)
{
    CdRecordPath = QCoreApplication::applicationDirPath().append("\\Tools\\cdrecord.exe");
    this->BurnOptInfo = &Binfo;
    Binfo.Destanation = &dev;
    this->FileCmd = FileCmd;

}

BurnManager::~BurnManager()
{
    if(this->BurnOptInfo !=NULL)delete this->BurnOptInfo;

}

void BurnManager::GetDiscWriters()
{

    QProcess *Cdrecord = new QProcess();
    QStringList ProgArgs;
    ProgArgs<<"-scanbus";
    Cdrecord->start(this->CdRecordPath,ProgArgs);
    if(Cdrecord->waitForStarted(-1))
    {


    }
    else
    {
        qInfo("Cdrecord Failed to check writers");
    }
    if(Cdrecord->waitForFinished(-1))
    {
        string Output = Cdrecord->readAllStandardOutput().constData();
        smatch wynik;
        regex SCSIDevices("[0-9],[0-9],[0-9]\\s*[0-9]\\)\\s*.{4,}"); // This will return CD Writing Devices
        regex AdditionalInfo("'([^']*)' '([^']*)' '([^']*)'");
        regex_search(Output,wynik,SCSIDevices);       
        for(int i=0;i<wynik.size();i++)
        {
            string dev = wynik.str(i);

            const char *DevB = new char(dev[0]); // Writer Key DEV=B,T,L
            const char *DevT = new char(dev[2]);
            const char *DevL = new char(dev[4]);
            int b,t,l;
            b = atoi(DevB);
            t = atoi(DevT);
            l = atoi(DevL);
            smatch InfoResult;
            regex_search(dev,InfoResult,AdditionalInfo,regex_constants::match_any);
           /* cout<<"0 -> "<<InfoResult[0]<<endl;
            cout<<"1 -> "<<InfoResult[1]<<endl;
            cout<<"2 -> "<<InfoResult[2]<<endl;
            cout<<"3 -> "<<InfoResult[3]<<endl;
            cout<<"4 -> "<<InfoResult[4]<<endl;*/
            this->CdWriters.push_back(new WriterDevice( b,t,l,QString::fromStdString(InfoResult[1]),
                                      QString::fromStdString(InfoResult[2]),QString::fromStdString(InfoResult[3]) )); // Add all detected writers to vector

        }
        this->GetWriterMaxIOSpeed();
        delete Cdrecord;

    }
    else
    {
        return;
    }

}

bool BurnManager::BlankDisc(WriterDevice *dev,QPlainTextEdit *LogOutput)
{

    if(!this->IsErasable(dev,LogOutput)) return false; // Not Possible to Erase Disc Abort Blank

    QString SProgramPath = QCoreApplication::applicationDirPath().append("\\Tools\\cdrecord.exe");

    QProcess *Cdrecord = new QProcess();

    QStringList ProgArgs;
    ProgArgs<< dev->toStringDevKey();
    ProgArgs<<"-blank=fast"; // For now only -fast
    Cdrecord->start(SProgramPath,ProgArgs); // Start Blanking
    if(Cdrecord->waitForStarted(-1))
    {


    }
    else
    {
        qInfo("Cdrecord Failed to check disk");
    }
    if(Cdrecord->waitForFinished(-1))
    {


        string Output = Cdrecord->readAllStandardOutput().constData();
        if(LogOutput != NULL)
        {
            LogOutput->setPlainText("BLANKING DISC PLEASE WAIT...........");
            LogOutput->appendPlainText(QString::fromStdString(Output));
            LogOutput->appendPlainText((QString)"COMPLETED!");
        }
        //cout<<Output<<endl;
        return true;

    }
    else
    {
        return false;
    }


}

bool BurnManager::IsErasable(WriterDevice *dev,QPlainTextEdit *LogOutput)
{

    if(dev == NULL)
    {
        if(&this->BurnOptInfo->Destanation == NULL || this->BurnOptInfo == NULL) return false; // If that happen something is really wrong !
        dev = this->BurnOptInfo->Destanation; // Fallback to BurnInfo->Destanation
    }


    vector<WriterDevice*> Writers;
    QProcess *Cdrecord = new QProcess();

    QStringList ProgArgs;
    ProgArgs<<"-media-info";
    ProgArgs<<dev->toStringDevKey();
    Cdrecord->start(this->CdRecordPath,ProgArgs);
    if(Cdrecord->waitForStarted(-1))
    {


    }
    else
    {
        qInfo("Cdrecord Failed to check disk");
    }
    if(Cdrecord->waitForFinished(-1))
    {

        // Check if Disc is present
        string Output = Cdrecord->readAllStandardOutput().constData();
        string ErrOutput = Cdrecord->readAllStandardError().constData();
        if(LogOutput != NULL)
        {
            LogOutput->setPlainText("CHECKING DISC PLEASE WAIT...........");
            //LogOutput->appendPlainText(QString::fromStdString(ErrOutput));

        }
        smatch StandardOutputRes;
        smatch ErrOutputRes;
        regex Disk("(cdrecord: No disk)"); // This will check if CD is present
        regex_search(Output,StandardOutputRes,Disk);
        regex_search(ErrOutput,ErrOutputRes,Disk);
        if(StandardOutputRes.size() == 1 || ErrOutputRes.size() == 1 )
        {
            if(LogOutput !=NULL)
            {
                LogOutput->appendPlainText("ERROR: No Disk in Selected Drive !");
            }
            return false;
        }

        smatch StandardOutputRes_Erase;
        smatch ErrOutputRes_Erase;
        regex DiskErase("Disk Is not erasable");
        regex_search(Output,StandardOutputRes_Erase,DiskErase);
        regex_search(ErrOutput,ErrOutputRes_Erase,DiskErase);
        cout<<Output<<endl;
        if(StandardOutputRes_Erase.size() == 1 || ErrOutputRes_Erase.size() == 1 )
        {
            if(LogOutput !=NULL)
            {
                LogOutput->appendPlainText("ERROR: Disk is not Erasable \n Remember to insert CD-RW or DVD-RW");
            }
            return false;
        }

        if(LogOutput != NULL)
        {
            LogOutput->appendPlainText(QString::fromStdString("COMPLETED READY FOR BLANK !"));
        }
        return true;


    }
    else
    {
        return false;
    }

}

void BurnManager::ConstructBurnInfo(int DiscType, int BurnType, int WriteSpeed, WriterDevice *Drive, bool SAO, bool TAO,QFileInfo Data)
{
    this->BurnOptInfo = new BurnInfo();
    this->BurnOptInfo->DiscType = DiscType;
    this->BurnOptInfo->BurnType = BurnType;
    this->BurnOptInfo->WriteSpeed = WriteSpeed;
    this->BurnOptInfo->Destanation = Drive;
    this->BurnOptInfo->Sao = SAO;
    this->BurnOptInfo->Tao = TAO;
    this->BurnOptInfo->Data = Data;

}

bool BurnManager::Burn()
{
    if(BurnOptInfo != NULL)
    {
        switch(BurnOptInfo->BurnType)
        {

        case MP3:
        {
            QProcess Burner;
            QStringList BurnArgs;
            BurnArgs<<BurnOptInfo->Destanation->toStringDevKey();
            BurnArgs<<QString("speed=").append(QString::number(BurnOptInfo->WriteSpeed));
            BurnArgs<<this->BurnOptInfo->Data.absoluteFilePath();
            Burner.start(this->CdRecordPath,BurnArgs);
            if(Burner.waitForStarted(-1)){}
            else{qInfo("ERR Burn Start");}
            if(Burner.waitForFinished(-1))
            {
                string Output = Burner.readAllStandardOutput();
            }
            else
            {
                qInfo("Err Burning");

            }

            break;
        }
        case AUDIOCD:
        {
            break;
        }
        default:
        {
            break;
        }
        }

    }
    else
    {
        return false;
    }

}

int *BurnManager::GetWriterMaxIOSpeed()
{
    // Get All Additional info about detected writers
    for(int i=0;i<this->CdWriters.size();i++)
    {
        QProcess WriterInfo;
        QStringList ProgArgs;
        ProgArgs<<this->CdWriters.at(i)->toStringDevKey();
        ProgArgs<<"-prcap";
        WriterInfo.start(this->CdRecordPath,ProgArgs);
        if(WriterInfo.waitForStarted(-1))
        {
        }
        else
        {
            qInfo("Cdrecord Failed to check writers");
        }
        if(WriterInfo.waitForFinished(-1))
        {

            string Output = WriterInfo.readAllStandardOutput().constData();
            smatch WriterSpeedInfo;
            sregex_token_iterator end;
            regex SpeedMatch("(Write speed . [0-9]+: .*)(CD\\s*)([0-9]+)(.+DVD\\s*)([0-9]+)(.+BD\\s*)([0-9]+)");
            for (std::sregex_token_iterator m(Output.cbegin(), Output.cend(), SpeedMatch);m != end;++m)
            {
                string g = *m;
                regex_search(g,WriterSpeedInfo,SpeedMatch);
                string tmpCd = WriterSpeedInfo[3];
                string tmpDvd = WriterSpeedInfo[5];
                this->CdWriters.at(i)->addCDSupportedSpeed(stoi(tmpCd));
                this->CdWriters.at(i)->addDVDSupportedSpeed(stoi(tmpDvd));

           }
        }
        else
        {
            return NULL;
        }

    }

}

WriterDevice::WriterDevice(int B, int T, int L)
{
    this->B = B;
    this->L = L;
    this->T = T;

}

WriterDevice::WriterDevice(int B,int T,int L,QString Vendor,QString Id,QString Revision)
{
    this->B = B;
    this->L = L;
    this->T = T;
    this->VendorInfo = Vendor;
    this->Id = Id;
    this->Revision = Revision;
}

QString WriterDevice::toQString()
{
    QString Key;
    Key.append("DEV = (").append(QString::number(this->B)).append(",").append(QString::number(this->T)).append(",").append(QString::number(this->L))
            .append(") ").append(this->VendorInfo).append(" ").append(this->Id).append(" ").append(this->Revision);
    return Key;
}

QString WriterDevice::toStringDevKey()
{
    QString dev = "dev=";
    dev.append(QString::number(this->B)).append(",").append(QString::number(this->T)).append(",")
            .append(QString::number(this->L));
    return dev;

}

vector<int> WriterDevice::getCDSupportedSpeeds() const
{
    return CDSupportedSpeeds;
}

vector<int> WriterDevice::getDVDSupportedSpeeds() const
{
    return DVDSupportedSpeeds;
}

void WriterDevice::addCDSupportedSpeed(int val)
{
    this->CDSupportedSpeeds.push_back(val);
}

void WriterDevice::addDVDSupportedSpeed(int val)
{
    this->DVDSupportedSpeeds.push_back(val);
}




