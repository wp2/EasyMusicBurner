#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "musicmodel.h"
#include "filemanager.h"
#include "includeheaders.h"
#include "burnisodialog.h"
#include "burnmanager.h"
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

    void on_pushButton_clicked();



    void on_WriterDetect_clicked();

private:
    Ui::MainWindow *ui;
    MusicModel *MusicListModel;
    void SetListView();
    void DebugMsgBox(QString text);
    void InfoMsgBox(QString info);

};

#endif // MAINWINDOW_H
