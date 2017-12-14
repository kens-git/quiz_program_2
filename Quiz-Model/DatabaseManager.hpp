#ifndef DATABASEMANAGER_HPP
#define DATABASEMANAGER_HPP

#include <QString>
#include <QVector>
class QSqlDatabase;
class QSqlQuery;

#include "CategoryDAO.hpp"
#include "EntryDAO.hpp"
#include "QuestionDAO.hpp"

const QString DB_FILENAME = "quiz_database.db";

class DatabaseManager {
    public:
        static DatabaseManager& instance();
        ~DatabaseManager();

        static void queryStatus(const QSqlQuery& query);

    protected:
        DatabaseManager(const QString& filepath = DB_FILENAME);
        DatabaseManager& operator=(const DatabaseManager& rhs);

    private:
        QSqlDatabase* mDatabase;

    public:
        // these are declared down here because the DAOs need to be initialized after mDatabase
        const CategoryDAO mCategoryDAO;
        const EntryDAO mEntryDAO;
        const QuestionDAO mQuestionDAO;
};

#endif // DATABASEMANAGER_HPP
