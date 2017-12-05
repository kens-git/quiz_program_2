#include "CategoryDAO.hpp"

#include <QSqlDatabase>
#include <QSqlQuery>
// TODO: figure out why bindValue won't work without this
#include <QVariant>
#include <QQueue>

#include "DatabaseManager.hpp"
#include "Category.hpp"
#include "TreeItem.hpp"

CategoryDAO::CategoryDAO(QSqlDatabase &database)
    : mDatabase(database)
{

}

void CategoryDAO::init() const {
    if (!mDatabase.tables().contains("categories")) {
        QSqlQuery query(mDatabase);

        query.exec("CREATE TABLE categories (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, parent_category TEXT)");
        DatabaseManager::queryStatus(query);

        query.exec("INSERT INTO categories (name, parent_category) VALUES ('Root', 'null')");
        DatabaseManager::queryStatus(query);
        // TODO: remove this
//        query.exec("INSERT INTO categories (name, parent_category) VALUES ('Computer Science', 'Root')");
//        query.exec("INSERT INTO categories (name, parent_category) VALUES ('Biology', 'Root')");
//        query.exec("INSERT INTO categories (name, parent_category) VALUES ('Programming', 'Computer Science')");
//        query.exec("INSERT INTO categories (name, parent_category) VALUES ('Algorithms', 'Programming')");
//        query.exec("INSERT INTO categories (name, parent_category) VALUES ('Compilers and Interpreters', 'Computer Science')");
//        query.exec("INSERT INTO categories (name, parent_category) VALUES ('Electronics', 'Root')");
//        query.exec("INSERT INTO categories (name, parent_category) VALUES ('Circuit Analysis', 'Electronics')");
    }
}

void CategoryDAO::addCategory(const Category &category) const {
    QSqlQuery query(mDatabase);

    query.prepare("INSERT INTO categories (name, parent_category) VALUES (:name, :parent_category)");
    query.bindValue(":name", category.getName());
    query.bindValue(":parent_category", category.getParentName());

    query.exec();
    DatabaseManager::queryStatus(query);
}

void CategoryDAO::removeCategory(const QString &categoryName) const {
    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM categories WHERE name = (:name)");
    query.bindValue(":name", categoryName);
    query.exec();
    DatabaseManager::queryStatus(query);
}

QStringList* CategoryDAO::getCategoriesAsList() const {
    QSqlQuery query("SELECT * FROM categories", mDatabase);
    query.exec();
    DatabaseManager::queryStatus(query);

    QStringList* categories = new QStringList();

    while (query.next()) {
        if (query.value("name") != "Root") {
            categories->insert(0, query.value("name").toString());
        }
    }

    categories->sort();
    categories->prepend(QString("Root"));

    return categories;
}

TreeItem* CategoryDAO::getCategories() const {
    QSqlQuery query("SELECT * FROM categories", mDatabase);
    query.exec();
    DatabaseManager::queryStatus(query);

    TreeItem* rootCategory = new TreeItem(QVariant("Select Category/Entry"));

    query.next();
    // should be the root category
    rootCategory->insertChild(0, query.value("name"));

    while(query.next()) {
        QQueue<TreeItem*> queue;
        bool found = false;

        // Should be the root category
        queue.push_back(rootCategory);

        // TODO: maybe use the TreeItem.find() method instead of searching here
        while (queue.size() != 0 && found != true) {
            for (int i = 0; i < queue[0]->childCount(); i++) {
                if (queue[0]->child(i)->data(0).toString() == query.value("parent_category")) {
                    found = true;
                    queue[0]->child(i)->insertChild(queue[0]->child(i)->childCount(), query.value("name"));
                    break;
                }

                queue.push_back(queue[0]->child(i));
            }
            queue.pop_front();
        }
    }

    return rootCategory;
}
