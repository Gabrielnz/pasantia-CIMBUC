#include "acercade.h"
#include "ui_acercade.h"

AcercaDe::AcercaDe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AcercaDe)
{
    ui->setupUi(this);
    this->adjustSize();
    this->setFixedSize(this->size());
}

AcercaDe::~AcercaDe()
{
    delete ui;
}
