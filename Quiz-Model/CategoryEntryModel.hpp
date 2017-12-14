#ifndef CATEGORYENTRYMODEL_HPP
#define CATEGORYENTRYMODEL_HPP

#include <QAbstractListModel>
#include <QModelIndex>
#include <QVariant>

#include "quiz-model_global.h"

class TreeItem;
class DatabaseManager;

// TODO: fix that invalid index error when switching tabs
class QUIZMODELSHARED_EXPORT CategoryEntryModel : public QAbstractItemModel {
    public:
        CategoryEntryModel(QObject* parent = nullptr);
        ~CategoryEntryModel();

        QVariant data(const QModelIndex &index, int role) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

        QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
        QModelIndex parent(const QModelIndex &index) const override;

        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        int columnCount(const QModelIndex &parent = QModelIndex()) const override;

        Qt::ItemFlags flags(const QModelIndex &index) const override;
        bool setHeaderData(int section, Qt::Orientation orientation,
                           const QVariant &value, int role = Qt::EditRole) override;

        void loadCategories();

    private:
        DatabaseManager& mDatabase;
        TreeItem* mRootCategory;

        TreeItem* getItem(const QModelIndex &index) const;
};

#endif // CATEGORYENTRYMODEL_HPP
