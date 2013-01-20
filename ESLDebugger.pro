#-------------------------------------------------
#
# Project created by QtCreator 2012-12-17T14:14:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ESLDebugger
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    connectdialog.cpp

HEADERS  += mainwindow.h \
    connectdialog.h

FORMS    += mainwindow.ui \
    connectdialog.ui

INCLUDEPATH += /Users/jmesquita/Documents/Programacao/freeswitch/libs/esl/src/include
DEPENDPATH += /Users/jmesquita/Documents/Programacao/freeswitch/libs/esl
LIBS += -L/Users/jmesquita/Documents/Programacao/freeswitch/libs/esl -lesl
