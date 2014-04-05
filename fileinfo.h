#ifndef FILEINFO_H
#define FILEINFO_H

#include <QAbstractListModel>

class FileInfo : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit FileInfo(QObject *parent = 0);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool removeRows(int row, int count, const QModelIndex &parent);

    bool dropMimeData(const QMimeData *data, Qt::DropAction action,
                      int row, int column, const QModelIndex &parent);
    QMimeData *mimeData(const QModelIndexList &indexes) const;
    QStringList mimeTypes() const;
    int rowCount(const QModelIndex &parent) const;
    Qt::DropActions supportedDropActions() const;

    void addPiece(const QPixmap &pixmap, const QPoint &location);
    void addPieces(const QPixmap& pixmap);
signals:

public slots:

};

#endif // FILEINFO_H
