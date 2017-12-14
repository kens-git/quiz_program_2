QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Quiz-Android
TEMPLATE = app

CONFIG += c+11

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
        main.cpp \
        MainWindow.cpp

HEADERS += \
        MainWindow.hpp

FORMS += \
        MainWindow.ui

LIBS += -L$$OUT_PWD/../Quiz-Model/ -lQuiz-Model
INCLUDEPATH += $$PWD/../Quiz-Model
DEPENDPATH += $$PWD/../Quiz-Model

contains(ANDROID_TARGET_ARCH,x86) {
    ANDROID_EXTRA_LIBS = \
        $$[QT_INSTALL_LIBS]/libQt5Sql.so
}

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
        $$[QT_INSTALL_LIBS]/libQt5Sql.so
}

RESOURCES += \
    res.qrc

DEPLOYMENT.files += quiz_database.db
DEPLOYMENT.path = /

INSTALLS += DEPLOYMENT
