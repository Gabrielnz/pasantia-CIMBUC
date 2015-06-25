#include "abrirlesion.h"
#include "ui_abrirlesion.h"

abrirLesion::abrirLesion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::abrirLesion)
{
    ui->setupUi(this);
}

abrirLesion::abrirLesion(QString *lesionExt, QString rutaExt, QString *fechaLesionExt) : ui(new Ui::abrirLesion){
    ui->setupUi(this);
    ui->btnAbrir->setEnabled(false);
    lesion = lesionExt;
    ruta = rutaExt;
    fechaLesion = fechaLesionExt;
    fechaSeleccionada = *fechaLesion;
    modeloLesion = new QFileSystemModel();
    modeloFecha = new QFileSystemModel();
    modeloLesion->setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
    modeloFecha->setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
    modeloLesion->setRootPath(ruta);
    modeloLesion->setReadOnly(true);
    modeloFecha->setReadOnly(true);
    ui->lesionList->setModel(modeloLesion);
    QModelIndex index = modeloLesion->index(ruta);
    ui->lesionList->scrollTo(index);
    ui->lesionList->setCurrentIndex(index);
    ui->lesionList->setRootIndex(index);
    this->setWindowTitle("Abrir lesion");
    this->adjustSize();
    this->setModal(true);
}

abrirLesion::~abrirLesion(){

    delete ui;
}

void abrirLesion::on_btnCancelar_clicked(){ close(); }

void abrirLesion::on_btnAbrir_clicked(){

    QString lesionSeleccionada = modeloLesion->fileName(ui->lesionList->currentIndex());
    *lesion = lesionSeleccionada;
    *fechaLesion = fechaSeleccionada;

    close();
}

void abrirLesion::on_lesionList_clicked(const QModelIndex &indexIn){
    //si selecciona solamente la lesion, la fecha pasa a ser la del dia actual
    fechaSeleccionada = QDate::currentDate().toString("dd.MM.yyyy");

    if(indexIn.isValid()){
        modeloFecha->setRootPath(modeloLesion->filePath(indexIn));
        ui->fechaLesionList->setModel(modeloFecha);
        QModelIndex index = modeloFecha->index(modeloLesion->filePath(indexIn));
        ui->fechaLesionList->scrollTo(index);
        ui->fechaLesionList->setCurrentIndex(index);
        ui->fechaLesionList->setRootIndex(index);
        ui->etqInfoLesion->setText(modeloLesion->fileName(indexIn));
        ui->etqInfoFecha->setText(QDate::currentDate().toString("dd/MM/yyyy"));
        ui->btnAbrir->setEnabled(true);
    }else{
        ui->btnAbrir->setEnabled(false);
    }
}

void abrirLesion::on_fechaLesionList_clicked(const QModelIndex &indexIn){

    if(indexIn.isValid()){
        fechaSeleccionada = modeloFecha->fileName(indexIn);
        QDate fecha = QDate::fromString(fechaSeleccionada, "dd.MM.yyyy");
        ui->etqInfoFecha->setText(fecha.toString("dd/MM/yyyy"));
    }
}
