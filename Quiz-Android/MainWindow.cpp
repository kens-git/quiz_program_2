#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include "EntryModel.hpp"
#include "QuizModel.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mQuizModel(nullptr)
{
    ui->setupUi(this);

    mEntryModel = new EntryModel(this);
    ui->entryComboBox->setModel(mEntryModel);

    ui->answerLabel->hide();
    ui->correctButton->setEnabled(false);
    ui->incorrectButton->setEnabled(false);
    ui->showAnswerButton->setEnabled(false);

    connect(ui->entryComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &MainWindow::startNewQuiz);
    connect(ui->correctButton, &QPushButton::clicked, this, &MainWindow::correctAnswer);
    connect(ui->incorrectButton, &QPushButton::clicked, this, &MainWindow::incorrectAnswer);
    connect(ui->showAnswerButton, &QPushButton::clicked, this, &MainWindow::answerButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;

    delete mEntryModel;
    delete mQuizModel;
}

void MainWindow::nextQuestion() {
    ui->showAnswerButton->setHidden(false);
    ui->answerLabel->setHidden(true);

    int percent = ((float)mQuizModel->numAnsweredQuestions() / (float)mQuizModel->numQuestions()) * 100;
    ui->progressBar->setValue(percent);

    if (mQuizModel->numAnsweredQuestions() == mQuizModel->numQuestions()) {
        ui->correctButton->setEnabled(false);
        ui->incorrectButton->setEnabled(false);
        ui->showAnswerButton->setEnabled(false);
        ui->questionLabel->setText("Quiz Finished");
    } else {
        ui->questionLabel->setText(mQuizModel->nextQuestion().getQuestionText());
        ui->answerLabel->setText(mQuizModel->nextQuestion().getAnswerText());
        mQuizModel->popQuestion();
    }
}

void MainWindow::startNewQuiz() {
    delete mQuizModel;

    mQuizModel = new QuizModel(ui->entryComboBox->currentData(Qt::DisplayRole).toString(), 0);

    if (mQuizModel->numLoadedQuestions() == 0) {
        // If the user selects a valid quiz and then an invalid (entry with no questions) quiz,
        // the correct and incorrect buttons are still visible, so, disable them before returning.
        ui->correctButton->setEnabled(false);
        ui->incorrectButton->setEnabled(false);
        ui->showAnswerButton->setEnabled(false);

        ui->questionLabel->setText("No questions could be loaded.");

        return;
    }

    ui->showAnswerButton->setEnabled(true);
    ui->correctButton->setEnabled(true);
    ui->incorrectButton->setEnabled(true);
    ui->correctLabel->setText(QString("Correct: %1").arg(0));
    ui->incorrectLabel->setText(QString("Incorrect: %1").arg(0));

    nextQuestion();
}

void MainWindow::correctAnswer() {
    mQuizModel->incCorrect();

    ui->correctLabel->setText(QString("Correct: %1").arg(mQuizModel->numCorrect()));

    nextQuestion();
}

void MainWindow::incorrectAnswer() {
    mQuizModel->incIncorrect();

    ui->incorrectLabel->setText(QString("Incorrect: %1").arg(mQuizModel->numIncorrect()));

    nextQuestion();
}

void MainWindow::answerButtonClicked() {
    ui->showAnswerButton->hide();
    ui->answerLabel->show();
}
