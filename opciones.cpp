#include "opciones.h"
#include "ui_opciones.h"

Opciones::Opciones(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Opciones)
{
    ui->setupUi(this);
    this->adjustSize();
    this->setFixedSize(this->size());
}

Opciones::~Opciones(){

    delete ui;
}
