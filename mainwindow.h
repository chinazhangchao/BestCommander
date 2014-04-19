#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QFileSystemWatcher>
#include "filelistmodel.h"
#include "filelistview.h"

namespace Ui
{
class MainWindow;
}

class Setting;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow( QWidget *parent = 0 );
    ~MainWindow();
    void init(QTabWidget *leftTabWidget, QTabWidget *rightTabWidget);
signals:

public slots:
    void openSlot();
    void tabSlot();
    void nextTabSlot();
    void prevTabSlot();
    void favoriteSlot();

private slots:
    void doubleClicked(const QModelIndex &index);

private:
    struct ViewData
    {
        FileListModel m;
        QSortFilterProxyModel pm;
        FileListView v;
        QTabWidget *parentTab;
    };

    void initViewList( const QList<QString> &files, QTabWidget &tabWidget,
                       QList<QSharedPointer<ViewData> >& );
    void initAction();

    Ui::MainWindow *ui;
    QTabWidget *currentActiveTab;
    QTabWidget *leftTabWidget;
    QTabWidget *rightTabWidget;
    QList<QSharedPointer<ViewData> > leftList;
    int leftCurrentIndex;
    QList<QSharedPointer<ViewData> > rightList;
    int rightCurrentIndex;
    QFileSystemWatcher fileSystemWatcher;
    Setting &setting;
};

#endif // MAINWINDOW_H
