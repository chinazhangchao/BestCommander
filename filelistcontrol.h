#ifndef FILELISTCONTROL_H
#define FILELISTCONTROL_H

#include <QObject>
#include <QSortFilterProxyModel>
#include <QFileSystemWatcher>
#include "filelistmodel.h"
#include "filelistview.h"

class FileListControl : public QObject
{
    Q_OBJECT
public:
    explicit FileListControl( QObject *parent = 0 );

    void init(QTabWidget *leftTabWidget, QTabWidget *rightTabWidget);
signals:

public slots:
    void openSlot();

private slots:
    void doubleClicked(const QModelIndex &index);

private:
    struct ViewData
    {
        FileListModel m;
        QSortFilterProxyModel pm;
        FileListView v;
    };

    void initViewList( const QStringList &files, QTabWidget &tabWidget,
                       QList<QSharedPointer<ViewData> >& );

    QTabWidget *currentActiveTab;
    QTabWidget *leftTabWidget;
    QTabWidget *rightTabWidget;
    QList<QSharedPointer<ViewData> > leftList;
    int leftCurrentIndex;
    QList<QSharedPointer<ViewData> > rightList;
    int rightCurrentIndex;
    QFileSystemWatcher fileSystemWatcher;
};

#endif // FILELISTCONTROL_H
