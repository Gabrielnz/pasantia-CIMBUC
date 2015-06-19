#include "dlgimagen.h"
#include "ui_dlgimagen.h"

dlgImagen::dlgImagen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgImagen)
{
    ui->setupUi(this);
}

dlgImagen::dlgImagen(QString nombreImagen, QString colorExt, QString rutaExt) : ui(new Ui::dlgImagen){
    ui->setupUi(this);
    QImage imagen(nombreImagen);
    color = colorExt;
    ruta = rutaExt;
    int w = imagen.width();
    int h = imagen.height();
    ui->etqImagen->setFixedWidth(w);
    ui->etqImagen->setFixedHeight(h);
    ui->etqImagen->setPixmap(QPixmap::fromImage(imagen));

    anotacion.setFileName(ruta + "/" + color + ".txt");
    anotacion.open(QIODevice::ReadOnly | QIODevice::Text);
    QString aux;
    aux = aux + anotacion.readLine();
    while(anotacion.canReadLine()){
        aux = aux + anotacion.readLine();
    }

    ui->textoAnotacion->setPlainText(aux);
    anotacion.close();
    this->setWindowTitle(nombreImagen);
    this->adjustSize();
    this->setFixedSize(this->size());
}

dlgImagen::~dlgImagen(){

    if(anotacion.isOpen())
        anotacion.close();

    delete ui;
}

void dlgImagen::on_btnAceptar_clicked(){

    anotacion.open(QIODevice::WriteOnly | QIODevice::Text);

    /* Point a QTextStream object at the file */
    QTextStream stream(&anotacion);

    QString aux = ui->textoAnotacion->toPlainText();
    stream << aux;

    /* Close the file */
    anotacion.close();

    close();
}
