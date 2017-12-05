#-------------------------------------------------
#
# Project created by QtCreator 2017-11-07T11:31:01
#
#-------------------------------------------------

QT       += sql
QT       -= gui

TARGET = Quiz-Model
TEMPLATE = lib

CONFIG += c++14

DEFINES += QUIZMODEL_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    DatabaseManager.cpp \
    Category.cpp \
    CategoryDAO.cpp \
    TreeItem.cpp \
    CategoryListModel.cpp \
    EntryDAO.cpp \
    EntryModel.cpp \
    QuestionDAO.cpp \
    Question.cpp \
    QuestionModel.cpp \
    CategoryEntryModel.cpp \
    QuizModel.cpp

HEADERS += \
        quiz-model_global.h \ 
    DatabaseManager.hpp \
    Category.hpp \
    CategoryDAO.hpp \
    TreeItem.hpp \
    CategoryListModel.hpp \
    EntryDAO.hpp \
    EntryModel.hpp \
    QuestionDAO.hpp \
    Question.hpp \
    QuestionModel.hpp \
    CategoryEntryModel.hpp \
    QuizModel.hpp
