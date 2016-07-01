#include "burnisodialog.h"
#include "ui_burnisodialog.h"

BurnIsoDialog::BurnIsoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BurnIsoDialog)
{
    ui->setupUi(this);
    Init();
    this->exec();
}

BurnIsoDialog::~BurnIsoDialog()
{
    delete ui;
}

void BurnIsoDialog::Init()
{
    BurnManager BurnCommander;
    BurnCommander.GetDiscWriters();
    for(int i=0; i<BurnCommander.CdWriters.size();i++)
    {
        this->ui->Writers->insertItem(0,BurnCommander.CdWriters.at(i)->toQString());

    }
}
