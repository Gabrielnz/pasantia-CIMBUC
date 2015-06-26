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
    crearhistoria.cpp \
    dlgimagen.cpp \
    dlginfo.cpp \
    crearlesion.cpp \
    abrirhistoria.cpp \
    abrirlesion.cpp \
    dlgconfirmar.cpp

HEADERS  += mainwindow.h \
    acercade.h \
    crearhistoria.h \
    dlgimagen.h \
    dlginfo.h \
    crearlesion.h \
    abrirhistoria.h \
    abrirlesion.h \
    dlgconfirmar.h

FORMS    += mainwindow.ui \
    acercade.ui \
    crearhistoria.ui \
    dlgimagen.ui \
    dlginfo.ui \
    crearlesion.ui \
    abrirhistoria.ui \
    abrirlesion.ui \
    dlgconfirmar.ui

INCLUDEPATH += C:\opencv\build\include

#librerias necesarias de opencv 3.0 para este proyecto
LIBS += C:\opencv\build\x86\vc12\lib\opencv_world300.lib
#LIBS += C:\opencv\build\bin\libopencv_core300.dll
#LIBS += C:\opencv\build\bin\libopencv_imgproc300.dll
#LIBS += C:\opencv\build\bin\libopencv_video300.dll
#LIBS += C:\opencv\build\bin\libopencv_videoio300.dll

#librerias opcionales de opencv 3.0
#LIBS += C:\opencv\build\bin\libopencv_highgui300.dll
#LIBS += C:\opencv\build\bin\libopencv_calib3d300.dll
#LIBS += C:\opencv\build\bin\libopencv_features2d300.dll
#LIBS += C:\opencv\build\bin\libopencv_flann300.dll
#LIBS += C:\opencv\build\bin\libopencv_imgcodecs300.dll
#LIBS += C:\opencv\build\bin\libopencv_ml300.dll
#LIBS += C:\opencv\build\bin\libopencv_photo300.dll
#LIBS += C:\opencv\build\bin\libopencv_videostab300.dll
#LIBS += C:\opencv\build\bin\libopencv_objdetect300.dll
#LIBS += C:\opencv\build\bin\libopencv_shape300.dll
#LIBS += C:\opencv\build\bin\libopencv_stitching300.dll
#LIBS += C:\opencv\build\bin\libopencv_superres300.dll
