#ifndef FILELISTMODEL_H
#define FILELISTMODEL_H

#include <QStandardItemModel>
#include <QDir>

class FileListModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit FileListModel( const QString &path = "", QObject *parent = 0 );
    void setPath( const QString &path );

signals:

public slots:

private:
    QDir dir;
};

#endif // FILELISTMODEL_H
