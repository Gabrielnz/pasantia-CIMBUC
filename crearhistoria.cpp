#include "crearhistoria.h"
#include "ui_crearhistoria.h"

crearHistoria::crearHistoria(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::crearHistoria)
{
    ui->setupUi(this);
    ui->btnCrearHistoria->setEnabled(false);
}

crearHistoria::~crearHistoria()
{
    delete ui;
}

void crearHistoria::on_btnCancelar_clicked()
{
    close();
}

void crearHistoria::on_lineaCrearHistoria_textChanged(const QString &historia){
    //se asegura de que se haya escrito algun texto para crear la historia
    if(!historia.isEmpty()){
        ui->btnCrearHistoria->setEnabled(true);
    }else{
        ui->btnCrearHistoria->setEnabled(false);
    }
}

void crearHistoria::on_btnCrearHistoria_clicked(){

    histCreada = ui->lineaCrearHistoria->text();

    close();
}

QString crearHistoria::getHistoriaCreada(){

    return this->histCreada;
}
