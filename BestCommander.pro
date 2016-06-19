#-------------------------------------------------
#
# Project created by QtCreator 2016-06-19T16:27:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BestCommander
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    filelistmodel.cpp \
    filelistview.cpp \
    setting.cpp

HEADERS  += mainwindow.h \
    filelistmodel.h \
    filelistview.h \
    general.h \
    setting.h \
    singleton.hpp

FORMS += \
    mainwindow.ui
