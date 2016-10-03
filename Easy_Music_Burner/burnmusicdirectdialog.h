#ifndef BURNMUSICDIRECTDIALOG_H
#define BURNMUSICDIRECTDIALOG_H

//#include <QDialog>
#include "includeheaders.h"
#include "burnmanager.h"
#include "burnmanagerworker.h"
namespace Ui {
class BurnMusicDirectDialog;
}

class BurnMusicDirectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BurnMusicDirectDialog(QWidget *parent = 0);
    explicit BurnMusicDirectDialog(int BurnMode,FileManager MusicFiles,QWidget *parent = 0);

    ~BurnMusicDirectDialog();

private slots:
    void on_BurnMusic_clicked();

    //void on_MultiSession_clicked();

    //void on_SingleSession_clicked();

private:
    FileManager MusicFiles;
    int BurnMode;
    BurnManager *RecordManager;
    void Init();
    bool CheckIfBurnOptionsAreValid();
    Ui::BurnMusicDirectDialog *ui;
    void InitWriterSelection();
    void InitWriterRecordSpeed();
    void InitFileNameSysSelection();
};

#endif // BURNMUSICDIRECTDIALOG_H
