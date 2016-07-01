#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this->ui->BurnISO,SIGNAL(triggered(bool)),this,SLOT(OnSettings()));
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

void MainWindow::InfoMsgBox(QString message)
{
    QMessageBox info;
    info.setText(message);
    info.exec();
}


void MainWindow::on_Create_ISO_clicked()
{
    #ifdef _WIN32
        if(this->ui->MusicFiles->selectionModel()->selectedIndexes().count() != 0)
        {
           // InfoMsgBox("Nie wybrałeś plików!");
           // return;
        }
        else
        {
           /* QDialog StatusDial;
            QLayout *layout = new QVBoxLayout(&StatusDial);
            QProgressBar *prog = new QProgressBar();
            prog->setMinimum(0);
            prog->setMaximum(0);
            layout->addWidget(prog);
            if(StatusDial.exec())
            {
                FileManager man("C:\Users\Wojtek\Documents\EMBTest",this->MusicListModel->getMusic());
                if(man.CreateISO()) StatusDial.close();
            }*/
            FileManager man("C:/Users/Wojtek/Documents/EMBTest",this->MusicListModel->getMusic());
            man.CreateISO();

        }

    #elif __linux__

    #endif

}

void MainWindow::OnSettings()
{
    BurnIsoDialog IsoDialog;


}

void MainWindow::on_pushButton_clicked()
{
    // Test of progress bar
    QDialog StatusDial;
    QLayout *layout = new QVBoxLayout(&StatusDial);
    QProgressBar *prog = new QProgressBar();
    prog->setMinimum(0);
    prog->setMaximum(0);
    layout->addWidget(prog);
    StatusDial.exec();
}

void MainWindow::on_WriterDetect_clicked()
{
    BurnManager Bman;
    Bman.GetDiscWriters();
}
