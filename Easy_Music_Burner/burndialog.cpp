#include "burndialog.h"
#include "ui_burndialog.h"

BurnDialog::BurnDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BurnDialog)
{
    ui->setupUi(this);
}

BurnDialog::~BurnDialog()
{
    delete ui;
}
