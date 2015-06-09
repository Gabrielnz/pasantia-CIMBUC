#-------------------------------------------------
#
# Project created by QtCreator 2015-06-04T12:39:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dermatoscopio
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    acercade.cpp \
    opciones.cpp \
    crearhistoria.cpp

HEADERS  += mainwindow.h \
    acercade.h \
    opciones.h \
    crearhistoria.h

FORMS    += mainwindow.ui \
    acercade.ui \
    opciones.ui \
    crearhistoria.ui

#supuesta linea para "agregar" el reconocimiento de opencv en el proyecto
LIBS += `pkg-config opencv --libs`
