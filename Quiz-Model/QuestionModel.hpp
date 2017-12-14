#ifndef QUESTIONMODEL_HPP
#define QUESTIONMODEL_HPP

#include <QAbstractTableModel>
#include <QVariant>
#include <QString>
#include <QVector>

#include "Question.hpp"
class DatabaseManager;

class QuestionModel : public QAbstractTableModel {
    public:
        QuestionModel(QObject* parent = nullptr);
        ~QuestionModel();

        QVariant data(const QModelIndex &index, int role) const override;
        bool setData(const QModelIndex &index, const QVariant &value, int role) override;
        int rowCount(const QModelIndex &parent) const override;
        int columnCount(const QModelIndex &parent) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
        Qt::ItemFlags flags(const QModelIndex &index) const override;

        void addNewQuestion();
        QModelIndex insertQuestion(const QString& question, const QString& answer);
        void removeQuestion(const QModelIndex& index);
        // sets mEntryName and loads the applicable questions
        void setCurrentEntry(const QString& entryName);

    private:
        DatabaseManager& mDatabase;
        QVector<QPair<unsigned int, Question>>* mQuestions;
        // value of the currently open entry
        QString mEntryName;

        const unsigned int NUM_COLUMNS = 2;
};

#endif // QUESTIONMODEL_HPP
