#ifndef ENTRYMODEL_HPP
#define ENTRYMODEL_HPP

#include <QStringListModel>
#include <QVariant>
#include <QString>
#include <QStringList>
#include <QObject>

class DatabaseManager;

class EntryModel : public QStringListModel {
    public:
        EntryModel(QObject* parent);
        ~EntryModel();

        void insertEntry(const QString& name, const QString& category);
        bool hasEntry(const QString& name) const;

    private:
        DatabaseManager& mDatabase;
        QStringList* mEntries;
};

#endif // ENTRYMODEL_HPP
