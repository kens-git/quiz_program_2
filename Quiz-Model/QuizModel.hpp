#ifndef QUIZMODEL_HPP
#define QUIZMODEL_HPP

#include <QStringList>
#include <QVector>

#include "Question.hpp"
class DatabaseManager;

class QuizModel {
    public:
        QuizModel(const QString& entry, unsigned int numQuestions);
        ~QuizModel();

        // TODO: make const methods const
        Question nextQuestion();
        void popQuestion();

        unsigned int numQuestions();
        unsigned int numLoadedQuestions();

        void incCorrect();
        unsigned int numCorrect();
        void incIncorrect();
        unsigned int numIncorrect();
        void addIncorrect(const QString& question);
        unsigned int numAnsweredQuestions();

    private:
        DatabaseManager& mDatabase;

        QVector<Question>* mQuestions;
        QStringList* mWrongQuestions;
        unsigned int mNumQuestions;
        unsigned int mCorrectAnswers;
        unsigned int mIncorrectAnswers;
};

#endif // QUIZMODEL_HPP
