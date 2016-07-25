#ifndef ISOCREATEDIALOG_H
#define ISOCREATEDIALOG_H

//#include <QDialog>
#include "includeheaders.h"
namespace Ui {
class IsoCreateDialog;
}

class IsoCreateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IsoCreateDialog(QWidget *parent = 0);
    ~IsoCreateDialog();

private:
    Ui::IsoCreateDialog *ui;
};

#endif // ISOCREATEDIALOG_H
