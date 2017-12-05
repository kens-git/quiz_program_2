#include "CategoryEntryModel.hpp"

#include <QVector>
#include <QVectorIterator>

#include "DatabaseManager.hpp"
#include "TreeItem.hpp"

CategoryEntryModel::CategoryEntryModel(QObject* parent) :
    QAbstractItemModel(parent),
    mDatabase(DatabaseManager::instance())
{
    mRootCategory = new TreeItem(QVariant("Root"));
    loadCategories();
}

CategoryEntryModel::~CategoryEntryModel() {
    // TODO: memory leak, mRootCategory's children aren't being deleted.
    // This won't run until the end of the program anyway, so it's not a vital fix
    delete mRootCategory;
    mRootCategory = nullptr;
}

int CategoryEntryModel::columnCount(const QModelIndex &parent) const {
    return mRootCategory->columnCount();
}

QVariant CategoryEntryModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    if (role != Qt::DisplayRole && role != Qt::EditRole) {
        return QVariant();
    }

    TreeItem* categoryItem = getItem(index);
    return categoryItem->data(index.column());
}

Qt::ItemFlags CategoryEntryModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) {
        return 0;
    }

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

TreeItem* CategoryEntryModel::getItem(const QModelIndex& index) const {
    if (index.isValid()) {
        TreeItem* categoryItem = static_cast<TreeItem*>(index.internalPointer());
        if (categoryItem) {
            return categoryItem;
        }
    }

    return mRootCategory;
}

QVariant CategoryEntryModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return mRootCategory->data(section);
    }

    return QVariant();
}

QModelIndex CategoryEntryModel::index(int row, int column, const QModelIndex &parent) const {
    if (parent.isValid() && parent.column() != 0) {
        return QModelIndex();
    }

    TreeItem *parentItem = getItem(parent);

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex CategoryEntryModel::parent(const QModelIndex &index) const {
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = getItem(index);
    TreeItem *parentItem = childItem->parent();

    if (parentItem->data(0) == mRootCategory->data(0))
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}

int CategoryEntryModel::rowCount(const QModelIndex &parent) const {
    TreeItem *parentItem = getItem(parent);

    return parentItem->childCount();
}

bool CategoryEntryModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role) {
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    bool result = mRootCategory->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}

void CategoryEntryModel::loadCategories() {
    beginInsertRows(QModelIndex(), 0, mRootCategory->childCount());
    mRootCategory = mDatabase.mCategoryDAO.getCategories();
    QVector<QPair<QString, QString>> entries = mDatabase.mEntryDAO.getEntriesWithCategories();

    QVectorIterator<QPair<QString, QString>> iter(entries);
    while (iter.hasNext()) {
        QPair<QString, QString> entry = iter.next();
        TreeItem* entryCategory = mRootCategory->find(entry.second);
        if (entryCategory != nullptr) {
            entryCategory->insertChild(entryCategory->childCount(), entry.first);
        }
    }
    endInsertRows();
}
