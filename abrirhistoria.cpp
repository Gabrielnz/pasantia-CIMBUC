#include "abrirhistoria.h"
#include "ui_abrirhistoria.h"

abrirHistoria::abrirHistoria(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::abrirHistoria)
{
    ui->setupUi(this);
}

abrirHistoria::abrirHistoria(QString *historiaExt, QString *lesionExt, QString rutaExt) : ui(new Ui::abrirHistoria){
    ui->setupUi(this);
    ui->btnAbrir->setEnabled(false);
    historia = historiaExt;
    lesion = lesionExt;
    ruta = rutaExt;
    modeloDir = new QFileSystemModel();
    modeloDir->setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
    modeloDir->setRootPath(ruta);
    modeloDir->setReadOnly(true);
    ui->listView->setModel(modeloDir);
    QModelIndex index = modeloDir->index(ruta);
    ui->listView->scrollTo(index);
    ui->listView->setCurrentIndex(index);
    ui->listView->setRootIndex(index);
    //permite que solo se seleccionen las carpetas del primer nivel
    //ui->treeView->setExpandsOnDoubleClick(false);
    //ui->treeView->setRootIsDecorated(false);
    this->setWindowTitle("Abrir historia");
    this->adjustSize();
    this->setModal(true);
}

abrirHistoria::~abrirHistoria(){

    delete ui;
}

void abrirHistoria::on_btnCancelar_clicked(){ close(); }

void abrirHistoria::on_btnAbrir_clicked(){

    QString histSeleccionada = modeloDir->fileName(ui->listView->currentIndex());

    *historia = histSeleccionada;
    *lesion = "";

    close();
}

void abrirHistoria::on_listView_clicked(const QModelIndex &index){

    if(index.isValid())
        ui->btnAbrir->setEnabled(true);
    else
        ui->btnAbrir->setEnabled(false);
}
