#include "mainwindow.h"
#include <QApplication>

int main( int argc, char *argv[] )
{
    QApplication a( argc, argv );
    MainWindow w;
    w.showMaximized();
    w.activate();

    return a.exec();
}
