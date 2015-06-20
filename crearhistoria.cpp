#include "crearhistoria.h"
#include "ui_crearhistoria.h"

crearHistoria::crearHistoria(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::crearHistoria)
{
    ui->setupUi(this);
}

crearHistoria::crearHistoria(QString dirRaizExt, QString *historiaExt): ui(new Ui::crearHistoria){

    ui->setupUi(this);
    historia = historiaExt;
    dirRaiz = dirRaizExt;
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

void crearHistoria::on_lineaCrearHistoria_textChanged(const QString &nuevaHistoria){
    //se asegura de que se haya escrito algun texto para crear la historia
    if(!nuevaHistoria.isEmpty()){
        ui->btnCrearHistoria->setEnabled(true);
    }else{
        ui->btnCrearHistoria->setEnabled(false);
    }
}

void crearHistoria::on_btnCrearHistoria_clicked(){

    *historia = ui->lineaCrearHistoria->text();
    QDir dir;
    //crea la estructura de carpetas para la nueva historia y la lesion
    dir.mkpath(dirRaiz + "/" + *historia);

    close();
}
