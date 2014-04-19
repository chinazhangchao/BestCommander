#ifndef SETTING_H
#define SETTING_H

#include <QObject>
#include <QSettings>
#include "singleton.hpp"

class Setting : public QObject, public Singleton<Setting>
{
    Q_OBJECT
protected:
    explicit Setting( QObject *parent = 0 );

    friend class Singleton<Setting>;

public:
    QList<QString> getFavorites() const;
    void removeFavorites( const QString &path );
    void addFavorites( const QString &path );
    QList<QString> getLeftTabs() const;
    QList<QString> getRightTabs() const;

signals:

public slots:

private:
    QSettings setting;
    QHash<QString, QString> favoritesHash;
    QHash<QString, QString> rightTabsHash;
    QHash<QString, QString> leftTabsHash;
    QList<QString> favorites;
    QList<QString> rightTabs;
    QList<QString> leftTabs;
};

#endif // SETTING_H
