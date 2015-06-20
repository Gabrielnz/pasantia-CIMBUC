#include "dlgreemplazar.h"
#include "ui_dlgreemplazar.h"

dlgReemplazar::dlgReemplazar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgReemplazar)
{
    ui->setupUi(this);
}

dlgReemplazar::dlgReemplazar(QString color) : ui(new Ui::dlgReemplazar){
    ui->setupUi(this);
    reemplazar = false;
    this->setModal(true);
    ui->etqReemplazar->setText("Desea reemplazar la imagen de color " + color + "?");
}

bool dlgReemplazar::getReemplazar(){
    return reemplazar;
}

dlgReemplazar::~dlgReemplazar()
{
    delete ui;
}

void dlgReemplazar::on_btnReemplazar_clicked()
{
    reemplazar = true;
    this->close();
}

void dlgReemplazar::on_btnCancelar_clicked()
{
    close();
}
