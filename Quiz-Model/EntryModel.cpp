#include "EntryModel.hpp"

#include "DatabaseManager.hpp"

EntryModel::EntryModel(QObject* parent)
    : QStringListModel(parent),
      mDatabase(DatabaseManager::instance()),
      mEntries(mDatabase.mEntryDAO.getEntries())
{
    setStringList(*mEntries);
}

EntryModel::~EntryModel() {
    delete mEntries;
    mEntries = nullptr;
}

void EntryModel::insertEntry(const QString &name, const QString &category) {
    mDatabase.mEntryDAO.addEntry(name, category);
    // TODO: have addEntry return true/false
    mEntries->push_back(name);
    mEntries->sort(Qt::CaseSensitive);

    setStringList(*mEntries);
}

bool EntryModel::hasEntry(const QString &name) const {
    if (mEntries->contains(name, Qt::CaseInsensitive)) {
        return true;
    }
    return false;
}
