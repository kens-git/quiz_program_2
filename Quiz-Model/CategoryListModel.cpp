#include "CategoryListModel.hpp"

#include "DatabaseManager.hpp"

CategoryListModel::CategoryListModel(QObject *parent)
    : QStringListModel(parent),
      mDatabase(DatabaseManager::instance()),
      mCategories(mDatabase.mCategoryDAO.getCategoriesAsList())
{
    setStringList(*mCategories);
}

CategoryListModel::~CategoryListModel() {
    delete mCategories;
    mCategories = nullptr;
}

void CategoryListModel::insertCategory(const QString &name, const QString& parentName) {
    unsigned int index = 0;
    for (unsigned int i = 0; i < mCategories->size(); i++) {
        if (name >= mCategories->at(i)) {
            index = i;
        }
    }

    mDatabase.mCategoryDAO.addCategory(Category(name, parentName));
    // TODO: have addCategory return true/false on success/failure, and don't insert the name if the query fails
    mCategories->insert(index, name);

    setStringList(*mCategories);
}

bool CategoryListModel::hasCategory(const QString &name) {
    if (mCategories->contains(name, Qt::CaseInsensitive)) {
        return true;
    }
    return false;
}
