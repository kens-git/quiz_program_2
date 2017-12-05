#include "Question.hpp"

Question::Question(const QString &question, const QString &answer) {
    mQuestion = question;
    mAnswer = answer;
}

QString Question::getQuestionText() const {
    return mQuestion;
}

void Question::setQuestionText(const QString &question) {
    mQuestion = question;
}

QString Question::getAnswerText() const {
    return mAnswer;
}

void Question::setAnswerText(const QString &answer) {
    mAnswer = answer;
}
