#include "crearlesion.h"
#include "ui_crearlesion.h"

crearLesion::crearLesion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::crearLesion)
{
    ui->setupUi(this);
}

crearLesion::crearLesion(QString dirRaizExt, QString historiaExt, QString fechaExt) : ui(new Ui::crearLesion){
    ui->setupUi(this);
    dirRaiz = dirRaizExt;
    historia = historiaExt;
    fecha = fechaExt;
    this->setModal(true);
    ui->btnAceptar->setEnabled(false);
    lesionLista = false;
    this->setWindowTitle("Nueva lesion");
    this->adjustSize();
    this->setFixedSize(this->size());
}

crearLesion::~crearLesion()
{
    delete ui;
}

void crearLesion::on_lineaLesion_textChanged(const QString &lesion)
{
    if(!lesion.isEmpty()){
        lesionLista = true;
        ui->btnAceptar->setEnabled(true);
    }else{
        lesionLista = false;
        ui->btnAceptar->setEnabled(false);
    }
}

void crearLesion::on_btnCancelar_clicked(){ close(); }

void crearLesion::on_btnAceptar_clicked()
{
    lesionCreada = ui->lineaLesion->text();
    QDir dir;
    //crea la estructura de carpetas para la nueva historia y la lesion
    dir.mkpath(dirRaiz + "/" + historia + "/" + lesionCreada + "/" + fecha);

    close();
}

QString crearLesion::getLesion(){
    return lesionCreada;
}
