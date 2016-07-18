#include "erasediscdialog.h"
#include "ui_erasediscdialog.h"

EraseDiscDialog::EraseDiscDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EraseDiscDialog)
{
    ui->setupUi(this);    
    this->ui->EraseStatus->setValue(0);
    this->BurnCmd = new BurnManager();
    this->BurnCmd->GetDiscWriters();
    for(int i = 0 ; i<this->BurnCmd->CdWriters.size();i++)
    {
        this->ui->DriveSelect->insertItem(0,this->BurnCmd->CdWriters.at(i)->toQString());
    }
    this->exec();
}

EraseDiscDialog::~EraseDiscDialog()
{
    delete ui;
}

void EraseDiscDialog::on_Erase_clicked()
{
    this->ui->EraseStatus->setMinimum(0);
    this->ui->EraseStatus->setMaximum(0);
    //this->BurnCmd->BlankDisc()
    this->accept();
}
