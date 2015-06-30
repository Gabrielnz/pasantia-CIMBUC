#include "eliminarhistoria.h"
#include "ui_eliminarhistoria.h"

eliminarHistoria::eliminarHistoria(QString rutaExt, QString *historiaExt, QString *lesionExt, QWidget *parent) : QDialog(parent), ui(new Ui::eliminarHistoria){

    ui->setupUi(this);
    ruta = rutaExt;
    historia = historiaExt;
    lesion = lesionExt;
    this->setWindowTitle("Eliminar historia");

    jHistoria.setFileName(ruta + "/" + *historia + "/" + "historia.json");
    jHistoria.open(QIODevice::ReadOnly);
    QByteArray jData = jHistoria.readAll();
    QJsonDocument jDoc(QJsonDocument::fromJson(jData));
    QJsonObject jObj = jDoc.object();
    ui->etqInfoCI->setText(jObj["CI"].toString());
    ui->etqInfoNombre->setText(jObj["Nombre"].toString());
    ui->etqInfoApellido->setText(jObj["Apellido"].toString());
    ui->etqInfoSexo->setText(jObj["Sexo"].toString());
    ui->etqInfoFechaNac->setText(jObj["Fecha de nacimiento"].toString());
    jHistoria.close();

    this->setModal(true);
    this->adjustSize();
    this->setFixedSize(this->size());
}

eliminarHistoria::~eliminarHistoria(){ delete ui; }

void eliminarHistoria::on_btnCancelar_clicked(){ close(); }

void eliminarHistoria::on_btnEliminar_clicked(){

    QDir dir;
    dir.setPath(ruta + "/" + *historia);
    dir.removeRecursively();
    *historia = "";
    *lesion = "";
    dlgInfo info("La historia se ha eliminado correctamente.", "Fecha eliminada");
    info.exec();

    close();
}
