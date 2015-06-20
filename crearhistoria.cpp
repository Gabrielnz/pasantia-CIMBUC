#include "crearhistoria.h"
#include "ui_crearhistoria.h"

crearHistoria::crearHistoria(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::crearHistoria)
{
    ui->setupUi(this);
}

crearHistoria::crearHistoria(QString dirRaizExt, QString fechaExt): ui(new Ui::crearHistoria){

    ui->setupUi(this);
    dirRaiz = dirRaizExt;
    fecha = fechaExt;
    histLista = false;
    lesionLista = false;
    ui->btnCrearHistoria->setEnabled(false);
    this->setModal(true);
    this->adjustSize();
    this->setFixedSize(this->size());
}

crearHistoria::~crearHistoria()
{
    delete ui;
}

void crearHistoria::on_btnCancelar_clicked(){ close();}

void crearHistoria::on_lineaCrearHistoria_textChanged(const QString &historia){
    //se asegura de que se haya escrito algun texto para crear la historia
    if(!historia.isEmpty()){
        histLista = true;
    }else{
        histLista = false;
    }

    if(histLista && lesionLista)
        ui->btnCrearHistoria->setEnabled(true);
    else
        ui->btnCrearHistoria->setEnabled(false);
}

void crearHistoria::on_btnCrearHistoria_clicked(){

    histCreada = ui->lineaCrearHistoria->text();
    lesionCreada = ui->lineaNuevaLesion->text();
    QDir dir;
    //crea la estructura de carpetas para la nueva historia y la lesion
    dir.mkpath(dirRaiz + "/" + histCreada + "/" + lesionCreada + "/" + fecha);

    close();
}

QString crearHistoria::getHistoriaCreada(){

    return this->histCreada;
}

QString crearHistoria::getLesionCreada(){

    return this->lesionCreada;
}

void crearHistoria::resetHistoria(){
    ui->lineaCrearHistoria->setText("");
}

void crearHistoria::resetLesion(){
    ui->lineaNuevaLesion->setText("");
}

void crearHistoria::on_lineaNuevaLesion_textChanged(const QString &lesion){

    if(!lesion.isEmpty()){
        lesionLista = true;
    }else{
        lesionLista = false;
    }

    if(histLista && lesionLista)
        ui->btnCrearHistoria->setEnabled(true);
    else
        ui->btnCrearHistoria->setEnabled(false);
}
