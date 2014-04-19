#include "mainwindow.h"
#include "general.h"
#include "ui_mainwindow.h"
#include <QTableView>
#include "filelistview.h"
#include <QDebug>
#include "setting.h"

void initView( FileListModel &model,
               QSortFilterProxyModel &proxyModel,
               FileListView &view, const QString &path )
{
    model.setPath( path );
    proxyModel.setSourceModel( &model );
    view.setModel( &proxyModel );
    view.resizeColumnsToContents();
    view.setCurrentIndex( QModelIndex( proxyModel.index( 0, 0 ) ) );
}

void open( QTabWidget *tabWidget, FileListView &v, const QModelIndex &index )
{
    QSortFilterProxyModel *p = qobject_cast<QSortFilterProxyModel*>( v.model() );
    Q_ASSERT( p != 0 );
    FileListModel *m = qobject_cast<FileListModel*>( p->sourceModel() );
    Q_ASSERT( m != 0 );
    QFileInfo fileInfo = m->fileInfo( p->mapToSource( index ) );
    //qDebug() << "canonicalFilePath:" << fileInfo.canonicalFilePath();
    if ( fileInfo.isDir() )
    {
        m->setPath( fileInfo.canonicalFilePath() );
        v.resizeColumnsToContents();
        v.setCurrentIndex( QModelIndex( p->index( 0, 0 ) ) );
        //qDebug() << "basename:" << fileInfo.baseName();
        //qDebug() << "filename:" << fileInfo.fileName();
        qDebug() << "canonicalFilePath:" << fileInfo.canonicalFilePath();
        qDebug() << "completeBaseName:" << fileInfo.completeBaseName();
        //qDebug() << "absoluteDir().dirName():" << fileInfo.absoluteDir().dirName();
        qDebug() << "dir().dirName():" << fileInfo.dir().dirName();
        qDebug() << "absolutePath():" << fileInfo.absolutePath();
        tabWidget->setTabText( tabWidget->currentIndex(), fileInfo.canonicalFilePath() );
    }
    else
    {
        qDebug() << "not a dir";
    }
}

void MainWindow::init( QTabWidget *l, QTabWidget *r )
{
    Q_ASSERT( l != nullptr && r != nullptr );
    leftTabWidget = l;
    rightTabWidget = r;
    leftTabWidget->clear();
    rightTabWidget->clear();
    QList<QString> leftFiles;
    leftFiles = setting.getLeftTabs();

    QList<QString> rightFiles;
    rightFiles = setting.getRightTabs();

    initViewList( leftFiles, *leftTabWidget , leftList );
    initViewList( rightFiles, *rightTabWidget , rightList );
    currentActiveTab = leftTabWidget;
    currentActiveTab->setFocus();
}

void MainWindow::initViewList( const QList<QString> &files, QTabWidget &tabWidget,
                                    QList<QSharedPointer<MainWindow::ViewData> > &list )
{
    for ( auto item : files )
    {
        QSharedPointer<ViewData> vd( new ViewData );
        vd->parentTab = &tabWidget;
        initView( vd->m, vd->pm, vd->v, item );
        DEBUG_ASSERT( connect( &( vd->v ), SIGNAL( doubleClicked( const QModelIndex & ) ),
                               this, SLOT( doubleClicked( const QModelIndex & ) ) ) );
        tabWidget.addTab( &( vd->v ), QFileInfo( item ).completeBaseName() );
        vd->v.setParentTab( &tabWidget );
        list.push_back( vd );
    }
}

void MainWindow::openSlot()
{
    qDebug() << "open";
    Q_ASSERT( currentActiveTab != nullptr );
    int cur = currentActiveTab->currentIndex();
    Q_ASSERT( cur != -1 && cur < currentActiveTab->count() );
    if ( currentActiveTab == leftTabWidget )
    {
        open( currentActiveTab, leftList[cur]->v, leftList[cur]->v.currentIndex() );
    }
    else if ( currentActiveTab == rightTabWidget )
    {
        open( currentActiveTab, rightList[cur]->v, rightList[cur]->v.currentIndex() );
    }
    else
    {
        qDebug() << "current tab error";
        Q_ASSERT(false);
    }
}

void MainWindow::tabSlot()
{
    if ( currentActiveTab == leftTabWidget )
    {
        currentActiveTab = rightTabWidget;
    }
    else
    {
        currentActiveTab = leftTabWidget;
    }
    currentActiveTab->currentWidget()->setFocus();
}

void MainWindow::nextTabSlot()
{

}

void MainWindow::prevTabSlot()
{

}

void MainWindow::favoriteSlot()
{

}

void MainWindow::doubleClicked( const QModelIndex &index )
{
    FileListView *v = qobject_cast<FileListView*>( sender() );
    Q_ASSERT( v != 0 );
    currentActiveTab = v->parentTab();
    Q_ASSERT( currentActiveTab != 0 );
    currentActiveTab->setFocus();
    open( currentActiveTab, *v, index );
}

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow( parent ),
    ui( new Ui::MainWindow ),
    currentActiveTab( nullptr ),
    leftCurrentIndex( -1 ),
    rightCurrentIndex( -1 ),
    setting( Setting::instance() )
{
    ui->setupUi( this );

    init( ui->leftTabWidget, ui->rightTabWidget );
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
    DEBUG_ASSERT( connect( actName, SIGNAL( triggered() ), this, SLOT( slot() ) ) );

void MainWindow::initAction()
{
    ADD_ACTION_MAP( openAct, Qt::Key_Return, openSlot )
    ADD_ACTION_MAP( tabAct, Qt::Key_Tab, tabSlot )
    ADD_ACTION_MAP( nextTabAct, Qt::CTRL| Qt::Key_Tab, nextTabSlot )
    ADD_ACTION_MAP( prevTabAct, Qt::SHIFT|Qt::CTRL| Qt::Key_Tab, prevTabSlot )
    ADD_ACTION_MAP( favoriteAct, Qt::CTRL| Qt::Key_D, favoriteSlot )
}
