#include "mainwindow.h"
#include "ui_mainwindow.h"

void initView(QFileSystemModel &model,
                          QSortFilterProxyModel &proxyModel,
                          QTableView *view)
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
    initView(leftModel, leftProxyModel, ui->leftView);
    initView(rightModel, rightProxyModel, ui->rightView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

