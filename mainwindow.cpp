#include "mainwindow.h"
#include "general.h"
#include "ui_mainwindow.h"
#include <QTableView>
#include "filelistview.h"
#include <QDebug>

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow( parent ),
    ui( new Ui::MainWindow ),
    fileListControl( this )
{
    ui->setupUi( this );

    fileListControl.init( ui->leftTabWidget, ui->rightTabWidget );
    initAction();
}

MainWindow::~MainWindow()
{
    delete ui;
}

#define ADD_ACTION_MAP(actName, shortCut, slot) \
    QAction *actName = new QAction( this );\
    actName->setShortcut( shortCut );\
    addAction(actName);\
    DEBUG_ASSERT( connect( actName, SIGNAL( triggered() ), &fileListControl, SLOT( slot() ) ) );

void MainWindow::initAction()
{
    ADD_ACTION_MAP( openAct, Qt::Key_Return, openSlot )
    ADD_ACTION_MAP( tabAct, Qt::Key_Tab, tabSlot )
    ADD_ACTION_MAP( nextTabAct, Qt::CTRL| Qt::Key_Tab, nextTabSlot )
    ADD_ACTION_MAP( prevTabAct, Qt::SHIFT|Qt::CTRL| Qt::Key_Tab, prevTabSlot )
    ADD_ACTION_MAP( favoriteAct, Qt::CTRL| Qt::Key_D, favoriteSlot )
}
