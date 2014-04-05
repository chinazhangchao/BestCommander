#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QSortFilterProxyModel>

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
    QFileSystemModel leftModel;
    QFileSystemModel rightModel;
    QSortFilterProxyModel leftProxyModel;
    QSortFilterProxyModel rightProxyModel;
};

#endif // MAINWINDOW_H
