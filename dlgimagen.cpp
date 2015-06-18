#include "dlgimagen.h"
#include "ui_dlgimagen.h"

dlgImagen::dlgImagen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgImagen)
{
    ui->setupUi(this);
}

dlgImagen::dlgImagen(QString nombreImagen) : ui(new Ui::dlgImagen){
    ui->setupUi(this);
    QImage imagen(nombreImagen);

    int w = imagen.width();
    int h = imagen.height();
    ui->etqImagen->setFixedWidth(w);
    ui->etqImagen->setFixedHeight(h);
    ui->etqImagen->setPixmap(QPixmap::fromImage(imagen));
    this->setWindowTitle(nombreImagen);
    this->adjustSize();
    this->setFixedSize(this->size());

    connect(ui->btnAceptar, SIGNAL(clicked(bool)), this, SLOT(close()));
}

dlgImagen::~dlgImagen()
{
    delete ui;
}
