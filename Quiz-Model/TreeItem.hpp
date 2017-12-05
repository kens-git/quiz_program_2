#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>
#include <QVector>

class TreeItem {
    public:
        explicit TreeItem(const QVariant& data, TreeItem* parent = nullptr);
        explicit TreeItem(const QVector<QVariant> &data, TreeItem* parent = nullptr);
        ~TreeItem();

        TreeItem* child(int number);
        int childCount() const;
        int columnCount() const;
        QVariant data(int column) const;
        bool insertChild(int position, const QVariant& data);
        bool insertChildren(int position, int count, int columns);
        bool insertColumns(int position, int columns);
        TreeItem* parent();
        bool removeChildren(int position, int count);
        bool removeColumns(int position, int columns);
        int childNumber() const;
        bool setData(int column, const QVariant &value);

        TreeItem* find(const QVariant& item);

    private:
        QList<TreeItem*> mChildItems;
        QVector<QVariant> mItemData;
        TreeItem *mParentItem;
};

#endif // TREEITEM_H


