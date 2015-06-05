#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "acercade.h"
#include <QtCore>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::procesarCuadroActualizarGUI(){
    capWebcam.read(matOriginal);

    if(matOriginal.empty() == true) return; //aunque no previene que la aplicacion llame 50 veces x segundo a este procedimiento, se sale, evitando que la pc se tranque mas de lo que deberia.

    //se prepara la imagen para convertirla de BGR A RGB para que Qt pueda manejarla
    cv::cvtColor(matOriginal, matOriginal, CV_BGR2RGB);
    //ocurre la conversion de cv mat a qimage. Investigar sobre cual QImage::Format_ es mas apropiado
    QImage img((uchar*)matOriginal.data, matOriginal.cols, matOriginal.rows, matOriginal.step, QImage::Format_RGB888);
    //se le asigna la imagen a la etiqueta de la camara
    ui->etqCamara->setPixmap(QPixmap::fromImage(img));

}

void MainWindow::on_actionAcerca_de_triggered()
{
    AcercaDe mensaje;
    mensaje.setModal(true);
    mensaje.exec();
}

void MainWindow::on_actionSalir_triggered()
{
    close();
}

void MainWindow::on_actionIniciar_camara_triggered()
{

    if(capWebcam.isOpened() == false){

        tmrTimer = new QTimer(this);

        capWebcam.open(0);/*Abre la camara web*/

        if(capWebcam.isOpened() == false){
            ui->etqHistoria->setText("No camera, nigger");
        }
        connect(tmrTimer, SIGNAL(timeout()), this, SLOT(procesarCuadroActualizarGUI()));
    }

    tmrTimer->start(20);
}

void MainWindow::on_actionDetener_camara_triggered()
{
    tmrTimer->stop();
}
