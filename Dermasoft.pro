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
    acercade.cpp \
    crearhistoria.cpp \
    dlgimagen.cpp \
    dlginfo.cpp \
    abrirhistoria.cpp \
    dlgconfirmar.cpp \
    verhistoria.cpp \
    regabriricon.cpp \
    abriricon.cpp \
    regicon.cpp \
    objcaptura.cpp

HEADERS  += mainwindow.h \
    acercade.h \
    crearhistoria.h \
    dlgimagen.h \
    dlginfo.h \
    abrirhistoria.h \
    dlgconfirmar.h \
    verhistoria.h \
    regabriricon.h \
    abriricon.h \
    regicon.h \
    objcaptura.h

FORMS    += mainwindow.ui \
    acercade.ui \
    crearhistoria.ui \
    dlgimagen.ui \
    dlginfo.ui \
    abrirhistoria.ui \
    dlgconfirmar.ui \
    verhistoria.ui \
    regabriricon.ui \
    abriricon.ui \
    regicon.ui


win32 {
    RC_ICONS += img/Eye_ico.ico
    INCLUDEPATH += C:\opencv\build\install\include
    LIBS += C:\opencv\build\bin\libopencv_core300.dll
    LIBS += C:\opencv\build\bin\libopencv_imgproc300.dll
    LIBS += C:\opencv\build\bin\libopencv_video300.dll
    LIBS += C:\opencv\build\bin\libopencv_videoio300.dll
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
    message("Usando la configuracion para Windows")
}

unix:!mac {
    INCLUDEPATH += /usr/local/include
    LIBS += `pkg-config opencv --libs`
    LIBS += /usr/local/lib/libopencv_core.so
    LIBS += /usr/local/lib/libopencv_highgui.so
    LIBS += /usr/local/lib/libopencv_imgproc.so
    LIBS += /usr/local/lib/libopencv_video.so
    message("Usando la configuracion para Linux")
}

DISTFILES += \
    cimbuc.jpg

RESOURCES += \
    resources.qrc

