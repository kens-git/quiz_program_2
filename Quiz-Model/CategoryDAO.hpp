#ifndef CATEGORYDAO_HPP
#define CATEGORYDAO_HPP


#include <QString>
#include <QVector>
class QSqlDatabase;

#include "Category.hpp"
class TreeItem;

class CategoryDAO {
    public:
        CategoryDAO(QSqlDatabase& database);
        void init() const;

        void addCategory(const Category& category) const;
        void removeCategory(const QString& categoryName) const;

        QStringList* getCategoriesAsList() const;
        TreeItem* getCategories() const;

    private:
        QSqlDatabase& mDatabase;
};

#endif // CATEGORYDAO_HPP
