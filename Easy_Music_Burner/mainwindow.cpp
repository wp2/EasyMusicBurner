#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
    Init();

    this->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetListView()
{
    vector<Music*> V;
    this->MusicListModel = new MusicModel(V);
    this->ui->MusicFiles->setModel(MusicListModel);
}

void MainWindow::on_ADD_clicked()
{
    if(this->ui->MemoryProgressBar->value() > this->ui->MemoryProgressBar->maximum() - 3)
    {
        QMessageBox OutOfMemory;
        OutOfMemory.setText("Przekroczyłeś dozwoloną pojemność nośnika");
        OutOfMemory.exec();
    }
    else
    {
        QFileDialog Filedial;
        Filedial.setFileMode(QFileDialog::ExistingFiles);
        if(Filedial.exec())
        {
            QStringList SelectedFiles = Filedial.selectedFiles();
            for(int i =0;i<SelectedFiles.count();i++)
            {
                QFileInfo ftmp(QFile(SelectedFiles.at(i)));
                Music *tmp = new Music(ftmp.fileName(),ftmp.absoluteFilePath(),ftmp.created().date(),ftmp.lastModified().date(),ftmp.suffix(),(ftmp.size() / 1024) / 1024);
                MusicListModel->AddFileToList(tmp);
                //DebugMsgBox(tmp->getFormat());
            }
        }
        CalculateMemoryUsage();
        this->ui->MemUsed->setText(QString::number(this->ui->MemoryProgressBar->value()));// Set Label showing current memory usage (sum of added files )
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
    CalculateMemoryUsage();
    this->ui->MemUsed->setText(QString::number(this->ui->MemoryProgressBar->value()));


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

void MainWindow::CalculateMemoryUsage()
{
    int Size = 0;
    for(int i = 0; i<this->MusicListModel->getMusic().size(); i++)
    {
        Size += this->MusicListModel->getMusic().at(i)->getFileSize();
    }
    if(Size > this->ui->MemoryProgressBar->maximum()) this->ui->MemoryProgressBar->setValue( this->ui->MemoryProgressBar->maximum() );
    else this->ui->MemoryProgressBar->setValue(Size);
}

void MainWindow::Init()
{
    connect(this->ui->BurnISO,SIGNAL(triggered(bool)),this,SLOT(OnSettings()));
    SetListView();
    SetDiscOptions();
    SetBurnModeOptions();
    SetInitMemoryBarState();
}

void MainWindow::SetDiscOptions()
{
    DiscOptions["CD-R (700 MB)"] = 700;
    DiscOptions["CD-RW (700 MB)"] = 700;
    DiscOptions["DVD-R (4.7 GB)"] = 4812;
    this->ui->DiscType->insertItem(0,"CD-R (700 MB)");
    this->ui->DiscType->insertItem(0,"CD-RW (700 MB)");
    this->ui->DiscType->insertItem(0,"DVD-R (4.7 GB)");
    connect(this->ui->DiscType,SIGNAL(currentTextChanged(QString)),this,SLOT(DiscType_Changed()));
}

void MainWindow::SetBurnModeOptions()
{
    BurnOptions["MP3"] = 1;
    this->ui->BurnMode->insertItem(0,"MP3");
}

void MainWindow::SetInitMemoryBarState()
{
    // Based on selected disc type option (CD-R) ......
    // Get current selected
    string key = this->ui->DiscType->currentText().toStdString(); // Now we have key for map
    int MemVal = DiscOptions[key];
    SetMaxMemoryAllowed(MemVal);
    this->ui->MaxMemAllowed->setText(QString::number(MemVal)); // Set Label Showing Max Memory Allowed

}

bool MainWindow::SetMaxMemoryAllowed(int MemoryMb)
{
    this->ui->MemoryProgressBar->setMaximum(MemoryMb);
    return true;
}


void MainWindow::on_Create_ISO_clicked()
{
    #ifdef _WIN32
        if(this->ui->MusicFiles->selectionModel()->selectedIndexes().count() != 0)
        {
            FileManager Fman("DDD",this->MusicListModel->getMusic());
            Fman.CreateISO();


        }
        else
        {


        }

    #elif __linux__

    #endif

}

void MainWindow::OnSettings()
{
    BurnIsoDialog IsoDialog;
}


void MainWindow::on_WriterDetect_clicked()
{
    BurnManager Bman;
    Bman.GetDiscWriters();
}

void MainWindow::on_Music_Down_clicked()
{
    if(this->ui->MusicFiles->selectionModel()->selectedIndexes().count() == 0 || this->ui->MusicFiles->selectionModel()->selectedIndexes().at(0).row()
            == this->MusicListModel->getMusic().size() -1) return;
    Music *up,*curr;
    curr = this->MusicListModel->getMusic().at(this->ui->MusicFiles->selectionModel()->selectedIndexes().at(0).row());
    up = this->MusicListModel->getMusic().at(this->ui->MusicFiles->selectionModel()->selectedIndexes().at(0).row()+1);
    this->MusicListModel->SetMusicAtPos(curr,this->ui->MusicFiles->selectionModel()->selectedIndexes().at(0).row()+1);
    this->MusicListModel->SetMusicAtPos(up,this->ui->MusicFiles->selectionModel()->selectedIndexes().at(0).row());
    QModelIndex index =this->MusicListModel->index( this->ui->MusicFiles->selectionModel()->selectedIndexes().at(0).row()+1, 0 );
    if(index.isValid())
    {
        this->ui->MusicFiles->selectionModel()->clearSelection();
        this->ui->MusicFiles->selectionModel()->select(index,QItemSelectionModel::Select );

    }
    emit this->MusicListModel->layoutChanged(); // Notify view that model has changed


}

void MainWindow::on_Music_UP_clicked()
{
    if(this->ui->MusicFiles->selectionModel()->selectedIndexes().count() == 0 || this->ui->MusicFiles->selectionModel()->selectedIndexes().at(0).row() == 0) return;
    Music *up,*curr;
    curr = this->MusicListModel->getMusic().at(this->ui->MusicFiles->selectionModel()->selectedIndexes().at(0).row());
    up = this->MusicListModel->getMusic().at(this->ui->MusicFiles->selectionModel()->selectedIndexes().at(0).row()-1);
    this->MusicListModel->SetMusicAtPos(curr,this->ui->MusicFiles->selectionModel()->selectedIndexes().at(0).row()-1);
    this->MusicListModel->SetMusicAtPos(up,this->ui->MusicFiles->selectionModel()->selectedIndexes().at(0).row());
    QModelIndex index =this->MusicListModel->index( this->ui->MusicFiles->selectionModel()->selectedIndexes().at(0).row()-1, 0 );
    if(index.isValid())
    {
        this->ui->MusicFiles->selectionModel()->clearSelection();
        this->ui->MusicFiles->selectionModel()->select(index,QItemSelectionModel::Select );

    }
    emit this->MusicListModel->layoutChanged(); //

}

void MainWindow::DiscType_Changed()
{
    // Disc opt changed check and set memory bar max value
    string key = this->ui->DiscType->currentText().toStdString();
    int MemVal = DiscOptions[key];
    SetMaxMemoryAllowed(MemVal);
    this->ui->MaxMemAllowed->setText(QString::number(MemVal));

}

void MainWindow::on_EraseDisc_triggered()
{
    EraseDiscDialog EraseDialog;
}
