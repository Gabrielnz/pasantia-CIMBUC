#include "crearlesion.h"
#include "ui_crearlesion.h"

crearLesion::crearLesion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::crearLesion)
{
    ui->setupUi(this);
}

crearLesion::crearLesion(QString dirRaizExt, QString historiaExt, QString *lesionExt) : ui(new Ui::crearLesion){
    ui->setupUi(this);
    dirRaiz = dirRaizExt;
    historia = historiaExt;
    lesion = lesionExt;
    this->setModal(true);
    ui->btnAceptar->setEnabled(false);
    lesionLista = false;
    this->setWindowTitle("Nueva lesion");
    this->adjustSize();
    this->setFixedSize(this->size());
}

crearLesion::~crearLesion(){

    delete ui;
}

void crearLesion::on_lineaLesion_textChanged(const QString &nuevaLesion){

    if(!nuevaLesion.isEmpty()){
        lesionLista = true;
        ui->btnAceptar->setEnabled(true);
    }else{
        lesionLista = false;
        ui->btnAceptar->setEnabled(false);
    }
}

void crearLesion::on_btnCancelar_clicked(){ close(); }

void crearLesion::on_btnAceptar_clicked(){

    *lesion = ui->lineaLesion->text();
    QDir dir;
    //crea la estructura de carpetas para la nueva historia y la lesion
    dir.mkpath(dirRaiz + "/" + historia + "/" + *lesion);

    close();
}
