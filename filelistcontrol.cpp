#include "filelistcontrol.h"
#include <QAction>
#include <QDebug>
#include "general.h"

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

void open(FileListView &v, const QModelIndex &index )
{
    QSortFilterProxyModel *p = qobject_cast<QSortFilterProxyModel*>( v.model() );
    Q_ASSERT( p != 0 );
    FileListModel *m = qobject_cast<FileListModel*>( p->sourceModel() );
    Q_ASSERT( m != 0 );
    QFileInfo fileInfo = m->fileInfo( p->mapToSource(index ));
    qDebug() << "canonicalFilePath:" << fileInfo.canonicalFilePath();
    if ( fileInfo.isDir() )
    {
        m->setPath( fileInfo.canonicalFilePath() );
        //p->setSourceModel( m );
        //p->sort( 0 );
        //v.setModel( p );
        v.resizeColumnsToContents();
        view.setCurrentIndex( QModelIndex( proxyModel.index( 0, 0 ) ) );
    }
    else
    {
        qDebug() << "not a dir";
    }
}

FileListControl::FileListControl( QObject *parent ) :
    QObject( parent ),
    currentActiveTab( nullptr ),
    leftCurrentIndex( -1 ),
    rightCurrentIndex( -1 )
{
}

void FileListControl::init( QTabWidget *l, QTabWidget *r )
{
    Q_ASSERT( l != nullptr && r != nullptr );
    leftTabWidget = l;
    rightTabWidget = r;
    leftTabWidget->clear();
    rightTabWidget->clear();
    QStringList leftFiles;
    leftFiles.push_back( "/Users/zhangchao" );

    QStringList rightFiles;
    rightFiles.push_back( "/Users/zhangchao/books" );

    initViewList( leftFiles, *leftTabWidget , leftList );
    initViewList( rightFiles, *rightTabWidget , rightList );
    currentActiveTab = leftTabWidget;
    currentActiveTab->setFocus();
}

void FileListControl::initViewList( const QStringList &files, QTabWidget &tabWidget,
                                    QList<QSharedPointer<FileListControl::ViewData> > &list )
{
    for ( auto item : files )
    {
        QSharedPointer<ViewData> vd( new ViewData );
        initView( vd->m, vd->pm, vd->v, item );
        DEBUG_ASSERT( connect( &( vd->v ), SIGNAL( doubleClicked( const QModelIndex & ) ),
                               this, SLOT( doubleClicked( const QModelIndex & ) ) ) );
        tabWidget.addTab( &( vd->v ), item );
        list.push_back( vd );
    }
}

void FileListControl::openSlot()
{
    qDebug() << "open";
    Q_ASSERT( currentActiveTab != nullptr );
    int cur = currentActiveTab->currentIndex();
    Q_ASSERT( cur != -1 && cur < currentActiveTab->count() );
    if ( currentActiveTab == leftTabWidget )
    {
        open(leftList[cur]->v, leftList[cur]->v.currentIndex());
    }
    else if ( currentActiveTab == rightTabWidget )
    {
        open(rightList[cur]->v, rightList[cur]->v.currentIndex());
    }
    else
    {
        qDebug() << "current tab error";
    }
}

void FileListControl::doubleClicked( const QModelIndex &index )
{
    FileListView *v = qobject_cast<FileListView*>( sender() );
    Q_ASSERT( v != 0 );
    open(*v, index);
}
