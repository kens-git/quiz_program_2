#-------------------------------------------------
#
# Project created by QtCreator 2017-11-03T11:00:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Quiz-Desktop
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        MainWindow.cpp

HEADERS += \
        MainWindow.hpp

FORMS += \
        MainWindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Quiz-Model/release/ -lQuiz-Model
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Quiz-Model/debug/ -lQuiz-Model
else:unix: LIBS += -L$$OUT_PWD/../Quiz-Model/ -lQuiz-Model

INCLUDEPATH += $$PWD/../Quiz-Model
DEPENDPATH += $$PWD/../Quiz-Model
