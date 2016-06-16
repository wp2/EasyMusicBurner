#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this->ui->actionUstawienia,SIGNAL(triggered(bool)),this,SLOT(OnSettings()));
    SetListView();
    this->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetListView()
{
    vector<Music*> V;
    MusicListModel = new MusicModel(V);
    this->ui->MusicFiles->setModel(MusicListModel);
}

void MainWindow::on_ADD_clicked()
{
    QFileDialog Filedial;
    Filedial.setFileMode(QFileDialog::ExistingFiles);
    if(Filedial.exec())
    {
        QStringList SelectedFiles = Filedial.selectedFiles();
        for(int i =0;i<SelectedFiles.count();i++)
        {
            QFileInfo ftmp(QFile(SelectedFiles.at(i)));
            Music *tmp = new Music(ftmp.fileName(),ftmp.absoluteFilePath(),ftmp.created().date(),ftmp.lastModified().date(),ftmp.suffix());
            MusicListModel->AddFileToList(tmp);
            //DebugMsgBox(tmp->getFormat());
        }
    }

}

void MainWindow::on_DEL_clicked()
{

    QModelIndexList ids = this->ui->MusicFiles->selectionModel()->selectedIndexes();
    for(int i = 0 ; i<ids.size();i++)
    {
        QModelIndex id = ids.at(i);
        MusicListModel->RemoveSelected(id.row());
    }


}
void MainWindow::DebugMsgBox(QString text)
{
    QMessageBox deb;
    deb.setText(text);
    deb.exec();
}



void MainWindow::on_Create_ISO_clicked()
{
    #ifdef WIN64

   // system("")
    #elif __linux__

    #endif

}

void MainWindow::OnSettings()
{
    DebugMsgBox("Ustawienia");

}
