#ifndef INCLUDEHEADERS_H
#define INCLUDEHEADERS_H

#include <QPlainTextEdit>
#include <QDialog>
#include <QProcess>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QString>
#include <iostream>
#include <QDate>
#include <vector>
#include <QTemporaryDir>
#include <QCoreApplication>
#include <QAbstractListModel>
#include <QThread>
#include <regex>
#include <cstdlib>
#include <map>
#ifdef _WIN32
#include <Windows.h>
#endif
// ENUM CODES HERE


enum DiscTypeCode
{
    CDR = 1,
    CDRW = 2,
    DVDR = 3,
    DVDRW = 4
};

enum BurnTypeCode
{
    MP3 = 100,
    AUDIOCD
};

using namespace std;
#endif // INCLUDEHEADERS_H
