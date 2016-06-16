#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "musicmodel.h"
#include <QFileDialog>
#include <QMessageBox>
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

private:
    Ui::MainWindow *ui;
    MusicModel *MusicListModel;
    void SetListView();
    void DebugMsgBox(QString text);


};

#endif // MAINWINDOW_H
