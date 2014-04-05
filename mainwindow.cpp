#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fileinfo.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    FileInfo *p = new FileInfo;
    ui->leftView->setModel(p);
}

MainWindow::~MainWindow()
{
    delete ui;
}
