#-------------------------------------------------
#
# Project created by QtCreator 2014-11-06T10:32:46
#
#-------------------------------------------------

QT       += core gui\
            xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FunShapes
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    object.cpp \
    scene.cpp \
    undoredo.cpp \
    xmlparser.cpp \
    dialogs.cpp

HEADERS  += mainwindow.h \
    object.h \
    scene.h \
    undoredo.h \
    xmlparser.h \
    dialogs.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

RC_FILE = logo.rc
