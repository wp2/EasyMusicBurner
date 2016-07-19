#include "burnmanager.h"

BurnManager::BurnManager()
{
    ProgramPath = QCoreApplication::applicationDirPath().append("\\Tools\\cdrecord.exe");

}

BurnManager::BurnManager(WriterDevice dev, BurnInfo Binfo)
{
    this->BurnOptInfo = &Binfo;
    Binfo.Destanation = dev;

}

void BurnManager::GetDiscWriters()
{
    QString SProgramPath = QCoreApplication::applicationDirPath().append("\\Tools\\cdrecord.exe");   
    QProcess *Cdrecord = new QProcess();
    QStringList ProgArgs;
    ProgArgs<<"-scanbus";
    Cdrecord->start(SProgramPath,ProgArgs);
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
       // qInfo(Output.c_str());
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
            cout<<"0 -> "<<InfoResult[0]<<endl;
            cout<<"1 -> "<<InfoResult[1]<<endl;
            cout<<"2 -> "<<InfoResult[2]<<endl;
            cout<<"3 -> "<<InfoResult[3]<<endl;
            cout<<"4 -> "<<InfoResult[4]<<endl;
            this->CdWriters.push_back(new WriterDevice( b,t,l,QString::fromStdString(InfoResult[1]),
                                      QString::fromStdString(InfoResult[2]),QString::fromStdString(InfoResult[3]) )); // Add all detected writers to vector

        }


    }
    else
    {
        exit(1);
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
        dev = &this->BurnOptInfo->Destanation; // Fallback to BurnInfo->Destanation
    }

    QString SProgramPath = QCoreApplication::applicationDirPath().append("\\Tools\\cdrecord.exe");
    vector<WriterDevice*> Writers;
    QProcess *Cdrecord = new QProcess();

    QStringList ProgArgs;
    ProgArgs<<"-media-info";
    ProgArgs<<dev->toStringDevKey();
    Cdrecord->start(SProgramPath,ProgArgs);
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
        regex Disk("cdrecord: No disk"); // This will check if CD is present
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

bool BurnManager::Burn()
{
    if(BurnOptInfo != NULL)
    {

    }
    else
    {
        return false;
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
