#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){

    ui->setupUi(this);
    txtCamara = ui->etqCamara->text();
    txtVistaPrev = ui->etqVistaprevia->text();
    dirRaiz = QDir::homePath() + "/" + "Dermasoft - Historias";
    fecha = QDate::currentDate().toString("dd.MM.yyyy");
    fechaIcon = new QString(fecha);
    tmrTimer = new QTimer;
    historia = new QString;
    icon = new QString;
    //conecta el timer con la actualizacion del cuadro de la GUI
    connect(tmrTimer, SIGNAL(timeout()), this, SLOT(procesarCuadroActualizarGUI()));
    QDir dir;
    dir.setPath(dirRaiz);

    if(!dir.exists())
        dir.mkdir(dirRaiz);

    dlgInfo info("Verifique que el dispositivo este conectado antes de empezar.", "Atencion", "Listo");
    info.exec();

    this->adjustSize();
    this->setFixedSize(this->size());

    numCams = 0;
    signalMapper = new QSignalMapper;
    ui->actionActualizar->trigger();
    revision();
}

MainWindow::~MainWindow(){ delete ui; }

void MainWindow::procesarCuadroActualizarGUI(){
    cv::Mat mAux;
    cam >> (mat);
    cam >> (mAux);
    //se prepara la imagen para convertirla de BGR A RGB para que Qt pueda manejarla
    cv::cvtColor(mat, mat, CV_BGR2RGB);
    //ocurre la conversion de cv mat a qimage. Investigar sobre cual QImage::Format_ es mas apropiado
    QImage imgAux((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
    QImage imgAux2((uchar*)mAux.data, mAux.cols, mAux.rows, mAux.step, QImage::Format_RGB888);

    if(!imgAux2.allGray()){
        qimg = imgAux;
        //se obtiene al largo y ancho de la imagen capturada
        int w = ui->etqCamara->width();
        int h = ui->etqCamara->height();
        //se le asigna la imagen a la etiqueta de la camara
        ui->etqCamara->setPixmap((QPixmap::fromImage(qimg)).scaled(w, h, Qt::KeepAspectRatio));
    }else{
        ui->actionDesconectar_camara->trigger();
        ui->actionActualizar->trigger();
        revision();
    }
}

void MainWindow::conectarCamaras(int num){
    //si la camara no ha sido abierta
    if(!cam.isOpened()){

        cam.open(num);/*Abre la camara web*/

        if(!cam.isOpened()){
            dlgInfo info("Porfavor verifique que la camara este conectada.", "Error al conectar la camara");
            info.exec();
        }else{
            indexCam = num;
            revision();

            if(!historia->isEmpty() && !icon->isEmpty()){

                if(*fechaIcon == fecha)
                    ui->cBoxModo->setCurrentIndex(1);
                else
                    ui->cBoxModo->setCurrentIndex(2);
            }else
                ui->cBoxModo->setCurrentIndex(0);
        }
    }
}

void MainWindow::on_actionDesconectar_camara_triggered(){

    cam.release();
    //borra la imagen que haya quedado en la etiqueta de la camara
    ui->etqCamara->clear();
    ui->etqCamara->setText(txtCamara);
    ui->etqVistaprevia->clear();
    ui->etqVistaprevia->setText(txtVistaPrev);
    revision();

    if(!historia->isEmpty() && !icon->isEmpty()){
        ui->cBoxModo->setCurrentIndex(2);
    }else
        ui->cBoxModo->setCurrentIndex(0);
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
    ui->cBoxModo->setCurrentIndex(0);

    if(!historia->isEmpty() && cam.isOpened()){

        regAbrirIcon reg(true, false);
        reg.exec();

        if(reg.selecciono()){
            ui->actionRegistrar_Iconografia->trigger();
        }
    }
}

void MainWindow::on_actionCerrar_historia_triggered(){

    //cuando se cierra una historia, se debe cerrar la icon de dicha historia tambien
    *historia = "";
    *icon = "";
    revision();
    ui->cBoxModo->setCurrentIndex(0);
}

void MainWindow::on_actionRegistrar_Iconografia_triggered(){

    regIcon n(dirRaiz, *historia, icon);
    n.exec();

    revision();

    if(!icon->isEmpty())
        ui->cBoxModo->setCurrentIndex(1);
    else
        ui->cBoxModo->setCurrentIndex(0);
}

void MainWindow::on_actionCerrar_icon_triggered(){

    *icon = "";
    revision();
    ui->cBoxModo->setCurrentIndex(0);
}

//Realiza una revision de la historia, la icon y la fecha, habilitando y deshabilitando los botones segun sea el caso
void MainWindow::revision(){

    bool actualizar, conectar, desconectar, crearHistoria, abrirHistoria, verHistoria, cerrarHistoria, regIcon, abrirIcon, cerrarIcon, cBoxModo, abrirCarpeta;
    QDir dirHist, dirIcon, dirFecha;
    QFileInfoList lista;

    //Si hay una historia cargada
    if(!historia->isEmpty()){
        crearHistoria = false;
        abrirHistoria = true;
        verHistoria = true;
        cerrarHistoria = true;
        ui->etqInfoHistoria->setText(*historia);
        if(!icon->isEmpty()){
            regIcon = false;
            abrirIcon = true;
            cerrarIcon = true;
            cBoxModo = true;

            dirFecha.setPath(dirRaiz + "/" + *historia + "/" + *icon + "/" + *fechaIcon);

            if(dirFecha.exists())
                abrirCarpeta = true;
            else
                abrirCarpeta = false;

            ui->etqInfoIcon->setText(*icon);
            ui->etqInfoFecha->setText(QDate::fromString(*fechaIcon, "dd.MM.yyyy").toString("dd/MM/yyyy"));
        }else{
            //Si hay una historia pero no hay una icon, deshabilita la seleccin de modos
            *fechaIcon = fecha;

            if(cam.isOpened()){
                regIcon = true;
            }else{
                regIcon = false;
            }

            dirIcon.setPath(dirRaiz + "/" + *historia);
            lista = dirIcon.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot);

            if(lista.count() >= 1)
                abrirIcon = true;
            else
                abrirIcon = false;

            cerrarIcon = false;
            cBoxModo = false;
            abrirCarpeta = false;
            ui->etqInfoIcon->setText("- - -");
            ui->etqInfoFecha->setText("- - -");
        }
    }else{
        *fechaIcon = fecha;
        //si la camara sigue activa, muestra el mensaje siguiente
        if(cam.isOpened()){
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

        verHistoria = false;
        cerrarHistoria = false;
        regIcon = false;
        abrirIcon = false;
        cerrarIcon = false;
        cBoxModo = false;
        abrirCarpeta = false;
        ui->etqInfoHistoria->setText("- - -");
        ui->etqInfoIcon->setText("- - -");
        ui->etqInfoFecha->setText("- - -");
    }

    if(cam.isOpened()){
        actualizar = false;
        conectar = false;
        desconectar = true;
        ui->etqInfoEstado->setText("<html><head/><body><p><span style= 'font-weight:600; color:#29bf33;'>Conectada</span></p></body></html>");
    }else{

        actualizar = true;

        if(numCams > 0){
            conectar = true;
        }else
            conectar = false;

        desconectar = false;
        ui->etqInfoEstado->setText("<html><head/><body><p><span style= 'font-weight:600; color:#c81d1d;'>Desconectada</span></p></body></html>");
    }

    ui->actionActualizar->setEnabled(actualizar);
    ui->menuCamaras->setEnabled(conectar);
    ui->actionDesconectar_camara->setEnabled(desconectar);
    ui->actionCrear_historia->setEnabled(crearHistoria);
    ui->actionAbrir_historia->setEnabled(abrirHistoria);
    ui->actionVer_historia->setEnabled(verHistoria);
    ui->actionCerrar_historia->setEnabled(cerrarHistoria);
    ui->actionRegistrar_Iconografia->setEnabled(regIcon);
    ui->actionAbrir_icon->setEnabled(abrirIcon);
    ui->actionCerrar_icon->setEnabled(cerrarIcon);
    ui->cBoxModo->setEnabled(cBoxModo);

    ui->btnAbrirCarpeta->setEnabled(abrirCarpeta);
}

/*Indice 0: Seleccionar
  Indice 1: Capturar
  Indice 2: Visualizar*/
void MainWindow::on_cBoxModo_currentIndexChanged(int index){

    //si se elige modo de captura o modo de visualizacion
    if(index != 0){
        //si la seleccion esta en modo captura y la camara esta activa, habilita los botones para capturar las fotos
        if(index == 1){
            //solamente se pueden capturar imagenes de una icon cuya fecha sea la del dia actual
            if(*fechaIcon == fecha){

                if(cam.isOpened()){
                    setBotones(true);

                    if(!tmrTimer->isActive())
                        tmrTimer->start(20);
                }else
                    setBotones(false);
            }else
                setBotones(false);
        }

        if(index == 2){
            if(tmrTimer->isActive())
                tmrTimer->stop();

            ui->etqCamara->clear();
            ui->etqCamara->setText(txtCamara);
            ui->etqVistaprevia->clear();
            ui->etqVistaprevia->setText(txtVistaPrev);
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
        ui->etqCamara->clear();
        ui->etqCamara->setText(txtCamara);
        ui->etqVistaprevia->clear();
        ui->etqVistaprevia->setText(txtVistaPrev);
        //desabilitar todos los botones, excepto seleccionar
        setBotones(false);
    }
    revision();
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

    QString nombreImagen(dirRaiz + "/" + *historia + "/" + *icon + "/" + *fechaIcon + "/" + color + " - " + *fechaIcon + ".jpg");
    QFileInfo archivo(nombreImagen);
    int w, h;

    //si la interfaz esta en modo de captura de imagenes
    if(ui->cBoxModo->currentIndex() == 1){

        QDir dir;
        dir.mkpath(dirRaiz + "/" + *historia + "/" + *icon + "/" + *fechaIcon);
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
        dlgImagen *imagen = new dlgImagen(nombreImagen, color, dirRaiz + "/" + *historia + "/" + *icon, *fechaIcon);
        imagen->exec();
    }

    if(archivo.exists()){

        QImage imagen(nombreImagen);
        w = ui->etqVistaprevia->width();
        h = ui->etqVistaprevia->height();
        ui->etqVistaprevia->setPixmap((QPixmap::fromImage(imagen)).scaled(w, h, Qt::KeepAspectRatio));
    }else{
        //borra la imagen que este en la vista previa
        ui->etqVistaprevia->clear();
        ui->etqVistaprevia->setText(txtVistaPrev);
    }
    revision();
}

void MainWindow::setColorDisponible(int colorIndex){

    QString nombreImagen, ruta;
    QFileInfo archivo;

    ruta = dirRaiz + "/" + *historia + "/" + *icon + "/" + *fechaIcon;

    switch (colorIndex) {

    case 0:
        nombreImagen = (ruta + "/" + "Amarillo - " + *fechaIcon + ".jpg");
        archivo.setFile(nombreImagen);
        if(archivo.exists())
            ui->btnAmarillo->setEnabled(true);
        else
            ui->btnAmarillo->setEnabled(false);
        break;

    case 1:
        nombreImagen = (ruta + "/" + "Azul - " + *fechaIcon + ".jpg");
        archivo.setFile(nombreImagen);
        if(archivo.exists())
            ui->btnAzul->setEnabled(true);
        else
            ui->btnAzul->setEnabled(false);
        break;

    case 2:
        nombreImagen = (ruta + "/" + "Blanco - " + *fechaIcon + ".jpg");
        archivo.setFile(nombreImagen);
        if(archivo.exists())
            ui->btnBlanco->setEnabled(true);
        else
            ui->btnBlanco->setEnabled(false);
        break;

    case 3:
        nombreImagen = (ruta + "/" + "Cyan - " + *fechaIcon + ".jpg");
        archivo.setFile(nombreImagen);
        if(archivo.exists())
            ui->btnCyan->setEnabled(true);
        else
            ui->btnCyan->setEnabled(false);
        break;

    case 4:
        nombreImagen = (ruta + "/" + "Magenta - " + *fechaIcon + ".jpg");
        archivo.setFile(nombreImagen);
        if(archivo.exists())
            ui->btnMagenta->setEnabled(true);
        else
            ui->btnMagenta->setEnabled(false);
        break;

    case 5:
        nombreImagen = (ruta + "/" + "Rojo - " + *fechaIcon + ".jpg");
        archivo.setFile(nombreImagen);
        if(archivo.exists())
            ui->btnRojo->setEnabled(true);
        else
            ui->btnRojo->setEnabled(false);
        break;

    case 6:
        nombreImagen = (ruta + "/" + "Verde - " + *fechaIcon + ".jpg");
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

void MainWindow::on_actionAbrir_historia_triggered(){

    abrirHistoria abrir(historia, icon, dirRaiz);
    abrir.exec();

    revision();
    ui->cBoxModo->setCurrentIndex(0);

    if(!historia->isEmpty()){
        QDir aux;
        aux.setPath(dirRaiz + "/" + *historia);
        aux.setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
        bool existenIcon;

        if(aux.entryList().count() > 0)
            existenIcon = true;
        else
            existenIcon = false;

        if(cam.isOpened() || existenIcon){
            regAbrirIcon regAbrir(cam.isOpened(), existenIcon);
            regAbrir.exec();

            if(regAbrir.selecciono()){
                if(regAbrir.opcionNueva()){
                    ui->actionRegistrar_Iconografia->trigger();
                }else if(existenIcon){
                    ui->actionAbrir_icon->trigger();
                }
            }
        }
    }
}

void MainWindow::on_actionAbrir_icon_triggered(){

    abrirIcon abrirL(icon, dirRaiz + "/" + *historia, fechaIcon);
    abrirL.exec();

    revision();

    if(!icon->isEmpty()){

        if(*fechaIcon == fecha && cam.isOpened())
            ui->cBoxModo->setCurrentIndex(1);
        else
            ui->cBoxModo->setCurrentIndex(2);
    }else
        ui->cBoxModo->setCurrentIndex(0);
}

void MainWindow::on_btnAbrirCarpeta_clicked(){

    QString path = QDir::toNativeSeparators(dirRaiz);
    QDesktopServices::openUrl(QUrl("file:///" + path + "/" + *historia + "/" + *icon + "/" + *fechaIcon));
}

void MainWindow::on_actionVer_historia_triggered(){

    verHistoria ver(dirRaiz, *historia);
    ver.exec();
}

void MainWindow::on_actionActualizar_triggered(){

    int i;

    disconnect(signalMapper, SIGNAL(mapped(int)), this, SLOT(conectarCamaras(int)));

    for(i = 0; i < numCams; i++){
        signalMapper->removeMappings(accionesDinamicas.at(i));
        disconnect(accionesDinamicas.at(i), SIGNAL(triggered()), signalMapper, SLOT(map()));
        accionesDinamicas.removeAt(i);
    }

    indexCam = -1;//valor por defecto del indice de la camara
    cv::VideoCapture camaras;
    i = numCams = 0;
    double w, h;
    bool flag = true;
    ui->menuCamaras->clear();

    while(flag){
        camaras.open(i);
        if(camaras.isOpened()){
            w = camaras.get(CV_CAP_PROP_FRAME_WIDTH);
            h = camaras.get(CV_CAP_PROP_FRAME_HEIGHT);
            accionesDinamicas.insert(i, ui->menuCamaras->addAction("Camara " + QString::number(i + 1) + " - " + QString::number(w) + "x" + QString::number(h)));
            connect(accionesDinamicas.at(i), SIGNAL(triggered()), signalMapper, SLOT(map()));
            signalMapper->setMapping(accionesDinamicas.at(i), i);
            numCams+=1;
            camaras.release();
        }else
            flag = false;
        i++;
    }
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(conectarCamaras(int)));

    if(numCams > 0)
        conectarCamaras(0);
    else
        ui->actionConectar_camara->setEnabled(false);

    setBotones(false);
    ui->cBoxModo->setCurrentIndex(0);
}
