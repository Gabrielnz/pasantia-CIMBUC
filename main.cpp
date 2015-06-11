#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[]){

    QApplication a(argc, argv);
    MainWindow w;

    //inicia la aplicacion en el medio de la pantalla
    QDesktopWidget widget;
    QRect mainScreenSize = widget.availableGeometry(widget.primaryScreen());
    int x = (mainScreenSize.width()- w.width()) / 2;
    int y = (mainScreenSize.height()- w.height()) / 2;
    w.move(x, y);
    //
    w.show();

    return a.exec();
}
