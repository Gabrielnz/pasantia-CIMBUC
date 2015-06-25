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

crearLesion::~crearLesion(){ delete ui; }

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
    QDir dir(dirRaiz + "/" + historia + "/" + ui->lineaLesion->text());

    if(!dir.exists()){

        *lesion = ui->lineaLesion->text();
        //crea la estructura de carpetas para la nueva historia y la lesion
        dir.mkpath(dirRaiz + "/" + historia + "/" + *lesion);
        dlgInfo info("La lesion ha sido creada correctamente.", "Lesion creada");
        info.exec();

        close();
    }else{
        dlgInfo info("La lesion con el nombre: " + ui->lineaLesion->text() + " ya existe, no se puede volver a crear.", "Error al crear lesion");
        ui->lineaLesion->setText("");
        info.exec();
    }
}
