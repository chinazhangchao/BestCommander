#include "mainwindow.h"
#include "general.h"
#include "ui_mainwindow.h"
#include <QTableView>
#include "filelistview.h"
#include <QDebug>
#include "setting.h"

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow( parent ),
    ui( new Ui::MainWindow ),
    setting( Setting::instance() )
{
    ui->setupUi( this );
    m_pTranslator = new QTranslator(this);
    //    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(changeLanguage()));
    //    changeLanguage();

    init( );
    initAction();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeLanguage()
{
    QString qmName = m_bChinese ? "chinese.qm" : "english.qm";
    m_bChinese = !m_bChinese;
    if (m_pTranslator->load(qmName, QApplication::applicationDirPath()))
    {
        qApp->installTranslator(m_pTranslator);
        ui->retranslateUi(this);
    }
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
    ADD_ACTION_MAP( nextTabAct, Qt::META | Qt::Key_Tab, nextTabSlot )
    //参考https://bugreports.qt-project.org/browse/QTBUG-8596
    nextTabAct->setText("下一项");
    ui->menuView->addAction(nextTabAct);
    ADD_ACTION_MAP( prevTabAct, Qt::SHIFT | Qt::META | Qt::Key_Tab, prevTabSlot )
    prevTabAct->setText("上一项");
    ui->menuView->addAction(prevTabAct);
    ADD_ACTION_MAP( favoriteAct, Qt::CTRL | Qt::Key_D, favoriteSlot )
    ADD_ACTION_MAP( newTabAct, Qt::CTRL | Qt::Key_T, newTabSlot )
}

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

void MainWindow::open( SideData &sideData, FileListView &v, const QModelIndex &index )
{
    QSortFilterProxyModel *p = qobject_cast<QSortFilterProxyModel*>( v.model() );
    Q_ASSERT( p != 0 );
    FileListModel *m = qobject_cast<FileListModel*>( p->sourceModel() );
    Q_ASSERT( m != 0 );
    QFileInfo fileInfo = m->fileInfo( p->mapToSource( index ) );
    if ( fileInfo.isDir() )
    {
        m->setPath( fileInfo.canonicalFilePath() );
        v.resizeColumnsToContents();
        v.setCurrentIndex( QModelIndex( p->index( 0, 0 ) ) );
        sideData.tabWidget->setTabText( sideData.tabWidget->currentIndex(),
                                        QFileInfo( fileInfo.canonicalFilePath() ).completeBaseName() );
        sideData.addressText->setText( fileInfo.canonicalFilePath() );
    }
    else
    {
        qDebug() << "not a dir";
    }
}

void MainWindow::init()
{
    leftSide.tabWidget = ui->leftTabWidget;
    rightSide.tabWidget = ui->rightTabWidget;
    leftSide.tabWidget->clear();
    rightSide.tabWidget->clear();
    DEBUG_ASSERT( connect( leftSide.tabWidget, SIGNAL( tabBarClicked( int ) ), this, SLOT( tabBarClicked( int ) ) ) );
    DEBUG_ASSERT( connect( rightSide.tabWidget, SIGNAL( tabBarClicked( int ) ), this, SLOT( tabBarClicked( int ) ) ) );
    leftSide.addressText = ui->leftAddressText;
    rightSide.addressText = ui->rightAddressText;
    QList<QString> leftFiles;
    leftFiles = setting.getLeftTabs();

    const QString defaultPath = QDir::homePath();
    if (leftFiles.isEmpty() )
        leftFiles.append(defaultPath);

    QList<QString> rightFiles;
    rightFiles = setting.getRightTabs();
    if (rightFiles.isEmpty() )
        rightFiles.append(defaultPath);

    initViewList( leftFiles, leftSide, 0 );
    initViewList( rightFiles, rightSide, 0 );
    currentSide = &leftSide;
}

void MainWindow::activate()
{
    currentSide->tabWidget->currentWidget()->setFocus();
}

void MainWindow::initViewList( const QList<QString> &files, SideData &sideData, int currentIndex )
{
    int i = 0;
    for ( auto item : files )
    {
        QSharedPointer<ViewData> vd( new ViewData );
        vd->parentTab = sideData.tabWidget;
        initView( vd->m, vd->pm, vd->v, item );
        DEBUG_ASSERT( connect( &( vd->v ), SIGNAL( doubleClicked( const QModelIndex & ) ),
                               this, SLOT( doubleClicked( const QModelIndex & ) ) ) );
        QFileInfo fileInfo( item );
        sideData.tabWidget->addTab( &( vd->v ), fileInfo.completeBaseName() );
        vd->v.setParentTab( sideData.tabWidget );
        sideData.fileList.push_back( vd );
        if ( i == currentIndex )
        {
            sideData.addressText->setText( fileInfo.canonicalFilePath() );
        }
        ++i;
    }
}

void MainWindow::openSlot()
{
    Q_ASSERT( currentSide != nullptr );
    int cur = currentSide->tabWidget->currentIndex();
    Q_ASSERT( cur != -1 && cur < currentSide->tabWidget->count() );
    open( *currentSide, currentSide->fileList[cur]->v, currentSide->fileList[cur]->v.currentIndex() );
    activate();
}

void MainWindow::tabSlot()
{
    if ( currentSide == &leftSide )
    {
        currentSide = &rightSide;
    }
    else
    {
        currentSide = &leftSide;
    }
    activate();
}

void MainWindow::nextTabSlot()
{
    qDebug() << "NextTabSLot";
    int index = currentSide->tabWidget->currentIndex( );
    index += 1;
    index %= currentSide->tabWidget->count();
    currentSide->tabWidget->setCurrentIndex( index );
    currentSide->addressText->setText( currentSide->fileList[index]->m.currentPath() );
    activate();
}

void MainWindow::prevTabSlot()
{
    qDebug() << "prevTabSlot";
    int index = currentSide->tabWidget->currentIndex( );
    if (index == 0)
        index = currentSide->tabWidget->count() - 1;
    else
        index -= 1;

    currentSide->tabWidget->setCurrentIndex( index );
    currentSide->addressText->setText( currentSide->fileList[index]->m.currentPath() );
    activate();
}

void MainWindow::favoriteSlot()
{
    qDebug() << "favoriteSlot";
}

void MainWindow::newTabSlot()
{
    qDebug() << "newTabSlot";
}

void MainWindow::doubleClicked( const QModelIndex &index )
{
    FileListView *v = qobject_cast<FileListView*>( sender() );
    Q_ASSERT( v != 0 );
    QTabWidget *currentActiveTab = v->parentTab();
    Q_ASSERT( currentActiveTab != 0 );
    if ( currentActiveTab == leftSide.tabWidget )
    {
        currentSide = &leftSide;
    }
    else if ( currentActiveTab == rightSide.tabWidget )
    {
        currentSide = &rightSide;
    }
    open( *currentSide, *v, index );
    activate();
}

void MainWindow::tabBarClicked( int index )
{
    QTabWidget *tabWidget = qobject_cast<QTabWidget*>( sender() );
    Q_ASSERT( tabWidget != 0 );
    if ( tabWidget == leftSide.tabWidget )
    {
        currentSide = &leftSide;
    }
    else if ( tabWidget == rightSide.tabWidget )
    {
        currentSide = &rightSide;
    }
    currentSide->tabWidget->setCurrentIndex( index );
    currentSide->addressText->setText( currentSide->fileList[index]->m.currentPath() );
    activate();
}
