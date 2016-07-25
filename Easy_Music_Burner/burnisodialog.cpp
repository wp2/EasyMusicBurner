#include "burnisodialog.h"
#include "ui_burnisodialog.h"
#include "thread"
BurnIsoDialog::BurnIsoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BurnIsoDialog)
{
    ui->setupUi(this);
    this->BurnCmd = new BurnManager();    

    Init();
    this->exec();
}

BurnIsoDialog::~BurnIsoDialog()
{
    delete BurnCmd;
    delete ui;
}

void BurnIsoDialog::Init()
{
    InitWriterSelection();
}

void BurnIsoDialog::InitWriterSelection()
{
    // Init Available Drivers **************************************
    BurnManagerWorker *BurnWorker = new BurnManagerWorker(this->BurnCmd,1);
    QThread *BurnThread = new QThread();
    BurnWorker->moveToThread(BurnThread);
    connect(BurnThread,SIGNAL(started()),BurnWorker,SLOT(doWork()),Qt::DirectConnection);
    connect(BurnWorker,SIGNAL(Finished()),BurnThread,SLOT(quit()),Qt::DirectConnection);
    connect(BurnThread, SIGNAL(finished()), BurnThread, SLOT(deleteLater()),Qt::DirectConnection);
    connect(BurnWorker, SIGNAL(Finished()), BurnWorker, SLOT(deleteLater()),Qt::DirectConnection);
    BurnThread->start();
    BurnThread->wait();

    // OK We have writers set them to combo
    for(int i = 0 ;i < this->BurnCmd->CdWriters.size();i++)
    {
        QVariant v = qVariantFromValue((void*)this->BurnCmd->CdWriters.at(i));
        this->ui->Writers->insertItem(0,this->BurnCmd->CdWriters.at(i)->toQString(),v);
    }

    //For curently selected writer output supported write speed
    WriterDevice *Drive = (WriterDevice*)this->ui->Writers->currentData().value<void*>();
    for(int j =0; j<Drive->getCDSupportedSpeeds().size();j++)
    {
        this->ui->RecordSpeed->insertItem(0,QString::number(Drive->getCDSupportedSpeeds().at(j)).append("x"),Drive->getCDSupportedSpeeds().at(j));
    }

}

void BurnIsoDialog::AnalyzeAndPopulateRecordSpeed()
{


}

bool BurnIsoDialog::CheckIfBurnOptionsAreValid()
{
    if(!this->ui->IsoPath->toPlainText().length() > 0)
    {
        return false;
    }
    if(!this->ui->Writers->count() > 0 )
    {
        return false;
    }
    if(!this->ui->SingleSession->isChecked() && !this->ui->MultiSession->isChecked())
    {
        return false;
    }
    if(this->ui->RecordSpeed->currentText().isEmpty())
    {
        return false;
    }
    return true;

}



void BurnIsoDialog::on_SelectIso_clicked()
{
    QFileDialog IsoFileChooser;
    IsoFileChooser.setFileMode(QFileDialog::ExistingFiles);
    IsoFileChooser.setNameFilter(tr(("Pliki Obrazu (*.iso)")));
    if(IsoFileChooser.exec())
    {
        QStringList SelectedFiles = IsoFileChooser.selectedFiles();
        for(int i =0;i<SelectedFiles.count();i++)
        {
            QFileInfo ftmp(QFile(SelectedFiles.at(i)));
            this->ui->IsoPath->setText(ftmp.absoluteFilePath());

        }
    }
    if(CheckIfBurnOptionsAreValid()){ this->ui->BurnISO->setEnabled(true);}
}




void BurnIsoDialog::on_BurnISO_clicked()
{
    //Check for the last time if all options are valid
    if(!CheckIfBurnOptionsAreValid()){ return;}
    this->BurnCmd->ConstructBurnInfo(0,MP3,this->ui->RecordSpeed->currentData().toInt(),(WriterDevice*)this->ui->Writers->currentData().value<void*>(),false,false,
                                     QFileInfo(this->ui->IsoPath->toPlainText()));
    if(this->BurnCmd->Burn()) this->accept();
    //Gather All options about burn from Dialog

    //BurnManager Burner(BurnManager::WriterDevice(),BurnManager::BurnInfo());
}

void BurnIsoDialog::ThreadFinished()
{
    cout<<"SIGNAl THREAD ENDED"<<endl;
}
