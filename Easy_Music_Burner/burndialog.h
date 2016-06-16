#ifndef BURNDIALOG_H
#define BURNDIALOG_H

#include <QDialog>

namespace Ui {
class BurnDialog;
}

class BurnDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BurnDialog(QWidget *parent = 0);
    ~BurnDialog();

private:
    Ui::BurnDialog *ui;
};

#endif // BURNDIALOG_H
