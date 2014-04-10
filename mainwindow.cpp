#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableView>
#include "filelistview.h"
#include <QDebug>

void initView( FileListModel &model,
               QSortFilterProxyModel &proxyModel,
               FileListView *view )
{
    qDebug() << "current Path:" << QDir::currentPath();
    model.setPath( QDir::currentPath() );
    proxyModel.setSourceModel( &model );
    view->setModel( &proxyModel );
    view->resizeColumnsToContents();
}
MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow( parent ),
    ui( new Ui::MainWindow )
{
    ui->setupUi( this );
    FileListView *leftView = new FileListView( this );
    FileListView *rightView = new FileListView( this );

    initView( leftModel, leftProxyModel, leftView );
    initView( rightModel, rightProxyModel, rightView );
    ui->leftTabWidget->clear();
    ui->leftTabWidget->addTab( leftView, QDir::currentPath() );
    ui->rightTabWidget->clear();
    ui->rightTabWidget->addTab( rightView, QDir::currentPath() );
}

MainWindow::~MainWindow()
{
    delete ui;
}

