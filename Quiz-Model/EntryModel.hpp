#ifndef ENTRYMODEL_HPP
#define ENTRYMODEL_HPP

#include <QStringListModel>
#include <QVariant>
#include <QString>
#include <QStringList>

class DatabaseManager;

class EntryModel : public QStringListModel {
    public:
        EntryModel(QObject* parent = nullptr);
        ~EntryModel();

        void insertEntry(const QString& name, const QString& category);
        bool hasEntry(const QString& name) const;

    private:
        DatabaseManager& mDatabase;
        QStringList* mEntries;
};

#endif // ENTRYMODEL_HPP
