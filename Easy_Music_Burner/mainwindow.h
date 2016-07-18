#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "musicmodel.h"
#include "filemanager.h"
#include "includeheaders.h"
#include "burnisodialog.h"
#include "burnmanager.h"
#include "erasediscdialog.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_ADD_clicked();

    void on_DEL_clicked();

    void on_Create_ISO_clicked();

    void OnSettings();

    void on_WriterDetect_clicked();

    void on_Music_Down_clicked();

    void on_Music_UP_clicked();

    void DiscType_Changed();

    void on_EraseDisc_triggered();

private:
    Ui::MainWindow *ui;
    MusicModel *MusicListModel;
    map<string,int> DiscOptions; // Temporary Solution thinking of better way to do this
    map<string,int> BurnOptions;
    void SetListView();
    void DebugMsgBox(QString text);
    void InfoMsgBox(QString info);
    bool CheckFreeSpace();
    void CalculateMemoryUsage();
    void Init();
    void SetDiscOptions();
    void SetBurnModeOptions();
    void SetInitMemoryBarState();
    bool SetMaxMemoryAllowed(int MemoryMb);

};

#endif // MAINWINDOW_H
