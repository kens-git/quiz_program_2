#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QWidget>
#include <QItemSelectionModel>

namespace Ui {
    class MainWindow;
}

class CategoryEntryModel;
class CategoryListModel;
class EntryModel;
class QuestionModel;
class QuizModel;

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

        void setCategoryEntryModel(CategoryEntryModel* model);
        void setCategoryListModel(CategoryListModel* model);
        void setEntryModel(EntryModel* model);
        void setQuestionModel(QuestionModel* model);

    private:
        Ui::MainWindow *ui;

        CategoryEntryModel* mCategoryEntryModel;
        CategoryListModel* mCategoryListModel;
        EntryModel* mEntryModel;
        QuestionModel* mQuestionModel;

        QuizModel* mQuizModel;

        void nextQuestion();

    private slots:
        void addNewCategory();
        void addNewEntry();
        void entrySelected();
        void quizTabClicked();
        void answerTextClicked();
        void addNewQuestion();
        void removeQuestion();
        void startNewQuiz();

        void correctAnswer();
        void incorrectAnswer();
};

#endif // MAINWINDOW_HPP
