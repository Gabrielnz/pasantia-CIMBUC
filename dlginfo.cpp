#include "dlginfo.h"
#include "ui_dlginfo.h"

dlgInfo::dlgInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgInfo)
{
    ui->setupUi(this);
}

dlgInfo::dlgInfo(QString mensaje, QString titulo) : ui(new Ui::dlgInfo){
    ui->setupUi(this);
    ui->etqInfo->setText(mensaje);
    this->setWindowTitle(titulo);
    this->setModal(true);
    this->adjustSize();
    this->setFixedSize(this->size());
}

dlgInfo::~dlgInfo(){

    delete ui;
}

void dlgInfo::on_btnAceptar_clicked(){ close(); }
