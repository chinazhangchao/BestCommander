#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include "filelistmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    FileListModel leftModel;
    FileListModel rightModel;
    QSortFilterProxyModel leftProxyModel;
    QSortFilterProxyModel rightProxyModel;
};

#endif // MAINWINDOW_H
