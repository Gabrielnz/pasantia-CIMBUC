#include "abriricon.h"
#include "ui_abriricon.h"

abrirIcon::abrirIcon(QString *iconExt, QString rutaExt, QString *fechaIconExt, QWidget *parent) : QDialog(parent), ui(new Ui::abrirIcon){

    ui->setupUi(this);
    ui->btnAbrir->setEnabled(false);
    icon = iconExt;
    ruta = rutaExt;
    fechaIcon = fechaIconExt;
    fechaSeleccionada = QDate::currentDate().toString("dd.MM.yyyy");
    modeloIcon = new QFileSystemModel();
    modeloFecha = new QFileSystemModel();
    modeloIcon->setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
    modeloFecha->setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
    modeloIcon->setRootPath(ruta);
    modeloIcon->setReadOnly(true);
    modeloFecha->setReadOnly(true);
    ui->iconList->setModel(modeloIcon);
    QModelIndex index = modeloIcon->index(ruta);
    ui->iconList->scrollTo(index);
    ui->iconList->activated(index);
    ui->iconList->setRootIndex(index);
    this->adjustSize();
    this->setModal(true);
}

abrirIcon::~abrirIcon(){ delete ui; }

void abrirIcon::on_btnCancelar_clicked(){ close(); }

void abrirIcon::on_btnAbrir_clicked(){

    QString iconSeleccionada = modeloIcon->fileName(ui->iconList->currentIndex());
    *icon = iconSeleccionada;
    *fechaIcon = fechaSeleccionada;

    close();
}

void abrirIcon::on_iconList_clicked(const QModelIndex &indexIn){
    //si selecciona solamente la icon, la fecha pasa a ser la del dia actual
    fechaSeleccionada = QDate::currentDate().toString("dd.MM.yyyy");

    if(indexIn.isValid()){
        modeloFecha->setRootPath(modeloIcon->filePath(indexIn));
        ui->fechaIconList->setModel(modeloFecha);
        QModelIndex index = modeloFecha->index(modeloIcon->filePath(indexIn));
        ui->fechaIconList->scrollTo(index);
        ui->fechaIconList->activated(index);
        ui->fechaIconList->setRootIndex(index);
        ui->etqInfoIcon->setText(modeloIcon->fileName(indexIn));
        ui->etqInfoFecha->setText(QDate::currentDate().toString("dd/MM/yyyy"));
        ui->btnAbrir->setEnabled(true);
    }else{
        ui->btnAbrir->setEnabled(false);
    }
}

void abrirIcon::on_fechaIconList_clicked(const QModelIndex &indexIn){

    if(indexIn.isValid()){
        fechaSeleccionada = modeloFecha->fileName(indexIn);
        QDate fecha = QDate::fromString(fechaSeleccionada, "dd.MM.yyyy");
        ui->etqInfoFecha->setText(fecha.toString("dd/MM/yyyy"));
    }
}
