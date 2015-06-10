#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "acercade.h"
#include "opciones.h"
#include "crearhistoria.h"
#include <QtCore>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){

    ui->setupUi(this);
    dirRaiz = QDir::homePath() + "/" + "Dermasoft - Historias";
    fecha = QDate::currentDate().toString("dd.MM.yyyy");
    tmrTimer = new QTimer(this);
    QDir dir;
    dir.mkpath(dirRaiz);
    ui->etqHistoria->setAlignment(Qt::AlignCenter);
    //deshabilitar todos los botones necesarios al iniciar la interfaz
    ui->btnCapturar->setEnabled(false);
    ui->btnMostrarImagen->setEnabled(false);
    ui->btnAnotar->setEnabled(false);
    ui->cBoxColor->setEnabled(false);
    ui->actionDetener_camara->setEnabled(false);
    ui->actionCerrar_historia->setEnabled(false);
    ui->actionEliminar_historia->setEnabled(false);
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

    //si la camara no ha sido abierta
    if(capWebcam.isOpened() == false){

        capWebcam.open(0);/*Abre la camara web*/

        if(capWebcam.isOpened() == false){
            //avisar que la camara no se pudo abrir por medio de un cuadro de dialogo o algo asi.
        }else{
            //conecta el timer con la actualizacion del cuadro de la GUI
            connect(tmrTimer, SIGNAL(timeout()), this, SLOT(procesarCuadroActualizarGUI()));
            tmrTimer->start(30);
        }
    }else{
        if(!tmrTimer->isActive())
            tmrTimer->start(30);
    }
    //dehabilita iniciar camara y habilita detener camara, solo si se pudo iniciar esta
    if(tmrTimer->isActive()){
        ui->actionIniciar_camara->setEnabled(false);
        ui->actionDetener_camara->setEnabled(true);
    }
    //si hay una historia cargada o creada para guardar las imagenes, habilita la seleccion de los colores
    revisionHistoria();
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

    ui->actionIniciar_camara->setEnabled(true);
    ui->actionDetener_camara->setEnabled(false);

    //en caso de que haya una historia cargada, habilita la seleccion de colores
    revisionHistoria();
}

void MainWindow::on_btnCapturar_clicked(){

    //crea el directorio con la fecha actual antes de tomar las fotos
    QDir dir;
    dir.mkpath(dirRaiz + "/" + historia + "/" + fecha);
    qimg.save(dirRaiz + "/" + historia + "/" + fecha + "/" + ui->cBoxColor->currentText() + " - " + fecha + ".png");

    int w = ui->etqVistaprevia->width();
    int h = ui->etqVistaprevia->height();
    //se le asigna la imagen a la etiqueta de la camara
    ui->etqVistaprevia->setPixmap((QPixmap::fromImage(qimg)).scaled(w, h, Qt::KeepAspectRatio));
    //habilita el boton de mostrar imagen para visualizar la imagen que se capturo
    if(!ui->btnMostrarImagen->isEnabled())
        ui->btnMostrarImagen->setEnabled(true);
    if(!ui->btnAnotar->isEnabled())
        ui->btnAnotar->setEnabled(true);
}

void MainWindow::on_cBoxColor_currentTextChanged(const QString &texto){

    QString nombreImagen(dirRaiz + "/" + historia + "/" + fecha + "/" + ui->cBoxColor->currentText() + " - " + fecha + ".png");

    if(texto != "Seleccionar"){
        QFileInfo archivo(nombreImagen);
        //si la camara esta activa, habilita el boton capturar
        if(tmrTimer->isActive()){
            ui->btnCapturar->setEnabled(true);
        }

        if(archivo.exists()){
            //si la imagen existe, habilita el boton para mostrarla
            ui->btnMostrarImagen->setEnabled(true);
            ui->btnAnotar->setEnabled(true);

            QImage imagen(nombreImagen);
            int w = ui->etqVistaprevia->width();
            int h = ui->etqVistaprevia->height();
            ui->etqVistaprevia->setPixmap((QPixmap::fromImage(imagen)).scaled(w, h, Qt::KeepAspectRatio));
        }else{
            //borra la imagen que este en la vista previa
            QPixmap pixDummy(0, 0);
            ui->etqVistaprevia->setPixmap(pixDummy);
            ui->btnMostrarImagen->setEnabled(false);
            ui->btnAnotar->setEnabled(false);
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

    QString nombreImagen(dirRaiz + "/" + historia + "/" + fecha + "/" + ui->cBoxColor->currentText() + " - " + fecha + ".png");
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

void MainWindow::on_actionOpciones_triggered(){

    Opciones opc;

    opc.setModal(true);
    opc.exec();
}

void MainWindow::on_actionCrear_historia_triggered(){

    QDir dir;
    crearHistoria crear;
    //obtiene el ID de la historia a crear
    crear.setModal(true);
    crear.exec();
    //crea la estructura de directorios necesaria para la nueva historia
    historia = crear.getHistoriaCreada();
    dir.mkpath(dirRaiz + "/" + historia);

    //revisa que la historia este cargada para activar los botones pertinentes
    revisionHistoria();
}

void MainWindow::on_actionCerrar_historia_triggered(){

    historia = "";
    revisionHistoria();
}

//Si hay una historia cargada, habilita los botones pertinentes, caso contrario los deshabilita
void MainWindow::revisionHistoria(){

    //si hay una historia cargada, habilita la seleccion de colores
    if(!historia.isEmpty()){
        ui->cBoxColor->setEnabled(true);
        QString hist("Historia: " + historia);
        ui->etqHistoria->setText("<p align='center'><span style=' font-weight:600;'>" + hist + " - " + fecha + "</span></p>");
        //deshabilita la opcion de crear o de abrir una historia, mientras ya este una cargada
        ui->actionCrear_historia->setEnabled(false);
        ui->actionAbrir_historia->setEnabled(false);
        //habilita la opcion de cerrar la historia cargada
        ui->actionCerrar_historia->setEnabled(true);
    }else{
        ui->cBoxColor->setEnabled(false);

        //si la camara sigue activa, muestra el mensaje siguiente
        if(tmrTimer->isActive()){
            ui->etqHistoria->setText("<p align='center'><span style=' font-weight:600;'>Crear o abrir una historia para continuar</span></p>");
        }else{
        //sino, borra el mensaje
            ui->etqHistoria->setText("");
        }
        //habilita la opcion de crear o de abrir una historia, en caso de que no haya una historia cargada
        ui->actionCrear_historia->setEnabled(true);
        ui->actionAbrir_historia->setEnabled(true);
        //deshabilita la opcion de cerrar la historia cargada
        ui->actionCerrar_historia->setEnabled(false);
    }
    ui->cBoxColor->setCurrentText("Seleccionar");
}
