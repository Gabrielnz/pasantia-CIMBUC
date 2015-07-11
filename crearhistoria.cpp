#include "crearhistoria.h"
#include "ui_crearhistoria.h"

crearHistoria::crearHistoria(QString dirRaizExt, QString *historiaExt, QWidget *parent): QDialog(parent), ui(new Ui::crearHistoria){

    ui->setupUi(this);
    historia = historiaExt;
    dirRaiz = dirRaizExt;
    QDate fechaMinima, fechaDefecto;
    fechaMinima = fechaDefecto = QDate::currentDate();
    fechaMinima.setDate(fechaMinima.year() - 120,fechaMinima.month(), fechaMinima.day() );
    fechaDefecto.setDate(fechaDefecto.year() - 18, fechaMinima.month(), fechaMinima.day());
    ui->editFechaNac->setDate(fechaDefecto);
    ui->editFechaNac->setDateRange(fechaMinima, QDate::currentDate());
    ui->btnCrearHistoria->setEnabled(false);
    QValidator *soloNumeros = new QIntValidator(1, 999999999, this);
    ui->lineaCI->setValidator(soloNumeros);
    QRegExp rx("^([a-zA-Z]+\[ ])+$");
    QValidator *soloPalabras = new QRegExpValidator(rx, this);
    ui->lineaNombre->setValidator(soloPalabras);
    ui->lineaApellido->setValidator(soloPalabras);
    nombre = "";
    apellido = "";
    this->setModal(true);
    this->adjustSize();
    this->setFixedSize(this->size());
}

QString crearHistoria::getNombre(){

    return nombre;
}

QString crearHistoria::getApellido(){

    return apellido;
}

crearHistoria::~crearHistoria(){

    if(jHistoria.isOpen())
        jHistoria.close();

    delete ui;
}

void crearHistoria::on_btnCancelar_clicked(){ close();}

void crearHistoria::on_lineaCI_textChanged(const QString &CI){
    //se asegura de que todos los campos esten llenos
    if(!CI.isEmpty() && !ui->lineaNombre->text().isEmpty() && !ui->lineaApellido->text().isEmpty() && (ui->radioMasculino->isChecked() || ui->radioFemenino->isChecked())){
        ui->btnCrearHistoria->setEnabled(true);
    }else{
        ui->btnCrearHistoria->setEnabled(false);
    }
}

void crearHistoria::on_btnCrearHistoria_clicked(){

    QDir dir;
    dir.setPath(dirRaiz + "/" + ui->cBoxCI->currentText() + " - " +  ui->lineaCI->text());

    if(!dir.exists()){
        *historia = ui->cBoxCI->currentText() + " - " +  ui->lineaCI->text();
        //crea la estructura de carpetas para la nueva historia y la icon
        dir.mkpath(dirRaiz + "/" + *historia);

        jHistoria.setFileName(dirRaiz + "/" + *historia + "/" + "historia.json");
        jHistoria.open(QIODevice::ReadWrite);
        QJsonDocument jDoc;
        QJsonObject jObj;
        QJsonValue jCI(*historia);
        QJsonValue jNombre(ui->lineaNombre->text());
        QJsonValue jApellido(ui->lineaApellido->text());
        QJsonValue jSexo;

        if(ui->radioMasculino->isChecked())
            jSexo = ui->radioMasculino->text();
        else
            jSexo = ui->radioFemenino->text();

        QJsonValue jFechaNac(ui->editFechaNac->date().toString("dd/MM/yyyy"));
        jObj.insert("CI", jCI);
        jObj.insert("Nombre", jNombre);
        jObj.insert("Apellido", jApellido);
        jObj.insert("Sexo", jSexo);
        jObj.insert("Fecha de nacimiento", jFechaNac);
        jDoc.setObject(jObj);
        jHistoria.write(jDoc.toJson());
        jHistoria.close();

        nombre = ui->lineaNombre->text();
        apellido = ui->lineaApellido->text();

        close();
    }else{
        dlgInfo info("La cédula " + ui->cBoxCI->currentText() + " - " +  ui->lineaCI->text() + " ya existe, porfavor introduzca una nueva.", "Error al crear historia");
        ui->lineaCI->setText("");
        info.exec();
    }
}

void crearHistoria::on_lineaNombre_textChanged(const QString &nombre){
    //se asegura de que todos los campos esten llenos
    ui->lineaNombre->setText(nombre.toUpper());

    if(!ui->lineaCI->text().isEmpty() && !nombre.isEmpty() && !ui->lineaApellido->text().isEmpty() && (ui->radioMasculino->isChecked() || ui->radioFemenino->isChecked())){
        ui->btnCrearHistoria->setEnabled(true);
    }else{
        ui->btnCrearHistoria->setEnabled(false);
    }
}

void crearHistoria::on_lineaApellido_textChanged(const QString &apellido){
    //se asegura de que todos los campos esten llenos
    ui->lineaApellido->setText(apellido.toUpper());

    if(!ui->lineaCI->text().isEmpty() && !ui->lineaNombre->text().isEmpty() && !apellido.isEmpty() && (ui->radioMasculino->isChecked() || ui->radioFemenino->isChecked())){
        ui->btnCrearHistoria->setEnabled(true);
    }else{
        ui->btnCrearHistoria->setEnabled(false);
    }
}

void crearHistoria::on_radioMasculino_clicked(){
    //se asegura de que todos los campos esten llenos
    if(!ui->lineaCI->text().isEmpty() && !ui->lineaNombre->text().isEmpty() && !ui->lineaApellido->text().isEmpty()){
        ui->btnCrearHistoria->setEnabled(true);
    }else{
        ui->btnCrearHistoria->setEnabled(false);
    }
}

void crearHistoria::on_radioFemenino_clicked(){
    //se asegura de que todos los campos esten llenos
    if(!ui->lineaCI->text().isEmpty() && !ui->lineaNombre->text().isEmpty() && !ui->lineaApellido->text().isEmpty()){
        ui->btnCrearHistoria->setEnabled(true);
    }else{
        ui->btnCrearHistoria->setEnabled(false);
    }
}
