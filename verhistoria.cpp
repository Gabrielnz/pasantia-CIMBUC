#include "verhistoria.h"
#include "ui_verhistoria.h"

verHistoria::verHistoria(QString ruta, QString historia, QWidget *parent) : QDialog(parent), ui(new Ui::verHistoria){

    ui->setupUi(this);
    QFile jHistoria;
    jHistoria.setFileName(ruta + "/" + historia + "/" + "historia.json");
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
    QDir dir;
    dir.setPath(ruta + "/" + historia);
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
    ui->etqInfoLesiones->setText(QString::number(dir.entryList().count()));
    this->setWindowTitle("Historia");
    this->setModal(true);
    this->adjustSize();
    this->setFixedSize(this->size());
}

verHistoria::~verHistoria(){ delete ui; }

void verHistoria::on_btnAceptar_clicked(){ close(); }
