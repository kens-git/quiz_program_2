#include "MainWindow.hpp"
#include "ui_MainWindow.h"

// TODO: remove debugging messages
#include <QDebug>
#include <QMessageBox>
#include <QItemDelegate>

#include "CategoryEntryModel.hpp"
#include "CategoryListModel.hpp"
#include "EntryModel.hpp"
#include "QuestionModel.hpp"
#include "QuizModel.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mCategoryEntryModel(nullptr),
    mEntryModel(nullptr),
    mQuizModel(nullptr)
{
    ui->setupUi(this);

    CategoryEntryModel* categoryEntryModel = new CategoryEntryModel(this);
    QItemSelectionModel* categorySelectionModel = new QItemSelectionModel(categoryEntryModel, this);
    setCategoryEntryModel(categoryEntryModel);
    // TODO: does this really need a selection model?
    //setCategoryEntrySelectionModel(categorySelectionModel);

    CategoryListModel* categoryListModel = new CategoryListModel(this);
    setCategoryListModel(categoryListModel);

    EntryModel* entryModel = new EntryModel(this);
    setEntryModel(entryModel);

    QuestionModel* questionModel = new QuestionModel(this);
    setQuestionModel(questionModel);
    ui->questionsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->addNewCategoryButton, &QPushButton::clicked, this, &MainWindow::addNewCategory);
    connect(ui->addNewEntryButton, &QPushButton::clicked, this, &MainWindow::addNewEntry);
    connect(ui->selectEntryListView, &QListView::clicked, this, &MainWindow::entrySelected);

    connect(ui->tabWidget, &QTabWidget::tabBarClicked, this, &MainWindow::quizTabClicked);

    ui->answerTextLabel->hide();
    ui->answerTextButton->setEnabled(false);
    connect(ui->answerTextButton, &QPushButton::clicked, this, &MainWindow::answerTextClicked);

    connect(ui->addNewQuestionButton, &QPushButton::clicked, this, &MainWindow::addNewQuestion);

    connect(ui->startNewQuizButton, &QPushButton::clicked, this, &MainWindow::startNewQuiz);

    ui->correctButton->setEnabled(false);
    ui->wrongButton->setEnabled(false);
    connect(ui->correctButton, &QPushButton::clicked, this, &MainWindow::correctAnswer);
    connect(ui->wrongButton, &QPushButton::clicked, this, &MainWindow::incorrectAnswer);
}

MainWindow::~MainWindow() {
    delete ui;

    delete mCategoryEntryModel;
    delete mCategoryListModel;
    delete mEntryModel;
    delete mQuestionModel;

    delete mQuizModel;
}

void MainWindow::setCategoryEntryModel(CategoryEntryModel *model) {
    mCategoryEntryModel = model;
    ui->categoryTreeView->setModel(mCategoryEntryModel);
}

void MainWindow::setCategoryEntrySelectionModel(QItemSelectionModel *selectionModel) {
    ui->categoryTreeView->setSelectionModel(selectionModel);
}

void MainWindow::setCategoryListModel(CategoryListModel *model) {
    mCategoryListModel = model;
    ui->newCategoryParentComboBox->setModel(mCategoryListModel);
    ui->newEntryParentComboBox->setModel(mCategoryListModel);
}

void MainWindow::setEntryModel(EntryModel *model) {
    mEntryModel = model;
    ui->selectEntryListView->setModel(mEntryModel);
}

void MainWindow::setEntrySelectionModel(QItemSelectionModel *selectionModel) {
    ui->selectEntryListView->setSelectionModel(selectionModel);
}

void MainWindow::setQuestionModel(QuestionModel *model) {
    mQuestionModel = model;
    ui->questionsTableView->setModel(model);
}

void MainWindow::addNewCategory() {
    if (ui->addNewCategoryLineEdit->text().isEmpty()) {
        return;
    }

    if (mCategoryListModel->hasCategory(ui->addNewCategoryLineEdit->text())) {
        return;
    }

    mCategoryListModel->insertCategory(ui->addNewCategoryLineEdit->text(),
                                       ui->newCategoryParentComboBox->currentText());

    ui->addNewCategoryLineEdit->setText(QString(""));
}

void MainWindow::entrySelected() {
    mQuestionModel->setCurrentEntry(
                ui->selectEntryListView->model()->data(ui->selectEntryListView->currentIndex()).toString());
}

void MainWindow::addNewEntry() {
    if (ui->addNewEntryLineEdit->text().isEmpty()) {
        return;
    }

    if (mEntryModel->hasEntry(ui->addNewEntryLineEdit->text())) {
        return;
    }

    mEntryModel->insertEntry(ui->addNewEntryLineEdit->text(),
                             ui->newEntryParentComboBox->currentText());

    ui->addNewEntryLineEdit->setText(QString(""));
}

void MainWindow::quizTabClicked() {
    mCategoryEntryModel->loadCategories();
}

void MainWindow::answerTextClicked() {
    ui->answerTextButton->hide();
    ui->answerTextLabel->show();
}

void MainWindow::addNewQuestion() {
    // TODO: disable the Add New Question button if no entry is selected
    mQuestionModel->addNewQuestion();
}

void MainWindow::startNewQuiz() {
    // TODO: actually check for a number (regex, maybe)
    if (ui->categoryTreeView->currentIndex() != QModelIndex() && ui->numQuestionsLineEdit->text() != "") {
        delete mQuizModel;

        mQuizModel = new QuizModel(ui->categoryTreeView->currentIndex().data().toString(),
                                   ui->numQuestionsLineEdit->text().toInt());

        if (mQuizModel->numLoadedQuestions() == 0) {
            QMessageBox::information(this,
                                     "Could not load questions.",
                                     "Either there was a problem or the entry has no associated questions.",
                                     QMessageBox::Ok);
            return;
        }

        ui->answerTextButton->setEnabled(true);
        ui->correctButton->setEnabled(true);
        ui->wrongButton->setEnabled(true);

        ui->numCorrectLabel->setText("Correct: 0");
        ui->numIncorrectLabel->setText("Incorrect: 0");

        nextQuestion();
    }
}

void MainWindow::nextQuestion() {
    ui->answerTextButton->setHidden(false);
    ui->answerTextLabel->setHidden(true);

    int percent = ((float)mQuizModel->numAnsweredQuestions() / (float)mQuizModel->numQuestions()) * 100;
    ui->progressBar->setValue(percent);

    if (mQuizModel->numAnsweredQuestions() == mQuizModel->numQuestions()) {
        ui->correctButton->setEnabled(false);
        ui->wrongButton->setEnabled(false);
        ui->answerTextButton->setEnabled(false);
        ui->questionTextLabel->setText("Quiz Finished");
    } else {
        ui->questionTextLabel->setText(mQuizModel->nextQuestion().getQuestionText());
        ui->answerTextLabel->setText(mQuizModel->nextQuestion().getAnswerText());
        mQuizModel->popQuestion();
    }
}

void MainWindow::correctAnswer() {
    mQuizModel->incCorrect();
    ui->numCorrectLabel->setText(QString("Correct: %1").arg(mQuizModel->numCorrect()));

    nextQuestion();
}

void MainWindow::incorrectAnswer() {
    mQuizModel->incIncorrect();
    ui->numIncorrectLabel->setText(QString("Incorrect: %1").arg(mQuizModel->numIncorrect()));

    nextQuestion();
}
