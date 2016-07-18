#include "musicmodel.h"


QString Music::getFileName() const
{
    return FileName;
}

QString Music::getPath() const
{
    return Path;
}

QString Music::getFormat() const
{
    return Format;
}


int Music::getFileSize() const
{
    return FileSize;
}

Music::Music(QString FileName, QString Path)
{
    this->FileName = FileName;
    this->Path = Path;

}

Music::Music(QString FileName, QString Path, QDate Created, QDate LastModified,QString Format,int FileSize)
{
    this->FileName = FileName;
    this->Path = Path;
    this->Created = Created;
    this->LastModified = LastModified;
    this->Format = Format;
    this->FileSize = FileSize;
}

int MusicModel::rowCount(const QModelIndex &parent) const
{
    return (int)music.size();
}

QVariant MusicModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid())
        return QVariant();

    if (index.row() >= music.size())
        return QVariant();

    if (role == Qt::DisplayRole)
        return music.at(index.row())->getFileName();
    else
        return QVariant();
}

bool MusicModel::AddFileToList(Music *value)
{
    beginInsertRows(QModelIndex(),(int)music.size() + 1,(int)music.size() +1);
    music.push_back(value);
    endInsertRows();
    return true;
}

bool MusicModel::RemoveSelected(int Id)
{
    beginRemoveRows(QModelIndex(),Id,Id);
    music.erase(music.begin() + Id);
    endRemoveRows();
    return true;
}

vector<Music *> MusicModel::getMusic() const
{
    return music;
}

void MusicModel::SetMusicAtPos(Music *tmp, int Pos)
{
    if(Pos > this->music.size())return;
    this->music[Pos] = tmp;
}








