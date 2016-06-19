#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QFileSystemWatcher>
#include <QTranslator>
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
    void init();
    void activate();

signals:

private slots:
    void openSlot();
    void tabSlot();
    void nextTabSlot();
    void prevTabSlot();
    void favoriteSlot();
    void newTabSlot();
    void doubleClicked(const QModelIndex &index);
    void tabBarClicked(int index);
    void changeLanguage();

private:
    struct ViewData
    {
        FileListModel m;
        QSortFilterProxyModel pm;
        FileListView v;
        QTabWidget *parentTab;
    };

    struct SideData
    {
        QTabWidget *tabWidget;
        QList<QSharedPointer<ViewData> > fileList;
        QLineEdit *addressText;
    };

    void initViewList( const QList<QString> &files,SideData &sideData, int currentIndex );
    void initAction();
    void open( SideData &sideData,
               FileListView &v, const QModelIndex &index );

    Ui::MainWindow *ui;
    SideData leftSide;
    SideData rightSide;
    SideData *currentSide;
    QFileSystemWatcher fileSystemWatcher;
    Setting &setting;
    QTranslator *m_pTranslator;
    bool m_bChinese;
};

#endif // MAINWINDOW_H
