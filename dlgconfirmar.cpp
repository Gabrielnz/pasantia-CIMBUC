#include "dlgconfirmar.h"
#include "ui_dlgconfirmar.h"

dlgConfirmar::dlgConfirmar(QString mensaje, QString titulo, QWidget *parent) : QDialog(parent), ui(new Ui::dlgConfirmar){

    ui->setupUi(this);
    confirmar = false;
    ui->etqConfirmacion->setText(mensaje);
    this->setWindowTitle(titulo);
    this->setModal(true);
    this->adjustSize();
    this->setFixedSize(this->size());
}

bool dlgConfirmar::confirmacion(){ return confirmar; }

dlgConfirmar::~dlgConfirmar(){ delete ui; }

void dlgConfirmar::on_btnAceptar_clicked(){

    confirmar = true;
    close();
}

void dlgConfirmar::on_btnCancelar_clicked(){ close(); }
