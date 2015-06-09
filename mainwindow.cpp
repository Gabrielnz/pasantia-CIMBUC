#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "acercade.h"
#include <QtCore>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){

    ui->setupUi(this);
    //deshabilitar todos los botones necesarios al iniciar la interfaz
    ui->btnCapturar->setEnabled(false);
    ui->btnMostrarImagen->setEnabled(false);
    ui->btnAnotar->setEnabled(false);
    ui->cBoxColor->setEnabled(false);
    ui->actionDetener_camara->setEnabled(false);
}

MainWindow::~MainWindow(){

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
    //se obtiene al largo y ancho de la imagen capturada
    int w = ui->etqCamara->width();
    int h = ui->etqCamara->height();
    //se le asigna la imagen a la etiqueta de la camara
    ui->etqCamara->setPixmap((QPixmap::fromImage(qimg)).scaled(w, h, Qt::KeepAspectRatio));
}

void MainWindow::on_actionAcerca_de_triggered(){

    AcercaDe mensaje;
    mensaje.setModal(true);
    mensaje.exec();
}

void MainWindow::on_actionSalir_triggered(){

    close();
}

void MainWindow::on_actionIniciar_camara_triggered(){

    //si la camara no ha sido abierta ya
    if(capWebcam.isOpened() == false){

        tmrTimer = new QTimer(this);

        capWebcam.open(0);/*Abre la camara web*/

        if(capWebcam.isOpened() == false){
            //avisar que la camara no se pudo abrir por medio de un cuadro de dialogo o algo asi.
        }else{
            connect(tmrTimer, SIGNAL(timeout()), this, SLOT(procesarCuadroActualizarGUI()));
            //habilitar seleccion de color
            ui->cBoxColor->setEnabled(true);
            tmrTimer->start(30);
        }
    }else{
        if(!tmrTimer->isActive())
            tmrTimer->start(30);

        //habilitar seleccion de color
        ui->cBoxColor->setEnabled(true);
    }
    //dehabilita iniciar camara y habilita detener camara
    ui->actionIniciar_camara->setEnabled(false);
    ui->actionDetener_camara->setEnabled(true);
}

void MainWindow::on_actionDetener_camara_triggered(){

    if(tmrTimer->isActive())
        tmrTimer->stop();

    //borra la imagen que haya quedado en la etiqueta de la camara
    QPixmap pixDummy(0, 0);
    ui->etqCamara->setPixmap(pixDummy);
    ui->etqVistaprevia->setPixmap(pixDummy);
    //desabilitar todos los botones
    ui->btnCapturar->setEnabled(false);
    ui->btnMostrarImagen->setEnabled(false);
    ui->btnAnotar->setEnabled(false);
    ui->cBoxColor->setEnabled(false);
    ui->cBoxColor->setCurrentText("Seleccionar");
    ui->actionIniciar_camara->setEnabled(true);
    ui->actionDetener_camara->setEnabled(false);
}

void MainWindow::on_btnCapturar_clicked(){

    qimg.save(ui->cBoxColor->currentText() + " - " + QDate::currentDate().toString("dd.MM.yyyy") + ".png");

    int w = ui->etqVistaprevia->width();
    int h = ui->etqVistaprevia->height();
    //se le asigna la imagen a la etiqueta de la camara
    ui->etqVistaprevia->setPixmap((QPixmap::fromImage(qimg)).scaled(w, h, Qt::KeepAspectRatio));
    //habilita el boton de mostrar imagen para visualizar la imagen que se capturo
    ui->btnMostrarImagen->setEnabled(true);
}

void MainWindow::on_cBoxColor_currentTextChanged(const QString &texto){

    QString nombreImagen(ui->cBoxColor->currentText() + " - " + QDate::currentDate().toString("dd.MM.yyyy") + ".png");

    if(texto != "Seleccionar"){
        QFileInfo archivo(nombreImagen);
        //habilita todos los botones
        ui->btnCapturar->setEnabled(true);
        ui->btnAnotar->setEnabled(true);

        if(archivo.exists()){
            //si la imagen existe, habilita el boton para mostrarla
            ui->btnMostrarImagen->setEnabled(true);

            QImage imagen(nombreImagen);
            int w = ui->etqVistaprevia->width();
            int h = ui->etqVistaprevia->height();
            ui->etqVistaprevia->setPixmap((QPixmap::fromImage(imagen)).scaled(w, h, Qt::KeepAspectRatio));
            //qDebug() << nombreImagen + "SI existe.";
        }else{
            //borra la imagen que este en la vistap previa
            //qDebug() << nombreImagen + "NO existe.";
            QPixmap pixDummy(0, 0);
            ui->etqVistaprevia->setPixmap(pixDummy);
            ui->btnMostrarImagen->setEnabled(false);
        }
    }else{
        //borra la imagen que este en la vistap previa
        //qDebug() << "Seleccione un color";
        QPixmap pixDummy(0, 0);
        ui->etqVistaprevia->setPixmap(pixDummy);
        //desabilitar todos los botones, excepto seleccionar
        ui->btnCapturar->setEnabled(false);
        ui->btnMostrarImagen->setEnabled(false);
        ui->btnAnotar->setEnabled(false);
    }
}

void MainWindow::on_btnMostrarImagen_clicked(){

    QString nombreImagen(ui->cBoxColor->currentText() + " - " + QDate::currentDate().toString("dd.MM.yyyy") + ".png");
    QImage imagen(nombreImagen);
    int w = imagen.width();
    int h = imagen.height();

    QDialog *dialogoImagen = new QDialog;
    QLabel *etqImagen = new QLabel(dialogoImagen);
    etqImagen->setFixedWidth(w);
    etqImagen->setFixedHeight(h);
    etqImagen->setPixmap(QPixmap::fromImage(imagen));
    dialogoImagen->setWindowTitle(nombreImagen);
    dialogoImagen->setFixedWidth(w);
    dialogoImagen->setFixedHeight(h);
    dialogoImagen->setModal(true);
    dialogoImagen->exec();
}
