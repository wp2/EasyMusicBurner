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
    BurnManager *BurnCmd;
public:
    explicit BurnIsoDialog(QWidget *parent = 0);
    ~BurnIsoDialog();

private slots:
    void on_SelectIso_clicked();



    void on_MultiSession_clicked();

    void on_SingleSession_clicked();

    void on_BurnISO_clicked();

private:
    Ui::BurnIsoDialog *ui;
    void Init();
    bool CheckIfBurnOptionsAreValid();
};

#endif // BURNISODIALOG_H
