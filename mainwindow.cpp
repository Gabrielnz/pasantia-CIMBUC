#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){

    ui->setupUi(this);
    //conectando los signals y slots del hilo de captura de imagenes
    connect(&captura, &objCaptura::nueva_imagen, this, &MainWindow::procesar_imagen);
    connect(&captura, &objCaptura::interrumpirConexion, this, &MainWindow::conexionInterrumpida);
    connect(this, &MainWindow::on_stop, &captura, &objCaptura::stop);
    connect(&captura, &objCaptura::limpiarVista, this, &MainWindow::limpiarVista);

    txtCamara = ui->etqCamara->text();
    txtVistaPrev = ui->etqVistaprevia->text();
    dirRaiz = QDir::homePath() + "/" + "Dermasoft - Historias";
    fecha = QDate::currentDate().toString("dd.MM.yyyy");
    fechaIcon = new QString(fecha);
    historia = new QString;
    icon = new QString;
    w = ui->etqCamara->width();
    h = ui->etqCamara->height();

    QDir dir;
    dir.setPath(dirRaiz);

    if(!dir.exists())
        dir.mkdir(dirRaiz);

    //Mapea los SIGNAL clicked() de todos los botones de colores al mismo SLOT accionColores(QString)
    colores << "Amarillo" << "Azul" << "Blanco" << "Cyan" << "Magenta" << "Rojo" << "Verde";
    int nColores = colores.size();
    btnsColores.push_back(ui->btnAmarillo);
    btnsColores.push_back(ui->btnAzul);
    btnsColores.push_back(ui->btnBlanco);
    btnsColores.push_back(ui->btnCyan);
    btnsColores.push_back(ui->btnMagenta);
    btnsColores.push_back(ui->btnRojo);
    btnsColores.push_back(ui->btnVerde);

    for(int i = 0; i < nColores; ++i){
        connect(btnsColores.at(i), SIGNAL(clicked()), &coloresMapper, SLOT(map()));
        coloresMapper.setMapping(btnsColores.at(i), colores.at(i));
    }
    connect(&coloresMapper, SIGNAL(mapped(QString)), this, SLOT(accionColores(QString)));

    dlgInfo info("Verifique que el dispositivo este conectado antes de empezar.", "Atencion", "Listo");
    info.exec();

    conectado = false;
    numCams = 0;
    //actualiza la lista de dispositivos la primera vez, y en caso de que haya al menos 1 disponible, lo conecta
    ui->actionActualizar->trigger();

    if(numCams > 0){
        conectar(0);
    }

    this->adjustSize();
    this->setFixedSize(this->size());
}

MainWindow::~MainWindow(){
    if(hiloCaptura.isRunning())
        emit on_stop();

    delete ui;
}

void MainWindow::conectar(int num){
    //si la camara no ha sido abierta
    if(!conectado){

        conectado = true;
        ui->etqInfoEstado->setText("<html><head/><body><p><span style= 'font-weight:600; color:#29bf33;'>Conectada</span></p></body></html>");
        indexCam = num;

        if(!historia->isEmpty() && !icon->isEmpty()){

            if(*fechaIcon == fecha){
                ui->cBoxModo->activated(1);
            }else{
                ui->cBoxModo->activated(2);
            }
        }else{
            ui->cBoxModo->activated(0);
        }
    }
}

void MainWindow::on_actionDesconectar_camara_triggered(){

    if(conectado){
        conectado = false;
        if(hiloCaptura.isRunning())
            emit on_stop();

        ui->etqInfoEstado->setText("<html><head/><body><p><span style= 'font-weight:600; color:#c81d1d;'>Desconectada</span></p></body></html>");

        if(!historia->isEmpty() && !icon->isEmpty()){
            ui->cBoxModo->activated(2);
        }else
            ui->cBoxModo->activated(0);
    }
}

void MainWindow::on_actionSalir_triggered(){ close();}

void MainWindow::on_actionAcerca_de_triggered(){

    AcercaDe mensaje;
    mensaje.exec();
}

void MainWindow::on_actionCrear_historia_triggered(){

    crearHistoria crear(dirRaiz, historia);
    crear.exec();

    if(!historia->isEmpty()){

        ui->etqInfoHistoria->setText(*historia);
        ui->actionRegistrar_Iconografia->trigger();
    }else{
        ui->etqInfoHistoria->setText("- - -");
        ui->etqInfoIcon->setText("- - -");
        ui->etqInfoFecha->setText("- - -");
        *fechaIcon = fecha;
        ui->cBoxModo->activated(0);
    }
}

void MainWindow::on_actionAbrir_historia_triggered(){

    abrirHistoria abrir(historia, icon, dirRaiz);
    abrir.exec();

    if(!historia->isEmpty()){

        ui->etqInfoHistoria->setText(*historia);

        QDir aux;
        aux.setPath(dirRaiz + "/" + *historia);
        aux.setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
        bool existenIcon;

        if(aux.entryList().size() > 0)
            existenIcon = true;
        else
            existenIcon = false;

        if(conectado || existenIcon){

            if(!existenIcon){
                ui->actionRegistrar_Iconografia->trigger();
            }else{

                if(!conectado){
                    ui->actionAbrir_icon->trigger();
                }else{

                    regAbrirIcon regAbrir(conectado, existenIcon);
                    regAbrir.exec();

                    if(regAbrir.selecciono()){
                        if(regAbrir.opcionNueva()){
                            ui->actionRegistrar_Iconografia->trigger();
                        }else if(existenIcon){
                            ui->actionAbrir_icon->trigger();
                        }
                    }else{
                        ui->cBoxModo->activated(0);
                    }
                }
            }
        }else{
            dlgInfo info("Esta histora no contiene iconografias para abrir.", "Historia vacia", "Entendido");
            info.exec();
            ui->cBoxModo->activated(0);
        }
    }else{
        ui->etqInfoHistoria->setText("- - -");
        ui->etqInfoIcon->setText("- - -");
        ui->etqInfoFecha->setText("- - -");
        *fechaIcon = fecha;
        ui->cBoxModo->activated(0);
    }
}

void MainWindow::on_actionCerrar_historia_triggered(){

    ui->etqInfoHistoria->setText("- - -");
    ui->etqInfoIcon->setText("- - -");
    ui->etqInfoFecha->setText("- - -");
    //cuando se cierra una historia, se debe cerrar la icon de dicha historia tambien
    *historia = "";
    *icon = "";
    *fechaIcon = fecha;
    limpiarVista();
    ui->cBoxModo->activated(0);
}

void MainWindow::on_actionRegistrar_Iconografia_triggered(){

    regIcon n(dirRaiz, *historia, icon);
    n.exec();

    if(!icon->isEmpty()){
        ui->etqInfoIcon->setText(*icon);
        ui->etqInfoFecha->setText(QDate::fromString(*fechaIcon, "dd.MM.yyyy").toString("dd/MM/yyyy"));
        ui->cBoxModo->activated(1);
    }else{
        ui->etqInfoIcon->setText("- - -");
        ui->etqInfoFecha->setText("- - -");
        *fechaIcon = fecha;
        ui->cBoxModo->activated(0);
    }
}

void MainWindow::on_actionAbrir_icon_triggered(){

    abrirIcon abrirI(icon, dirRaiz + "/" + *historia, fechaIcon);
    abrirI.exec();

    if(!icon->isEmpty()){

        ui->etqInfoIcon->setText(*icon);
        ui->etqInfoFecha->setText(QDate::fromString(*fechaIcon, "dd.MM.yyyy").toString("dd/MM/yyyy"));

        if(conectado && *fechaIcon == fecha)
            ui->cBoxModo->activated(1);
        else
            ui->cBoxModo->activated(2);
    }else{
        ui->etqInfoIcon->setText("- - -");
        ui->etqInfoFecha->setText("- - -");
        *fechaIcon = fecha;
        ui->cBoxModo->activated(0);
    }
}

void MainWindow::on_actionCerrar_icon_triggered(){

    ui->etqInfoIcon->setText("- - -");
    ui->etqInfoFecha->setText("- - -");
    *icon = "";
    *fechaIcon = fecha;
    limpiarVista();
    ui->cBoxModo->activated(0);
}

//Realiza una revision de todos los botones, habilitando/deshabilitando segun el caso
void MainWindow::revisionBtns(){

    bool actualizar, conectar, desconectar, crearHistoria, abrirHistoria, verHistoria, cerrarHistoria, regIcon, abrirIcon, cerrarIcon, cBoxModo, habColores, abrirCarpeta;
    QDir dirHist, dirIcon, dirFecha;
    QFileInfoList lista;
    //revisa los botones para conectar, actualizar y desconectar la camara
    if(conectado){
        actualizar = false;
        conectar = false;
        desconectar = true;
    }else{

        actualizar = true;
        desconectar = false;

        if(numCams > 0){
            conectar = true;
        }else
            conectar = false;
    }
    //revisa la historia, la iconografia y la fecha
    if(!historia->isEmpty()){
        crearHistoria = false;
        abrirHistoria = false;
        verHistoria = true;
        cerrarHistoria = true;
        if(!icon->isEmpty()){
            regIcon = false;
            abrirIcon = false;
            cerrarIcon = true;
            cBoxModo = true;

            dirFecha.setPath(dirRaiz + "/" + *historia + "/" + *icon + "/" + *fechaIcon);

            if(dirFecha.exists()){
                abrirCarpeta = true;
            }else{
                abrirCarpeta = false;
            }
        }else{
            //Si hay una historia pero no hay una icon, deshabilita la seleccin de modos

            if(conectado){
                regIcon = true;
            }else{
                regIcon = false;
            }

            dirIcon.setPath(dirRaiz + "/" + *historia);
            lista = dirIcon.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot);

            if(lista.size() > 0)
                abrirIcon = true;
            else
                abrirIcon = false;

            cerrarIcon = cBoxModo = abrirCarpeta = false;
        }
    }else{
        //si la camara sigue activa, muestra el mensaje siguiente
        if(conectado){
            crearHistoria = true;
        }else{
            crearHistoria = false;
        }

        dirHist.setPath(dirRaiz);
        lista = dirHist.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot);

        if(lista.size() > 0)
            abrirHistoria = true;
        else
            abrirHistoria = false;

        verHistoria = cerrarHistoria = regIcon = abrirIcon = cerrarIcon = cBoxModo = abrirCarpeta = false;
    }
    //revisa los botones de captura/visualizacion de colores
    switch (ui->cBoxModo->currentIndex()){

    case 1:
        if(conectado && !historia->isEmpty() && !icon->isEmpty() && *fechaIcon == fecha)
            habColores = true;
        else
            habColores = false;

        abrirCarpeta = false;
        habilitarColores(habColores);
        break;

    case 2:
        disponibilidadColores();
        break;

    default:
        habColores = abrirCarpeta = false;
        habilitarColores(false);
        break;
    }
    ui->actionActualizar->setEnabled(actualizar);
    ui->actionConectar_camara->setEnabled(conectar);
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

void MainWindow::habilitarColores(bool flag){

    foreach (QPushButton *btn, btnsColores) {
        btn->setEnabled(flag);
    }
}

void MainWindow::accionColores(QString color){

    QString nombreImagen(dirRaiz + "/" + *historia + "/" + *icon + "/" + *fechaIcon + "/" + *historia + " - " + *icon + " - " + *fechaIcon + " - " + color + ".jpg");
    QFileInfo archivo(nombreImagen);
    int wPrev, hPrev;

    //si la interfaz esta en modo de captura de imagenes
    if(ui->cBoxModo->currentIndex() == 1){

        QDir dir;
        dir.mkpath(dirRaiz + "/" + *historia + "/" + *icon + "/" + *fechaIcon);
        QImage imgCapturada(img.copy());
        QFileInfo archivo(nombreImagen);

        if(!archivo.exists()){
            imgCapturada.save(nombreImagen);
            wPrev = ui->etqVistaprevia->width();
            hPrev = ui->etqVistaprevia->height();
            //se le asigna la imagen a la etiqueta de la camara
            ui->etqVistaprevia->setPixmap((QPixmap::fromImage(img)).scaled(wPrev, hPrev, Qt::KeepAspectRatio));
        }else{

            dlgConfirmar conf("La imagen de color: " + color + " ya existe, desea reemplazarla?", "Reemplazar imagen");
            conf.exec();

            bool reemplazar = conf.confirmacion();

            if(reemplazar){
                imgCapturada.save(nombreImagen);
                wPrev = ui->etqVistaprevia->width();
                hPrev = ui->etqVistaprevia->height();
                //se le asigna la imagen a la etiqueta de la camara
                ui->etqVistaprevia->setPixmap((QPixmap::fromImage(img)).scaled(wPrev, hPrev, Qt::KeepAspectRatio));
            }
        }

    }else{
    //si la interfaz esta en modo de visualizacion de imagenes
        dlgImagen *imagen = new dlgImagen(nombreImagen, color, dirRaiz + "/" + *historia + "/" + *icon, *fechaIcon);
        imagen->exec();
    }

    if(archivo.exists()){

        QImage imagen(nombreImagen);
        wPrev = ui->etqVistaprevia->width();
        hPrev = ui->etqVistaprevia->height();
        ui->etqVistaprevia->setPixmap((QPixmap::fromImage(imagen)).scaled(wPrev, hPrev, Qt::KeepAspectRatio));
    }else{
        //borra la imagen que este en la vista previa
        ui->etqVistaprevia->clear();
        ui->etqVistaprevia->setText(txtVistaPrev);
    }
}

void MainWindow::conexionInterrumpida(){

    ui->actionDesconectar_camara->trigger();
    limpiarVista();
    ui->actionActualizar->trigger();
}

void MainWindow::limpiarVista(){

    ui->etqCamara->clear();
    ui->etqCamara->setText(txtCamara);
    ui->etqVistaprevia->clear();
    ui->etqVistaprevia->setText(txtVistaPrev);
}

void MainWindow::procesar_imagen(QPixmap pixmap){

    img = pixmap.toImage();
    ui->etqCamara->setPixmap(pixmap.scaled(w, h, Qt::KeepAspectRatio));
}

void MainWindow::disponibilidadColores(){

    QString nombreImagen, ruta, color;
    QFileInfo archivo;
    ruta = dirRaiz + "/" + *historia + "/" + *icon + "/" + *fechaIcon;

    for(int i = 0; i < colores.size(); ++i){

        color = colores.at(i);
        nombreImagen = (ruta + "/" + *historia + " - " + *icon + " - " + *fechaIcon + " - " + color + ".jpg");
        archivo.setFile(nombreImagen);
        if(archivo.exists())
            btnsColores.at(i)->setEnabled(true);
        else
            btnsColores.at(i)->setEnabled(false);
    }
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

    disconnect(&camsMapper, SIGNAL(mapped(int)), this, SLOT(conectar(int)));

    for(i = 0; i < numCams; ++i){
        camsMapper.removeMappings(accionesDinamicas.at(i));
        disconnect(accionesDinamicas.at(i), SIGNAL(triggered()), &camsMapper, SLOT(map()));
        accionesDinamicas.removeAt(i);
    }

    indexCam = -1;//valor por defecto del indice de la camara
    cv::VideoCapture camaras;
    i = numCams = 0;
    double wRes, hRes;
    bool flag = true;
    ui->menuCamaras->clear();

    while(flag){
        camaras.open(i);
        if(camaras.isOpened()){
            wRes = camaras.get(CV_CAP_PROP_FRAME_WIDTH);
            hRes = camaras.get(CV_CAP_PROP_FRAME_HEIGHT);
            accionesDinamicas.insert(i, ui->menuCamaras->addAction("Camara " + QString::number(i + 1) + " - " + QString::number(wRes) + "x" + QString::number(hRes)));
            connect(accionesDinamicas.at(i), SIGNAL(triggered()), &camsMapper, SLOT(map()));
            camsMapper.setMapping(accionesDinamicas.at(i), i);
            numCams+=1;
            camaras.release();
        }else
            flag = false;
        ++i;
    }
    connect(&camsMapper, SIGNAL(mapped(int)), this, SLOT(conectar(int)));

    ui->cBoxModo->activated(0);
}

void MainWindow::on_cBoxModo_activated(int index){

    if(index == 1){
        //si le hilo no esta corriendo ya, y hay una historia/iconografia/fecha valida cargada, arranca el hilo
        if(conectado && !historia->isEmpty() && !icon->isEmpty() && *fechaIcon == fecha && !hiloCaptura.isRunning()){
            hiloCaptura = QtConcurrent::run(&this->captura, &objCaptura::start, int(indexCam));
        }
    }else{
        if(hiloCaptura.isRunning())
            emit on_stop();
    }
    ui->cBoxModo->setCurrentIndex(index);
    revisionBtns();
}
