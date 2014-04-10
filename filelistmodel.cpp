#include "filelistmodel.h"
#include <QStringList>
#include <QMessageBox>
#include <QFileInfo>
#include <QList>
#include <QDateTime>
#include <QDebug>

FileListModel::FileListModel( const QString &path, QObject *parent ) :
    QStandardItemModel( parent )
{
    if ( !path.isEmpty() )
    {
        setPath( path );
    }
}

void FileListModel::setPath( const QString &path )
{
    dir.setPath( path );
    if ( !dir.exists() )
    {
        QMessageBox::information( nullptr, tr( "info" ), tr( "Dir Not Exist!" ) );
        return;
    }
    QStringList columnLabels;
    columnLabels.push_back( tr( "Name" ) );
    columnLabels.push_back( tr( "Size" ) );
    columnLabels.push_back( tr( "Kind" ) );
    columnLabels.push_back( tr( "Date Modified" ) );
    setHorizontalHeaderLabels( columnLabels );
    QList<QFileInfo> fileList = dir.entryInfoList();
    int rowCount = 0;
    for ( const QFileInfo &entry : fileList )
    {
        qDebug() << "entry.baseName:" << entry.baseName();
        qDebug() << "entry.fileName:" << entry.fileName();
        qDebug() << "entry.filePath:" << entry.filePath();
        qDebug() << "entry.size:" << entry.size();
        qDebug() << "entry.suffix:" << entry.suffix();
        qDebug() << "entry.lastModified:" << entry.lastModified().toString();
        QString fileName = entry.fileName();
        if ( fileName == "." )
        {
            continue;
        }
        QStandardItem *c1 = new QStandardItem( entry.fileName() );
        QStandardItem *c2 = new QStandardItem( entry.size() );
        QStandardItem *c3 = new QStandardItem( entry.suffix() );
        QStandardItem *c4 = new QStandardItem( entry.lastModified().toString() );

        setItem( rowCount, 0, c1 );
        setItem( rowCount, 1, c2 );
        setItem( rowCount, 2, c3 );
        setItem( rowCount, 3, c4 );

        ++rowCount;
    }
}
