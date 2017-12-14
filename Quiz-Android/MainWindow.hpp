#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class EntryModel;
class QuizModel;

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private:
        Ui::MainWindow *ui;

        EntryModel* mEntryModel;
        QuizModel* mQuizModel;

        void nextQuestion();

    private slots:
        void startNewQuiz();
        void correctAnswer();
        void incorrectAnswer();
        void answerButtonClicked();
};

#endif // MAINWINDOW_HPP
