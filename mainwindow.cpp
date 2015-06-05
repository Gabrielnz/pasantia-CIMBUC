#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "acercade.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //conectando signal y slot para la opcion salir del dropdown de archivo
    connect(ui->actionSalir, SIGNAL(triggered(bool)),this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionAcerca_de_triggered()
{
    AcercaDe mensaje;
    mensaje.setModal(true);
    mensaje.exec();
}
