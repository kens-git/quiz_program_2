#ifndef QUESTION_HPP
#define QUESTION_HPP

#include <QString>

class Question {
    public:
        Question() = default;
        Question(const QString& question, const QString& answer);

        QString getQuestionText() const;
        void setQuestionText(const QString& question);
        QString getAnswerText() const;
        void setAnswerText(const QString& answer);

    private:
        QString mQuestion;
        QString mAnswer;
};

#endif // QUESTION_HPP
