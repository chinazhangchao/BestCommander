#ifndef FILELISTVIEW_H
#define FILELISTVIEW_H

#include <QTableView>

class FileListView : public QTableView
{
    Q_OBJECT
public:
    explicit FileListView( QWidget *parent = 0 );

signals:

};

#endif // FILELISTVIEW_H
