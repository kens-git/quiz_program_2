#include "DatabaseManager.hpp"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDebug>

DatabaseManager& DatabaseManager::instance() {
#if defined(Q_OS_ANDROID)
    // Overwrite the previous version of the database to ensure it's up-to-date with the current db version
    QFile file("./" + DB_FILENAME);
    file.remove();
    QFile::copy(":/" + DB_FILENAME, "./" + DB_FILENAME);
    QFile::setPermissions("./" + DB_FILENAME, QFile::WriteOwner | QFile::ReadOwner);

    static DatabaseManager singleton(DB_FILENAME);
#else
    static DatabaseManager singleton;
#endif
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
