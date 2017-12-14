#include "QuizModel.hpp"

#include "DatabaseManager.hpp"

QuizModel::QuizModel(const QString& entry, unsigned int numQuestions)
    : mDatabase(DatabaseManager::instance()),
      mQuestions(mDatabase.mQuestionDAO.getQuizQuestions(entry))
{
    mNumQuestions = numQuestions;
    mCorrectAnswers = 0;
    mIncorrectAnswers = 0;
    mWrongQuestions = new QStringList();

    if (mNumQuestions == 0) {
        mNumQuestions = numLoadedQuestions();
    }
    if (numLoadedQuestions() < mNumQuestions) {
        mNumQuestions = numLoadedQuestions();
    }
}

QuizModel::~QuizModel() {
    delete mQuestions;
    mQuestions = nullptr;
    delete mWrongQuestions;
    mWrongQuestions = nullptr;
}

Question QuizModel::nextQuestion() {
    if (mQuestions != nullptr) {
        return mQuestions->back();
    } else {
        return Question("Entry returned no valid questions.", "null");
    }
}

void QuizModel::popQuestion() {
    mQuestions->pop_back();
}

unsigned int QuizModel::numQuestions() {
    return mNumQuestions;
}

unsigned int QuizModel::numLoadedQuestions() {
    mQuestions->size();
}

void QuizModel::incCorrect() {
    ++mCorrectAnswers;
}

unsigned int QuizModel::numCorrect() {
    return mCorrectAnswers;
}

void QuizModel::incIncorrect() {
    ++mIncorrectAnswers;
}

unsigned int QuizModel::numIncorrect() {
    return mIncorrectAnswers;
}

void QuizModel::addIncorrect(const QString& question) {
    mWrongQuestions->push_back(question);
}

unsigned int QuizModel::numAnsweredQuestions() {
    return mCorrectAnswers + mIncorrectAnswers;
}
