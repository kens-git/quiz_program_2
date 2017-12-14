#ifndef QUESTIONDAO_HPP
#define QUESTIONDAO_HPP

#include <QVector>
#include <QPair>
class QSqlDatabase;

class Question;

class QuestionDAO {
    public:
        QuestionDAO(QSqlDatabase& database);
        void init() const;

        // returns (auto-incremented) ID of entered question
        unsigned int addQuestion(const QString& question, const QString& answer, const QString& entryName) const;
        void updateQuestionText(const QString& question, unsigned int id) const;
        void updateAnswerText(const QString& answer, unsigned int id) const;
        void removeQuestion(unsigned int id) const;

        QVector<QPair<unsigned int, Question>>* getQuestions(const QString& entryName) const;
        // fetches the questions for a particular category/entry
        QVector<Question>* getQuizQuestions(const QString& entryName) const;

    private:
        QSqlDatabase& mDatabase;
};

#endif // QUESTIONDAO_HPP
