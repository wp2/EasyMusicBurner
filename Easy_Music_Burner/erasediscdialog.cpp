#include "erasediscdialog.h"
#include "ui_erasediscdialog.h"

EraseDiscDialog::EraseDiscDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EraseDiscDialog)
{
    ui->setupUi(this);    

    this->BurnCmd = new BurnManager();
    this->BurnCmd->GetDiscWriters();
    for(int i = 0 ; i<this->BurnCmd->CdWriters.size();i++)
    {
        QVariant v = qVariantFromValue((void*)this->BurnCmd->CdWriters.at(i));
        this->ui->DriveSelect->insertItem(0,this->BurnCmd->CdWriters.at(i)->toQString(),v);
    }
    this->exec();
}

EraseDiscDialog::~EraseDiscDialog()
{
    delete ui;
}

void EraseDiscDialog::on_Erase_clicked()
{

    //this->BurnCmd->BlankDisc()
    WriterDevice *Drive = (WriterDevice*)this->ui->DriveSelect->currentData().value<void*>();
    this->BurnCmd->BlankDisc(Drive,this->ui->plainTextEdit);
    //this->accept();
}

void EraseDiscDialog::OnProgramOutput(QString Log)
{

}
