#-------------------------------------------------
#
# Project created by QtCreator 2019-03-06T11:12:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab_02
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
		point.cpp \
		lineseg.cpp \
		triangle.cpp \
        window.cpp \
    ellipse.cpp \
    rectangle.cpp \
    house.cpp \
    arc.cpp \
    outline.cpp \
    stack.cpp

HEADERS += \
		point.h \
		lineseg.h \
		triangle.h \
        window.h \
    ellipse.h \
    rectangle.h \
    house.h \
    arc.h \
    outline.h \
    stack.h \
    command.h

FORMS += \
        window.ui
