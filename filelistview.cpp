#include "filelistview.h"
#include <QHeaderView>

FileListView::FileListView(QWidget *parent) :
    QTableView(parent)
{
    verticalHeader()->setVisible(false);
    resizeColumnsToContents();
    setSortingEnabled(true);
    setShowGrid(false);
}
