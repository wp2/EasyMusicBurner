#-------------------------------------------------
#
# Project created by QtCreator 2016-06-16T12:22:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += console
LIBS += advapi32.lib
TARGET = Easy_Music_Burner
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    musicmodel.cpp \
    filemanager.cpp \
    burnmanager.cpp \
    burnisodialog.cpp

HEADERS  += mainwindow.h \
    musicmodel.h \
    filemanager.h \
    includeheaders.h \
    burnmanager.h \
    burnisodialog.h

FORMS    += mainwindow.ui \
    burnisodialog.ui

RESOURCES +=
