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
