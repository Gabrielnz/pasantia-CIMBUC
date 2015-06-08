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
    QImage imgaux((uchar*)matOriginal.data, matOriginal.cols, matOriginal.rows, matOriginal.step, QImage::Format_RGB888);
    qimg = imgaux;
    //se le asigna la imagen a la etiqueta de la camara
    ui->etqCamara->setPixmap(QPixmap::fromImage(qimg));

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
    //si la camara no ha sido abierta ya
    if(capWebcam.isOpened() == false){

        tmrTimer = new QTimer(this);

        capWebcam.open(0);/*Abre la camara web*/

        if(capWebcam.isOpened() == false){
            //avisar que la camara no se pudo abrir por medio de un cuadro de dialogo o algo asi.
        }
        connect(tmrTimer, SIGNAL(timeout()), this, SLOT(procesarCuadroActualizarGUI()));
    }
    if(!tmrTimer->isActive())
        tmrTimer->start(30);
}

void MainWindow::on_actionDetener_camara_triggered()
{
    if(tmrTimer->isActive())
        tmrTimer->stop();
}

void MainWindow::on_btnCapturar_clicked()
{
    if(capWebcam.isOpened() == true){//si la camara esta abierta ya
        QDate fecha;
        qimg.save(ui->cBoxColor->currentText() + " - " + fecha.currentDate().toString("dd.MM.yyyy") + ".png");
    }
}

