#include "filelistview.h"
#include <QHeaderView>
#include "general.h"
#include "filelistmodel.h"

FileListView::FileListView( QWidget *parent ) :
    QTableView( parent )
{
    verticalHeader()->setVisible( false );
    resizeColumnsToContents();
    setSortingEnabled( true );
    setShowGrid( false );
    setSelectionBehavior( QAbstractItemView::SelectRows );
    setSelectionMode( QAbstractItemView::ExtendedSelection );
    setEditTriggers(QAbstractItemView::SelectedClicked);
}

void FileListView::setParentTab( QTabWidget *parentTab)
{
    Q_ASSERT(parentTab != nullptr);
    parentTabWidget = parentTab;
}

QTabWidget *FileListView::parentTab()
{
    return parentTabWidget;
}
