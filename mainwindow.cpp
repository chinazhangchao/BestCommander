#include "mainwindow.h"
#include "general.h"
#include "ui_mainwindow.h"
#include <QTableView>
#include "filelistview.h"
#include <QDebug>

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow( parent ),
    ui( new Ui::MainWindow ),
    fileListControl(this)
{
    ui->setupUi( this );
    fileListControl.init( ui->leftTabWidget, ui->rightTabWidget);
    initAction();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initAction()
{
    QAction *openAct = new QAction( this );
    openAct->setShortcut( Qt::Key_Return );
    openAct->setShortcutContext(Qt::ApplicationShortcut);
    addAction(openAct);
    DEBUG_ASSERT( connect( openAct, SIGNAL( triggered() ), &fileListControl, SLOT( openSlot() ) ) );
}
