#include "burnmusicdirectdialog.h"
#include "ui_burnmusicdirectdialog.h"

BurnMusicDirectDialog::BurnMusicDirectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BurnMusicDirectDialog)
{
    this->BurnMode = MP3; // As Default
    this->RecordManager = new BurnManager();
    ui->setupUi(this);
    this->Init();
    this->exec();
}

BurnMusicDirectDialog::BurnMusicDirectDialog(int BurnMode,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BurnMusicDirectDialog)
{
    this->BurnMode = BurnMode; // As selected by User
    this->RecordManager = new BurnManager();
    ui->setupUi(this);
    this->Init();
    this->exec();
}



BurnMusicDirectDialog::~BurnMusicDirectDialog()
{
    delete ui;
}

void BurnMusicDirectDialog::Init()
{
    this->InitWriterSelection();
    this->InitWriterRecordSpeed();

}

void BurnMusicDirectDialog::on_BurnMusic_clicked()
{
   // this->RecordManager->ConstructBurnInfo(0,this->BurnMode,this->ui->BurnSpeed->currentData().toInt(),(WriterDevice*)this->ui->Drives->currentData().value<void*>(),false,false,
    //                                       QFileInfo(this->ui->));
   // this->RecordManager->Burn();
}
/*
void BurnMusicDirectDialog::on_MultiSession_clicked()
{
    if(this->ui->MultiSession->isChecked() && !this->ui->SingleSession->isChecked())
    {
        this->ui->MultiSession->setChecked(true);
    }
    else if(!this->ui->MultiSession->isChecked() && this->ui->SingleSession->isChecked())
    {
        this->ui->SingleSession->setChecked(false);
        this->ui->MultiSession->setChecked(true);
    }

}

void BurnMusicDirectDialog::on_SingleSession_clicked()
{
    if(!this->ui->MultiSession->isChecked() && this->ui->SingleSession->isChecked())
    {
        this->ui->SingleSession->setChecked(true);
    }
    else if(this->ui->MultiSession->isChecked() && !this->ui->SingleSession->isChecked())
    {
        this->ui->MultiSession->setChecked(false);
        this->ui->SingleSession->setChecked(true);
    }

}
*/

bool BurnMusicDirectDialog::CheckIfBurnOptionsAreValid()
{
    if(this->ui->FileNameSys->currentText().isEmpty())return false;
    if(this->ui->Drives->currentText().isEmpty())return false;
    if(this->ui->BurnSpeed->currentText().isEmpty())return false;
    return true;

}

void BurnMusicDirectDialog::InitWriterSelection()
{
    // Init Available Drivers **************************************
    // Do this in thread ( not required here because this.exec() has been not called)
    BurnManagerWorker *BurnWorker = new BurnManagerWorker(this->RecordManager,1);
    QThread *BurnThread = new QThread();
    BurnWorker->moveToThread(BurnThread);
    connect(BurnThread,SIGNAL(started()),BurnWorker,SLOT(doWork()),Qt::DirectConnection);
    connect(BurnWorker,SIGNAL(Finished()),BurnThread,SLOT(quit()),Qt::DirectConnection);
    connect(BurnThread, SIGNAL(finished()), BurnThread, SLOT(deleteLater()),Qt::DirectConnection);
    connect(BurnWorker, SIGNAL(Finished()), BurnWorker, SLOT(deleteLater()),Qt::DirectConnection);
    BurnThread->start();
    BurnThread->wait();

    // OK We have writers set them to combo
    for(int i = 0 ;i < this->RecordManager->CdWriters.size();i++)
    {
        QVariant v = qVariantFromValue((void*)this->RecordManager->CdWriters.at(i));
        this->ui->Drives->insertItem(0,this->RecordManager->CdWriters.at(i)->toQString(),v);
    }

}

void BurnMusicDirectDialog::InitWriterRecordSpeed()
{
    WriterDevice *Drive = (WriterDevice*)this->ui->Drives->currentData().value<void*>();
    for(int j =0; j<Drive->getCDSupportedSpeeds().size();j++)
    {
        this->ui->BurnSpeed->insertItem(0,QString::number(Drive->getCDSupportedSpeeds().at(j)).append("x"),Drive->getCDSupportedSpeeds().at(j));
    }

}
