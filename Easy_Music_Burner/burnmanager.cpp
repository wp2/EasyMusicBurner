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

vector<WriterDevice *> BurnManager::GetDiscWriters()
{
    QString SProgramPath = QCoreApplication::applicationDirPath().append("\\Tools\\cdrecord.exe");
    vector<WriterDevice*> Writers;
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

            this->CdWriters.push_back(new WriterDevice( b,t,l,"ATAPI","IDTEST","TST" )); // Add all detected writers to vector
            //cout<<"Result["<<i<<"]"<<endl;    // Debug Info
            //cout<<wynik[i]<<endl;
            //cout<<endl;
        }
        return Writers;

    }
    else
    {
        exit(1);
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
            .append(") ").append(this->VendorInfo).append(" ").append(this->Id);
    return Key;
}
