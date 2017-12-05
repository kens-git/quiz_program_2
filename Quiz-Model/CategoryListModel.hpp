#ifndef CATEGORYLISTMODEL_HPP
#define CATEGORYLISTMODEL_HPP

#include <QStringListModel>
#include <QVariant>
#include <QStringList>
#include <QString>

class DatabaseManager;

class CategoryListModel : public QStringListModel {
    public:
        CategoryListModel(QObject* parent);
        ~CategoryListModel();

        // TODO: remove these, probably don't need them, use setStringList()
        QVariant data(const QModelIndex &index, int role) const override;
        int rowCount(const QModelIndex &parent) const override;

        void insertCategory(const QString& name, const QString& parentName);
        bool hasCategory(const QString& name);

    private:
        DatabaseManager& mDatabase;
        QStringList* mCategories;
};

#endif // CATEGORYLISTMODEL_HPP
