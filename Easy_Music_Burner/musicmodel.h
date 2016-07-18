#ifndef MUSICMODEL_H
#define MUSICMODEL_H
#include "includeheaders.h"
using namespace std;

class Music
{

    QString FileName;
    QString Path;
    QDate Created;
    QDate LastModified;
    QString Format;
    int FileSize;
public:
    Music(QString FileName,QString Path);
    Music(QString FileName, QString Path,QDate Created,QDate LastModified,QString Format,int FileSize);

public:
    QString getFileName() const;
    QString getPath() const;
    QString getFormat() const;

    int getFileSize() const;
};

class MusicModel : public QAbstractListModel
{
    Q_OBJECT;
public:

    MusicModel(vector<Music*> &Music, QObject *parent = 0) : QAbstractListModel(parent) {this->music = Music;};

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role) const;

    bool AddFileToList(Music* value);

    bool RemoveSelected(int Id);


    vector<Music *> getMusic() const;

    void SetMusicAtPos(Music *tmp,int Pos);

private:
    vector<Music*> music;
};

#endif // MUSICMODEL_H
