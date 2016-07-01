#include "burnmanager.h"

BurnManager::BurnManager()
{
    ProgramPath = QCoreApplication::applicationDirPath().append("\\Tools\\cdrecord.exe");

}

void BurnManager::GetDiscWriters()
{
    CdWriters.clear();
    QProcess *Cdrecord = new QProcess();
    QStringList ProgArgs;
    ProgArgs<<"-scanbus";
    Cdrecord->start(this->ProgramPath,ProgArgs);
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
            dev.erase(5,string::npos);
            const char *DevB = new char(dev[0]); // Writer Key DEV=B,T,L
            const char *DevT = new char(dev[2]);
            const char *DevL = new char(dev[4]);
            int b,t,l;
            b = atoi(DevB);
            t = atoi(DevT);
            l = atoi(DevL);

            CdWriters.push_back(new WriterDevice( b,t,l )); // Add all detected writers to vector
            //cout<<"Result["<<i<<"]"<<endl;    // Debug Info
            //cout<<wynik[i]<<endl;
            //cout<<endl;
        }


    }
    else
    {
        exit(1);
    }

}

BurnManager::WriterDevice::WriterDevice(int B, int T, int L)
{
    this->B = B;
    this->L = L;
    this->T = T;
}

QString BurnManager::WriterDevice::toQString()
{
    QString Key;
    Key.append(QString::number(this->B)).append(",").append(QString::number(this->T)).append(",").append(QString::number(this->L));
    return Key;
}
