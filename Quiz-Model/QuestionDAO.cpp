#include "QuestionDAO.hpp"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

#include "DatabaseManager.hpp"
#include "Question.hpp"

QuestionDAO::QuestionDAO(QSqlDatabase& database)
    : mDatabase(database)
{

}

void QuestionDAO::init() const {
    if (!mDatabase.tables().contains("questions")) {
        QSqlQuery query(mDatabase);

        query.exec("CREATE TABLE questions (id INTEGER PRIMARY KEY AUTOINCREMENT, question TEXT, answer TEXT, entry_name TEXT)");

        DatabaseManager::queryStatus(query);
    }
}

unsigned int QuestionDAO::addQuestion(const QString& question, const QString& answer, const QString& entryName) const {
    QSqlQuery query(mDatabase);

    query.prepare("INSERT INTO questions (question, answer, entry_name) VALUES (:question, :answer, :entry_name)");
    query.bindValue(":question", question);
    query.bindValue(":answer", answer);
    query.bindValue(":entry_name", entryName);

    query.exec();
    DatabaseManager::queryStatus(query);

    // TODO: verify that the query was successful before returning the id
    return query.lastInsertId().toInt();
}

void QuestionDAO::updateQuestionText(const QString &question, unsigned int id) const {
    QSqlQuery query(mDatabase);

    query.prepare("UPDATE questions SET question = (:question) WHERE id = (:id)");
    query.bindValue(":question", question);
    query.bindValue(":id", id);
    query.exec();
    DatabaseManager::queryStatus(query);
}

void QuestionDAO::updateAnswerText(const QString &answer, unsigned int id) const {
    QSqlQuery query(mDatabase);

    query.prepare("UPDATE questions SET answer = (:answer) WHERE id = (:id)");
    query.bindValue(":answer", answer);
    query.bindValue(":id", id);
    query.exec();
    DatabaseManager::queryStatus(query);
}

void QuestionDAO::removeQuestion(unsigned int id) const {
    QSqlQuery query(mDatabase);

    query.prepare("DELETE FROM questions WHERE id = (:id)");
    query.bindValue(":id", id);

    query.exec();
    DatabaseManager::queryStatus(query);
}

QVector<QPair<unsigned int, Question>>* QuestionDAO::getQuestions(const QString& entryName) const {
    QSqlQuery query(mDatabase);
    query.prepare("SELECT * FROM questions WHERE entry_name = (:entry_name)");
    query.bindValue(":entry_name", entryName);
    query.exec();
    DatabaseManager::queryStatus(query);

    QVector<QPair<unsigned int, Question>>* questions = new QVector<QPair<unsigned int, Question>>();

    while (query.next()) {
        questions->push_back(QPair<unsigned int, Question>(
                                                        query.value("id").toUInt(),
                                                        Question(query.value("question").toString(),
                                                        query.value("answer").toString())));
    }

    return questions;
}

QVector<Question>* QuestionDAO::getQuizQuestions(const QString& entry) const {
    QVector<Question>* questions = new QVector<Question>();

    QSqlQuery query(mDatabase);
    query.prepare("SELECT * FROM categories WHERE name = (:name)");
    query.bindValue(":name", entry);
    query.exec();
    if (query.next()) {
        // TODO: fetch each category and question
    } else {
        query.prepare("SELECT * FROM questions WHERE entry_name = (:entry_name)");
        query.bindValue(":entry_name", entry);
        query.exec();

        while (query.next()) {
            questions->push_back(Question(query.value("question").toString(), query.value("answer").toString()));
        }
    }

    return questions;
}
