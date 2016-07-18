#include "burnisodialog.h"
#include "ui_burnisodialog.h"

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

    //vector<WriterDevice*> Dev = BurnManager::GetDiscWriters();
    this->BurnCmd->GetDiscWriters();
    for(int i=0; i<this->BurnCmd->CdWriters.size();i++)
    {
        //this->ui->Writers->insertItem(0,Dev.at(i)->toQString(),Dev.at(i));

    }

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


void BurnIsoDialog::on_MultiSession_clicked()
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
    if(CheckIfBurnOptionsAreValid()){ this->ui->BurnISO->setEnabled(true);}

}

void BurnIsoDialog::on_SingleSession_clicked()
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
    if(CheckIfBurnOptionsAreValid()){ this->ui->BurnISO->setEnabled(true);}
}

void BurnIsoDialog::on_BurnISO_clicked()
{
    //Check for the last time if all options are valid
    if(!CheckIfBurnOptionsAreValid()){ return;}
    //Gather All options about burn from Dialog
    this->accept();
    //BurnManager Burner(BurnManager::WriterDevice(),BurnManager::BurnInfo());
}
