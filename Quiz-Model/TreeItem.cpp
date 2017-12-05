#include "TreeItem.hpp"

#include <QStringList>
#include <QQueue>

TreeItem::TreeItem(const QVariant &data, TreeItem *parent) {
    mParentItem = parent;
    mItemData.push_back(data);
}

TreeItem::TreeItem(const QVector<QVariant> &data, TreeItem *parent) {
    mParentItem = parent;
    mItemData = data;
}

TreeItem::~TreeItem() {
    qDeleteAll(mChildItems);
}

TreeItem *TreeItem::child(int number) {
    return mChildItems.value(number);
}

int TreeItem::childCount() const {
    return mChildItems.count();
}

int TreeItem::childNumber() const {
    if (mParentItem)
        return mParentItem->mChildItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}

int TreeItem::columnCount() const {
    return mItemData.count();
}

QVariant TreeItem::data(int column) const {
    return mItemData.value(column);
}

bool TreeItem::insertChild(int position, const QVariant &data) {
    if (position < 0 || position > mChildItems.size())
        return false;

        TreeItem *item = new TreeItem(data, this);
        mChildItems.insert(position, item);

    return true;
}

bool TreeItem::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > mChildItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        QVector<QVariant> data(columns);
        TreeItem *item = new TreeItem(data, this);
        mChildItems.insert(position, item);
    }

    return true;
}

bool TreeItem::insertColumns(int position, int columns) {
    if (position < 0 || position > mItemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        mItemData.insert(position, QVariant());

    foreach (TreeItem *child, mChildItems)
        child->insertColumns(position, columns);

    return true;
}

TreeItem *TreeItem::parent()
{
    return mParentItem;
}

bool TreeItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > mChildItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete mChildItems.takeAt(position);

    return true;
}

bool TreeItem::removeColumns(int position, int columns)
{
    if (position < 0 || position + columns > mItemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        mItemData.remove(position);

    foreach (TreeItem *child, mChildItems)
        child->removeColumns(position, columns);

    return true;
}

bool TreeItem::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= mItemData.size())
        return false;

    mItemData[column] = value;
    return true;
}

TreeItem* TreeItem::find(const QVariant &item) {
    TreeItem* foundItem = nullptr;
    QQueue<TreeItem*> queue;
    bool found = false;

    queue.push_back(this);

    while (queue.size() != 0 && found != true) {
        for (int i = 0; i < queue[0]->childCount(); i++) {
            if (queue[0]->child(i)->data(0).toString() == item.toString()) {
                found = true;
                foundItem = queue[0]->child(i);
                break;
            }

            queue.push_back(queue[0]->child(i));
        }
        queue.pop_front();
    }

    return foundItem;
}
