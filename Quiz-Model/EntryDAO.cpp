#include "EntryDAO.hpp"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QStringList>

#include "DatabaseManager.hpp"

EntryDAO::EntryDAO(QSqlDatabase& database)
    : mDatabase(database)
{

}

void EntryDAO::init() const {
    if (!mDatabase.tables().contains("entries")) {
        QSqlQuery query(mDatabase);

        query.exec("CREATE TABLE entries (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, category TEXT)");

        DatabaseManager::queryStatus(query);
    }
}

void EntryDAO::addEntry(const QString& name, const QString& category) const {
    QSqlQuery query(mDatabase);

    query.prepare("INSERT INTO entries (name, category) VALUES (:name, :category)");
    query.bindValue(":name", name);
    query.bindValue(":category", category);

    query.exec();
    DatabaseManager::queryStatus(query);
}

void EntryDAO::removeEntry(const QString &name) const {
    QSqlQuery query(mDatabase);

    query.prepare("DELETE FROM entries WHERE name = (:name)");
    query.bindValue(":name", name);

    query.exec();
    DatabaseManager::queryStatus(query);
}

QStringList* EntryDAO::getEntries() const {
    QSqlQuery query("SELECT * FROM entries", mDatabase);
    DatabaseManager::queryStatus(query);

    QStringList* entries = new QStringList();

    while (query.next()) {
        entries->push_back(query.value("name").toString());
    }

    entries->sort();

    return entries;
}

QVector<QPair<QString, QString>> EntryDAO::getEntriesWithCategories() const {
    QSqlQuery query("SELECT * FROM entries");
    DatabaseManager::queryStatus(query);

    QVector<QPair<QString, QString>> entries;

    while(query.next()) {
        entries.push_back(QPair<QString, QString>(QString(query.value("name").toString()),
                                        QString(query.value("category").toString())));
    }

    return entries;
}
