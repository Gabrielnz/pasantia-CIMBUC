#include "dlgimagen.h"
#include "ui_dlgimagen.h"

dlgImagen::dlgImagen(QString nombreImagen, QString colorExt, QString rutaExt, QString fechaExt, QWidget *parent) : QDialog(parent), ui(new Ui::dlgImagen){
    ui->setupUi(this);
    QImage imagen(nombreImagen);
    color = colorExt;
    ruta = rutaExt;
    fecha = fechaExt;
    int w = imagen.width();
    int h = imagen.height();
    ui->etqImagen->setFixedWidth(w);
    ui->etqImagen->setFixedHeight(h);
    ui->etqImagen->setPixmap(QPixmap::fromImage(imagen));
    jAnotaciones.setFileName(ruta + "/" + fecha + "/" + "anotaciones.json");
    jAnotaciones.open(QIODevice::ReadWrite);
    QByteArray jData = jAnotaciones.readAll();
    QJsonDocument jDoc(QJsonDocument::fromJson(jData));
    QJsonObject jObj = jDoc.object();
    QJsonValue jVal;

    if(jObj.contains(color)){
        jVal = jObj.value(color);
        ui->textoAnotacion->setPlainText(jVal.toString());
    }

    jAnotaciones.close();
    this->setWindowTitle(nombreImagen);
    this->setModal(true);
    this->adjustSize();
    this->setFixedSize(this->size());
}

dlgImagen::~dlgImagen(){

    if(jAnotaciones.isOpen())
        jAnotaciones.close();

    delete ui;
}

void dlgImagen::on_btnAceptar_clicked(){

    jAnotaciones.open(QIODevice::ReadWrite);
    QByteArray jData = jAnotaciones.readAll();
    QJsonDocument jDoc(QJsonDocument::fromJson(jData));
    QJsonObject jObj = jDoc.object();
    QJsonValue jVal(ui->textoAnotacion->toPlainText());

    if(jObj.contains(color)){
        jObj.remove(color);
    }

    jObj.insert(color, jVal);
    jDoc.setObject(jObj);
    jAnotaciones.reset();
    jAnotaciones.write(jDoc.toJson());
    jAnotaciones.close();

    close();
}
