#include "QuestionModel.hpp"

#include <QDebug>

#include "DatabaseManager.hpp"

QuestionModel::QuestionModel(QObject *parent)
    : QAbstractTableModel(parent),
      mDatabase(DatabaseManager::instance())
{
    mQuestions = new QVector<QPair<unsigned int, Question>>();
    mEntryName = "null";
}

QuestionModel::~QuestionModel() {
    delete mQuestions;
    mQuestions = nullptr;
}

QVariant QuestionModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        if (index.column() == 0) {
            return mQuestions->at(index.row()).second.getQuestionText();
        }
        else if (index.column() == 1) {
            return mQuestions->at(index.row()).second.getAnswerText();
        } else {
            return QVariant();
        }
    }
    else {
        return QVariant();
    }
}

bool QuestionModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid()) {
        return false;
    }

    if (index.row() > mQuestions->size() - 1 || index.row() < 0) {
        return false;
    }

    if (index.column() == 0) {
        // QVector doesn't seem to have a method to return an object in a non-const way,
        // so reassign a new Question when the value of the question/answer changes
        (*mQuestions)[index.row()].second = Question(value.toString(), mQuestions->at(index.row()).second.getAnswerText());
        mDatabase.mQuestionDAO.updateQuestionText(value.toString(), mQuestions->at(index.row()).first);
    }
    else if (index.column() == 1) {
        (*mQuestions)[index.row()].second = Question(mQuestions->at(index.row()).second.getQuestionText(), value.toString());
        mDatabase.mQuestionDAO.updateAnswerText(value.toString(), mQuestions->at(index.row()).first);
    } else {
        return false;
    }

    return true;
}

int QuestionModel::rowCount(const QModelIndex &parent) const {
    return mQuestions->size();
}

int QuestionModel::columnCount(const QModelIndex &parent) const {
    return NUM_COLUMNS;
}

QVariant QuestionModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal) {
        if (section == 0) {
            return QString("Question");
        }
        if (section == 1) {
            return QString("Answer");
        }
    }

    return section + 1;
}

Qt::ItemFlags QuestionModel::flags(const QModelIndex &index) const {
    return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

void QuestionModel::addNewQuestion() {
    if (mEntryName != "null") {
        beginInsertRows(QModelIndex(), mQuestions->size(), mQuestions->size());
        Question question("null", "null");
        unsigned int id = mDatabase.mQuestionDAO.addQuestion(question.getQuestionText(), question.getAnswerText(), mEntryName);
        mQuestions->push_back(QPair<unsigned int, Question>(id, question));
        endInsertRows();
    }
}

QModelIndex QuestionModel::insertQuestion(const QString &question, const QString &answer) {

}

void QuestionModel::removeQuestion(const QModelIndex& index) {
    if (!index.isValid()) {
        return;
    }

    mDatabase.mQuestionDAO.removeQuestion(mQuestions->at(index.row()).first);

    beginRemoveRows(QModelIndex(), index.row(), index.row());
    mQuestions->remove(index.row());
    endRemoveRows();
}

void QuestionModel::setCurrentEntry(const QString &entryName) {
    mEntryName = entryName;

    beginRemoveRows(QModelIndex(), 0, mQuestions->size() - 1);
    delete mQuestions;
    endRemoveRows();
    mQuestions = mDatabase.mQuestionDAO.getQuestions(mEntryName);
    beginInsertRows(QModelIndex(), 0, mQuestions->size() - 1);
    endInsertRows();
}
