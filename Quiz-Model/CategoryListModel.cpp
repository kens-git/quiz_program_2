#include "CategoryListModel.hpp"

#include "DatabaseManager.hpp"

CategoryListModel::CategoryListModel(QObject *parent)
    : QStringListModel(parent),
      mDatabase(DatabaseManager::instance()),
      mCategories(mDatabase.mCategoryDAO.getCategoriesAsList())
{

}

CategoryListModel::~CategoryListModel() {
    delete mCategories;
    mCategories = nullptr;
}

QVariant CategoryListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    return mCategories->at(index.row());
}

int CategoryListModel::rowCount(const QModelIndex &parent) const {
    return mCategories->size();
}

void CategoryListModel::insertCategory(const QString &name, const QString& parentName) {
    // TODO: this doesn't work, please use QStringListModel, future self
    unsigned int index = 0;
    for (unsigned int i = 0; i < mCategories->size(); i++) {
        if (name >= mCategories->at(i)) {
            index = i;
        }
    }

    beginInsertRows(QModelIndex(), index, index);
    mDatabase.mCategoryDAO.addCategory(Category(name, parentName));
    // TODO: have addCategory return true/false on success/failure, and don't insert the name if the query fails
    mCategories->insert(index, name);
    endInsertRows();
}

bool CategoryListModel::hasCategory(const QString &name) {
    if (mCategories->contains(name, Qt::CaseInsensitive)) {
        return true;
    }
    return false;
}
