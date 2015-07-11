#include "regabriricon.h"
#include "ui_regabriricon.h"

regAbrirIcon::regAbrirIcon(bool nueva, bool abrir, QWidget *parent) : QDialog(parent), ui(new Ui::regAbrirIcon){

    ui->setupUi(this);
    ui->btnReg->setEnabled(nueva);
    ui->btnAbrir->setEnabled(abrir);

    seleccionoAlgo = false;

    this->setModal(true);
    this->adjustSize();
    this->setFixedSize(this->size());
}

regAbrirIcon::~regAbrirIcon()
{
    delete ui;
}

void regAbrirIcon::on_btnReg_clicked(){

    nueva = true; abrir = false; seleccionoAlgo = true;
    close();
}

void regAbrirIcon::on_btnAbrir_clicked(){

    nueva = false; abrir = true; seleccionoAlgo = true;
    close();
}

bool regAbrirIcon::opcionNueva(){
    return nueva;
}

bool regAbrirIcon::opcionAbrir(){
    return abrir;
}

bool regAbrirIcon::selecciono(){
    return seleccionoAlgo;
}
