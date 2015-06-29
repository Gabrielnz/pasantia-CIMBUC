#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){

    ui->setupUi(this);
    dirRaiz = QDir::homePath() + "/" + "Dermasoft - Historias";
    fecha = QDate::currentDate().toString("dd.MM.yyyy");
    fechaLesion = new QString(fecha);
    tmrTimer = new QTimer;
    historia = new QString;
    lesion = new QString;
    //conecta el timer con la actualizacion del cuadro de la GUI
    connect(tmrTimer, SIGNAL(timeout()), this, SLOT(procesarCuadroActualizarGUI()));
    QDir dir;
    dir.setPath(dirRaiz);

    if(!dir.exists())
        dir.mkdir(dirRaiz);

    //deshabilitar todos los botones necesarios al iniciar la interfaz
    ui->actionDesconectar_camara->setEnabled(false);
    ui->actionCrear_historia->setEnabled(false);
    ui->actionAbrir_historia->setEnabled(false);
    ui->actionCerrar_historia->setEnabled(false);
    ui->actionEliminar_historia->setEnabled(false);
    ui->actionNueva_lesion->setEnabled(false);
    ui->actionAbrir_lesion->setEnabled(false);
    ui->actionCerrar_lesion->setEnabled(false);
    ui->actionEliminar_lesion->setEnabled(false);
    ui->cBoxModo->setEnabled(false);
    setBotones(false);
    ui->btnAbrirCarpeta->setEnabled(false);
    ui->btnGenerarReporte->setEnabled(false);
    this->adjustSize();
    this->setFixedSize(this->size());

    /////////////////////////////////////////////PROBANDO/DESARROLLANDO///////////////////////////////////////////////////
    //Averiguar de que manera aplicar un candado a todos los archivos que se esten manejando en el directorio raiz
    locker = new QLockFile(dirRaiz + "/" + "lock");
    locker->setStaleLockTime(0);
    locker->tryLock();
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int i, numCamaras;
    bool flag = true;
    i = numCamaras = 0;
    cv::VideoCapture camaras;
    QList<QAction*> accionesDinamicas;
    QSignalMapper *signalMapper = new QSignalMapper;
    ui->menuCamaras->clear();
    while(flag){
        camaras.open(i);
        if(camaras.isOpened()){
            accionesDinamicas.insert(i, ui->menuCamaras->addAction("Camara - " + QString::number(i)));
            connect(accionesDinamicas.at(i), SIGNAL(triggered()), signalMapper, SLOT(map()));
            signalMapper->setMapping(accionesDinamicas.at(i), i);
            numCamaras+=1;
            camaras.release();
        }else
            flag = false;
        i++;
    }
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(conectarCamaras(int)));

    if(numCamaras == 0){
        ui->menuCamaras->setEnabled(false);
    }

    dlgInfo info("Porfavor, no conecte o desconecte ninguna camara mientras la aplicacion este en ejecucion.", "Atencion");
    info.exec();
}

MainWindow::~MainWindow(){ delete ui; }

void MainWindow::procesarCuadroActualizarGUI(){

    capWebcam.read(matOriginal);
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

void MainWindow::conectarCamaras(int num){
    //si la camara no ha sido abierta
    if(capWebcam.isOpened() == false){

        capWebcam.open(num);/*Abre la camara web*/

        if(capWebcam.isOpened() == false){
            dlgInfo info("Porfavor verifique que la camara este conectada.", "Error al conectar la camara");
            info.exec();
        }else{
            ui->menuCamaras->setEnabled(false);
            ui->actionDesconectar_camara->setEnabled(true);
            revision();
            dlgInfo info("La camara fue conectada correctamente.", "Camara conectada");
            info.exec();
        }
    }
}

void MainWindow::on_actionDesconectar_camara_triggered(){

    capWebcam.release();
    //borra la imagen que haya quedado en la etiqueta de la camara
    QPixmap pixDummy(0, 0);
    ui->etqCamara->setPixmap(pixDummy);
    ui->etqVistaprevia->setPixmap(pixDummy);
    //ui->actionConectar_camara->setEnabled(true);
    ui->menuCamaras->setEnabled(true);
    ui->actionDesconectar_camara->setEnabled(false);
    ui->cBoxModo->setCurrentIndex(0);

    revision();
    dlgInfo info("La camara fue desconectada correctamente.", "Camara desconectada");
    info.exec();
}

void MainWindow::on_actionSalir_triggered(){ close();}

void MainWindow::on_actionAcerca_de_triggered(){

    AcercaDe mensaje;
    mensaje.exec();
}

void MainWindow::on_actionCrear_historia_triggered(){

    crearHistoria crear(dirRaiz, historia);
    crear.exec();
    revision();
}

void MainWindow::on_actionCerrar_historia_triggered(){

    //cuando se cierra una historia, se debe cerrar la lesion de dicha historia tambien
    *historia = "";
    *lesion = "";
    revision();
}

void MainWindow::on_actionCerrar_lesion_triggered(){

    *lesion = "";
    revision();
}

//Realiza una revision de la historia y la lesion
void MainWindow::revision(){

    bool crearHistoria, abrirHistoria, cerrarHistoria, eliminarHistoria, nuevaLesion, abrirLesion, cerrarLesion, eliminarLesion, cBoxModo, abrirCarpeta, generarReporte;
    QDir dirHist, dirLesion;
    QFileInfoList lista;

    //Si hay una historia cargada
    if(!historia->isEmpty()){
        crearHistoria = false;
        abrirHistoria = true;
        cerrarHistoria = true;
        eliminarHistoria = true;
        ui->etqInfoHistoria->setText(*historia);
        if(!lesion->isEmpty()){
            nuevaLesion = false;
            abrirLesion = true;
            cerrarLesion = true;
            eliminarLesion = true;
            cBoxModo = true;
            abrirCarpeta = true;
            generarReporte = true;
            ui->etqInfoLesion->setText(*lesion);
            ui->etqInfoFecha->setText(QDate::fromString(*fechaLesion, "dd.MM.yyyy").toString("dd/MM/yyyy"));
        }else{
            //Si hay una historia pero no hay una lesion, deshabilita la seleccin de modos
            *fechaLesion = fecha;

            if(capWebcam.isOpened()){
                nuevaLesion = true;
            }else{
                nuevaLesion = false;
            }

            dirLesion.setPath(dirRaiz + "/" + *historia);
            lista = dirLesion.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot);

            if(lista.count() >= 1)
                abrirLesion = true;
            else
                abrirLesion = false;

            cerrarLesion = false;
            eliminarLesion = false;
            cBoxModo = false;
            abrirCarpeta = false;
            generarReporte = false;
            ui->etqInfoLesion->setText("- - -");
            ui->etqInfoFecha->setText("- - -");
        }
    }else{
        *fechaLesion = fecha;
        //si la camara sigue activa, muestra el mensaje siguiente
        if(capWebcam.isOpened()){
            crearHistoria = true;
        }else{
            crearHistoria = false;
        }

        dirHist.setPath(dirRaiz);
        lista = dirHist.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot);

        if(lista.count() >= 1)
            abrirHistoria = true;
        else
            abrirHistoria = false;

        cerrarHistoria = false;
        eliminarLesion = false;
        nuevaLesion = false;
        abrirLesion = false;
        cerrarLesion = false;
        eliminarLesion = false;
        cBoxModo = false;
        abrirCarpeta = false;
        generarReporte = false;
        ui->etqInfoHistoria->setText("- - -");
        ui->etqInfoLesion->setText("- - -");
        ui->etqInfoFecha->setText("- - -");
    }

    if(capWebcam.isOpened())
        ui->etqInfoEstado->setText("Conectada");
    else
        ui->etqInfoEstado->setText("Desconectada");

    ui->actionCrear_historia->setEnabled(crearHistoria);
    ui->actionAbrir_historia->setEnabled(abrirHistoria);
    ui->actionCerrar_historia->setEnabled(cerrarHistoria);
    ui->actionEliminar_historia->setEnabled(eliminarHistoria);
    ui->actionNueva_lesion->setEnabled(nuevaLesion);
    ui->actionAbrir_lesion->setEnabled(abrirLesion);
    ui->actionCerrar_lesion->setEnabled(cerrarLesion);
    ui->actionEliminar_lesion->setEnabled(eliminarLesion);
    ui->cBoxModo->setEnabled(cBoxModo);
    ui->btnAbrirCarpeta->setEnabled(abrirCarpeta);
    ui->btnGenerarReporte->setEnabled(generarReporte);

    ui->cBoxModo->setCurrentIndex(0);
}

/*Indice 0: Seleccionar
  Indice 1: Capturar
  Indice 2: Visualizar*/
void MainWindow::on_cBoxModo_currentIndexChanged(int index){

    //si se elige modo de captura o modo de visualizacion
    if(index != 0){
        //si la seleccion esta en modo captura y la camara esta activa, habilita los botones para capturar las fotos
        if(index == 1){
            //solamente se pueden capturar imagenes de una lesion cuya fecha sea la del dia actual
            if(*fechaLesion == fecha){

                if(capWebcam.isOpened()){
                    setBotones(true);

                    if(!tmrTimer->isActive())
                        tmrTimer->start(30);
                }else
                    setBotones(false);
            }else
                setBotones(false);
        }

        if(index == 2){
            if(tmrTimer->isActive())
                tmrTimer->stop();
            QPixmap pixDummy(0, 0);
            ui->etqCamara->setPixmap(pixDummy);
            //si la camara esta en modo de visualizacion
            QStringList colores;

            colores << "Amarillo" << "Azul" << "Blanco" << "Cyan" << "Magenta" << "Rojo" << "Verde";

            for(int i = 0; i < colores.size(); i++){

                setColorDisponible(colores.indexOf(colores.at(i)));
            }
        }

    }else{
        if(tmrTimer->isActive())
            tmrTimer->stop();
        //borra la imagen que este en la vista previa y en la camara
        QPixmap pixDummy(0, 0);
        ui->etqCamara->setPixmap(pixDummy);
        ui->etqVistaprevia->setPixmap(pixDummy);
        //desabilitar todos los botones, excepto seleccionar
        setBotones(false);
    }
}

void MainWindow::setBotones(bool flag){

    ui->btnAmarillo->setEnabled(flag);
    ui->btnAzul->setEnabled(flag);
    ui->btnBlanco->setEnabled(flag);
    ui->btnCyan->setEnabled(flag);
    ui->btnMagenta->setEnabled(flag);
    ui->btnRojo->setEnabled(flag);
    ui->btnVerde->setEnabled(flag);
}

void MainWindow::accionBotones(QString color){

    QString nombreImagen(dirRaiz + "/" + *historia + "/" + *lesion + "/" + *fechaLesion + "/" + color + " - " + *fechaLesion + ".jpg");
    QFileInfo archivo(nombreImagen);
    int w, h;

    //si la interfaz esta en modo de captura de imagenes
    if(ui->cBoxModo->currentIndex() == 1){

        QDir dir;
        dir.mkpath(dirRaiz + "/" + *historia + "/" + *lesion + "/" + *fechaLesion);
        QImage imgCapturada(qimg.copy());
        QFileInfo archivo(nombreImagen);

        if(!archivo.exists()){
            imgCapturada.save(nombreImagen);
            w = ui->etqVistaprevia->width();
            h = ui->etqVistaprevia->height();
            //se le asigna la imagen a la etiqueta de la camara
            ui->etqVistaprevia->setPixmap((QPixmap::fromImage(qimg)).scaled(w, h, Qt::KeepAspectRatio));
        }else{

            dlgConfirmar conf("La imagen de color: " + color + " ya existe, desea reemplazarla?", "Reemplazar imagen");
            conf.exec();

            bool reemplazar = conf.confirmacion();

            if(reemplazar){
                imgCapturada.save(nombreImagen);
                w = ui->etqVistaprevia->width();
                h = ui->etqVistaprevia->height();
                //se le asigna la imagen a la etiqueta de la camara
                ui->etqVistaprevia->setPixmap((QPixmap::fromImage(qimg)).scaled(w, h, Qt::KeepAspectRatio));
            }
        }

    }else{
    //si la interfaz esta en modo de visualizacion de imagenes
        dlgImagen *imagen = new dlgImagen(nombreImagen, color, dirRaiz + "/" + *historia + "/" + *lesion, *fechaLesion);
        imagen->exec();
    }

    if(archivo.exists()){

        QImage imagen(nombreImagen);
        w = ui->etqVistaprevia->width();
        h = ui->etqVistaprevia->height();
        ui->etqVistaprevia->setPixmap((QPixmap::fromImage(imagen)).scaled(w, h, Qt::KeepAspectRatio));
    }else{
        //borra la imagen que este en la vista previa
        QPixmap pixDummy(0, 0);
        ui->etqVistaprevia->setPixmap(pixDummy);
    }
}

void MainWindow::setColorDisponible(int colorIndex){

    QString nombreImagen, ruta;
    QFileInfo archivo;

    ruta = dirRaiz + "/" + *historia + "/" + *lesion + "/" + *fechaLesion;

    switch (colorIndex) {

    case 0:
        nombreImagen = (ruta + "/" + "Amarillo - " + *fechaLesion + ".jpg");
        archivo.setFile(nombreImagen);
        if(archivo.exists())
            ui->btnAmarillo->setEnabled(true);
        else
            ui->btnAmarillo->setEnabled(false);
        break;

    case 1:
        nombreImagen = (ruta + "/" + "Azul - " + *fechaLesion + ".jpg");
        archivo.setFile(nombreImagen);
        if(archivo.exists())
            ui->btnAzul->setEnabled(true);
        else
            ui->btnAzul->setEnabled(false);
        break;

    case 2:
        nombreImagen = (ruta + "/" + "Blanco - " + *fechaLesion + ".jpg");
        archivo.setFile(nombreImagen);
        if(archivo.exists())
            ui->btnBlanco->setEnabled(true);
        else
            ui->btnBlanco->setEnabled(false);
        break;

    case 3:
        nombreImagen = (ruta + "/" + "Cyan - " + *fechaLesion + ".jpg");
        archivo.setFile(nombreImagen);
        if(archivo.exists())
            ui->btnCyan->setEnabled(true);
        else
            ui->btnCyan->setEnabled(false);
        break;

    case 4:
        nombreImagen = (ruta + "/" + "Magenta - " + *fechaLesion + ".jpg");
        archivo.setFile(nombreImagen);
        if(archivo.exists())
            ui->btnMagenta->setEnabled(true);
        else
            ui->btnMagenta->setEnabled(false);
        break;

    case 5:
        nombreImagen = (ruta + "/" + "Rojo - " + *fechaLesion + ".jpg");
        archivo.setFile(nombreImagen);
        if(archivo.exists())
            ui->btnRojo->setEnabled(true);
        else
            ui->btnRojo->setEnabled(false);
        break;

    case 6:
        nombreImagen = (ruta + "/" + "Verde - " + *fechaLesion + ".jpg");
        archivo.setFile(nombreImagen);
        if(archivo.exists())
            ui->btnVerde->setEnabled(true);
        else
            ui->btnVerde->setEnabled(false);
        break;

    default:
        break;
    }
}

void MainWindow::on_btnRojo_clicked(){

    accionBotones("Rojo");
}

void MainWindow::on_btnVerde_clicked(){

    accionBotones("Verde");
}

void MainWindow::on_btnAzul_clicked(){

    accionBotones("Azul");
}

void MainWindow::on_btnCyan_clicked(){

    accionBotones("Cyan");
}

void MainWindow::on_btnMagenta_clicked(){

    accionBotones("Magenta");
}

void MainWindow::on_btnAmarillo_clicked(){

    accionBotones("Amarillo");
}

void MainWindow::on_btnBlanco_clicked(){

    accionBotones("Blanco");
}

void MainWindow::on_btnGenerarReporte_clicked(){

}

void MainWindow::on_actionNueva_lesion_triggered(){

    crearLesion nuevaLesion(dirRaiz, *historia, lesion);
    nuevaLesion.exec();

    revision();
}

void MainWindow::on_actionAbrir_historia_triggered(){

    abrirHistoria abrirH(historia, lesion, dirRaiz);
    abrirH.exec();

    revision();
}

void MainWindow::on_actionAbrir_lesion_triggered(){

    abrirLesion abrirL(lesion, dirRaiz + "/" + *historia, fechaLesion);
    abrirL.exec();

    revision();
}

void MainWindow::on_actionEliminar_historia_triggered(){

    eliminarHistoria elim(dirRaiz, historia, lesion);
    elim.exec();
    revision();
}

void MainWindow::on_actionEliminar_lesion_triggered(){

    dlgConfirmar conf("Seguro que desea eliminar la lesion: " + *lesion + "?", "Eliminar lesion");
    conf.exec();

    if(conf.confirmacion()){

        QDir dir;
        dir.setPath(dirRaiz + "/" + *historia + "/" + *lesion);
        dir.removeRecursively();
        dlgInfo info("La lesion se elimino correctamente.", "Lesion eliminada");
        info.exec();

        *lesion = "";
        revision();
    }
}

void MainWindow::on_btnAbrirCarpeta_clicked(){

    QString path = QDir::toNativeSeparators(dirRaiz);
    QDesktopServices::openUrl(QUrl("file:///" + path + "/" + *historia + "/" + *lesion));
}
