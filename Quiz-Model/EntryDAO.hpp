#ifndef ENTRYDAO_HPP
#define ENTRYDAO_HPP

#include <QString>
#include <QVector>
#include <QPair>
class QSqlDatabase;

class EntryDAO {
    public:
        EntryDAO(QSqlDatabase& database);
        void init() const;

        void addEntry(const QString& name, const QString& category) const;
        void removeEntry(const QString& entry) const;

        QStringList* getEntries() const;
        QVector<QPair<QString, QString>> getEntriesWithCategories() const;

    private:
        QSqlDatabase& mDatabase;
};

#endif // ENTRYDAO_HPP
