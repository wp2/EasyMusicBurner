#ifndef BURNISODIALOG_H
#define BURNISODIALOG_H

#include <QDialog>
#include "burnmanager.h"
namespace Ui {
class BurnIsoDialog;
}

class BurnIsoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BurnIsoDialog(QWidget *parent = 0);
    ~BurnIsoDialog();

private:
    Ui::BurnIsoDialog *ui;
    void Init();
};

#endif // BURNISODIALOG_H
