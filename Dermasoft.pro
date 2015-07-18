#-------------------------------------------------
#
# Project created by QtCreator 2015-06-04T12:39:05
#
#-------------------------------------------------

QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Dermasoft
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    crearhistoria.cpp \
    dlgimagen.cpp \
    abrirhistoria.cpp \
    verhistoria.cpp \
    abriricon.cpp \
    regicon.cpp \
    objcaptura.cpp

HEADERS  += mainwindow.h \
    crearhistoria.h \
    dlgimagen.h \
    abrirhistoria.h \
    verhistoria.h \
    abriricon.h \
    regicon.h \
    objcaptura.h

FORMS    += mainwindow.ui \
    crearhistoria.ui \
    dlgimagen.ui \
    abrirhistoria.ui \
    verhistoria.ui \
    abriricon.ui \
    regicon.ui

#configuracion para Windows
win32 {
    RC_ICONS += img/Eye_ico.ico
    INCLUDEPATH += C:\opencv\build\install\include
    LIBS += C:\opencv\build\bin\libopencv_core300.dll
    LIBS += C:\opencv\build\bin\libopencv_imgproc300.dll
    LIBS += C:\opencv\build\bin\libopencv_video300.dll
    LIBS += C:\opencv\build\bin\libopencv_videoio300.dll
}
#configuracion para Linux
unix:!mac {
    INCLUDEPATH += /usr/local/include
    LIBS += `pkg-config opencv --libs`
    LIBS += /usr/local/lib/libopencv_core.so
    LIBS += /usr/local/lib/libopencv_highgui.so
    LIBS += /usr/local/lib/libopencv_imgproc.so
    LIBS += /usr/local/lib/libopencv_video.so
}

RESOURCES += \
    resources.qrc

