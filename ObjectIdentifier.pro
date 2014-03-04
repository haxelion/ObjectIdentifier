#-------------------------------------------------
#
# Project created by QtCreator 2014-02-21T17:04:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ObjectIdentifier
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    processingthread.cpp

HEADERS  += mainwindow.h \
    processingthread.h \
    MatToQImage.h

FORMS    += mainwindow.ui

unix|win32: LIBS += -lopencv_core -lopencv_imgproc
