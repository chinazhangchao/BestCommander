#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableView>
#include "filelistview.h"

void initView(QFileSystemModel &model,
                          QSortFilterProxyModel &proxyModel,
                          FileListView *view)
{
    model.setRootPath(QDir::currentPath());
    proxyModel.setSourceModel(&model);
    view->setModel(&proxyModel);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    FileListView *leftView = new FileListView(this);
    FileListView *rightView= new FileListView(this);

    initView(leftModel, leftProxyModel, leftView);
    initView(rightModel, rightProxyModel, rightView);
    ui->leftTabWidget->clear();
    ui->leftTabWidget->addTab(leftView, QDir::currentPath());
    ui->rightTabWidget->clear();
    ui->rightTabWidget->addTab(rightView, QDir::currentPath());
}

MainWindow::~MainWindow()
{
    delete ui;
}

