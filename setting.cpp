#include "setting.h"
#include <QDebug>
#include <QDir>

template<typename T> QHash<QString, T> GetGroupKeyValues(QSettings &setting, const QString &group)
{
    QHash<QString, T> hash;
    setting.beginGroup(group);
    QStringList keys = setting.childKeys();
    for (auto item : keys)
    {
        QVariant val = setting.value(item);
        if (!val.isNull())
        {
            hash.insert(item, val.value<T>());
        }
    }
    setting.endGroup();
    return hash;
}

Setting::Setting(QObject *parent) :
    QObject(parent),
    setting("./bestcommander.ini", QSettings::IniFormat)
{
    qDebug() << "current path:" << QDir::currentPath();
    favoritesHash = GetGroupKeyValues<QString>(setting, "Favorites");
    favorites = favoritesHash.values();
    leftTabsHash = GetGroupKeyValues<QString>(setting, "LeftTabs");
    leftTabs = leftTabsHash.values();
    rightTabsHash = GetGroupKeyValues<QString>(setting, "RightTabs");
    rightTabs = rightTabsHash.values();
}

QList<QString> Setting::getFavorites() const
{
    return favorites;
}

void Setting::removeFavorites(const QString &path)
{
    Q_ASSERT(!path.isEmpty());
    favorites.removeOne(path);
}

void Setting::addFavorites(const QString &path)
{
    Q_ASSERT(!path.isEmpty());
    favorites.push_back(path);
}

QList<QString> Setting::getLeftTabs() const
{
    return leftTabs;
}

QList<QString> Setting::getRightTabs() const
{
    return rightTabs;
}
