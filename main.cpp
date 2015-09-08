#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QTextCodec>

int main( int argc, char *argv[] )
{
    QApplication a( argc, argv );

    // translation file for Qt
//    QTranslator qt( 0 );
//    qt.load( QString( "qt_" ) + QTextCodec::locale(), "." );
//    app.installTranslator( &qt );

    // translation file for application strings
    QTranslator myapp( 0 );
//    myapp.load( QString( "myapp_" ) + QTextCodec::locale(), "." );
    myapp.load("chinese.qm");
    a.installTranslator( &myapp );

    MainWindow w;
    w.showMaximized();
    w.activate();

    return a.exec();
}
