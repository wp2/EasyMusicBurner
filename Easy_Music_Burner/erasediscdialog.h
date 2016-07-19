#ifndef ERASEDISCDIALOG_H
#define ERASEDISCDIALOG_H

#include <QDialog>
#include "includeheaders.h"
#include "burnmanager.h"
namespace Ui {
class EraseDiscDialog;
}

class EraseDiscDialog : public QDialog
{
    Q_OBJECT
    BurnManager *BurnCmd;
public:
    explicit EraseDiscDialog(QWidget *parent = 0);
    ~EraseDiscDialog();

private slots:
    void on_Erase_clicked();
    void OnProgramOutput(QString Log);
private:
    Ui::EraseDiscDialog *ui;
    QThread Communicator; // Test of communicating between Status -> BurnerManager Methods
};

#endif // ERASEDISCDIALOG_H
