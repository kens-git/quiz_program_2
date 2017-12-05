#include "DatabaseManager.hpp"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

DatabaseManager& DatabaseManager::instance() {
    static DatabaseManager singleton;
    return singleton;
}

DatabaseManager::~DatabaseManager() {
    mDatabase->close();
    delete mDatabase;
    mDatabase = nullptr;
}

DatabaseManager::DatabaseManager(const QString &filepath)
    : mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))),
      mCategoryDAO(*mDatabase),
      mEntryDAO(*mDatabase),
      mQuestionDAO(*mDatabase)
{
    mDatabase->setDatabaseName(filepath);
    mDatabase->open();

    QSqlQuery query(*mDatabase);

    if (!mDatabase->contains("entries")) {
        query.exec("CREATE TABLE entries (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, category TEXT)");
    }
    if (!mDatabase->contains("questions")) {
        query.exec("CREATE TABLE questions (id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "question_text TEXT, answer_text TEXT, book TEXT");
    }

    mCategoryDAO.init();
    mEntryDAO.init();
    mQuestionDAO.init();
}

void DatabaseManager::queryStatus(const QSqlQuery &query) {
    if (!query.lastError().type() == QSqlError::ErrorType::NoError) {
       qWarning() << "Error while executing:";
       qWarning() << query.lastQuery();
       qWarning() << query.lastError().text();
    }
}
