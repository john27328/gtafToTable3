#-------------------------------------------------
#
# Project created by QtCreator 2015-07-06T17:05:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = grafToTable3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    grafsouce.cpp \
    grafwidget.cpp \
    point.cpp

HEADERS  += mainwindow.h \
    grafsource.h \
    grafwidget.h \
    point.h

OTHER_FILES +=


QMAKE_LFLAGS += -static -static-libgcc
