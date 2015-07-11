#include "acercade.h"
#include "ui_acercade.h"

AcercaDe::AcercaDe(QWidget *parent) : QDialog(parent), ui(new Ui::AcercaDe){

    ui->setupUi(this);
    this->setModal(true);

    QPixmap logoPix(":/img/cimbuc.jpg");
    QPixmap iconoPix(":/img/Eye_64.png");

    ui->etqCIMBUC->setPixmap(logoPix.scaled(1000, 200, Qt::KeepAspectRatio));
    ui->etqIcono->setPixmap(iconoPix);

    this->adjustSize();
    this->setFixedSize(this->size());
}

AcercaDe::~AcercaDe(){ delete ui; }
