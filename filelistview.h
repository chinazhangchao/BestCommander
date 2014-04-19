#ifndef FILELISTVIEW_H
#define FILELISTVIEW_H

#include <QTableView>

class FileListView : public QTableView
{
    Q_OBJECT
public:
    explicit FileListView( QWidget *parent = 0 );
    void setParentTab( QTabWidget *parentTab);
    QTabWidget *parentTab();

signals:

private:
    QTabWidget *parentTabWidget;
};

#endif // FILELISTVIEW_H
