#-------------------------------------------------
#
# Project created by QtCreator 2014-04-05T09:01:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BestCommander
TEMPLATE = app
#QMAKE_CXXFLAGS += -std=c++11 -mmacosx-version-min=10.7
QMAKE_CXXFLAGS += -mmacosx-version-min=10.7 -std=gnu0x -stdlib=libc+
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    filelistview.cpp \
    filelistmodel.cpp \
    setting.cpp

HEADERS  += mainwindow.h \
    filelistview.h \
    filelistmodel.h \
    general.h \
    setting.h \
    singleton.hpp

FORMS    += mainwindow.ui
