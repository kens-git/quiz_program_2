#ifndef CATEGORYLISTMODEL_HPP
#define CATEGORYLISTMODEL_HPP

#include <QStringListModel>
#include <QVariant>
#include <QStringList>
#include <QString>

class DatabaseManager;

class CategoryListModel : public QStringListModel {
    public:
        CategoryListModel(QObject* parent = nullptr);
        ~CategoryListModel();

        void insertCategory(const QString& name, const QString& parentName);
        bool hasCategory(const QString& name);

    private:
        DatabaseManager& mDatabase;
        QStringList* mCategories;
};

#endif // CATEGORYLISTMODEL_HPP
