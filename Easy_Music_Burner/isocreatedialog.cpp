#include "isocreatedialog.h"
#include "ui_isocreatedialog.h"

IsoCreateDialog::IsoCreateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IsoCreateDialog)
{
    ui->setupUi(this);
}

IsoCreateDialog::~IsoCreateDialog()
{
    delete ui;
}
