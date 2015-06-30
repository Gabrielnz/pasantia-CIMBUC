#include "abrirhistoria.h"
#include "ui_abrirhistoria.h"

abrirHistoria::abrirHistoria(QString *historiaExt, QString *lesionExt, QString rutaExt, QWidget *parent) : QDialog(parent), ui(new Ui::abrirHistoria){

    ui->setupUi(this);
    ui->btnAbrir->setEnabled(false);
    historia = historiaExt;
    lesion = lesionExt;
    ruta = rutaExt;
    QValidator *soloNumeros = new QIntValidator(1, 999999999, this);
    ui->lineaBuscar->setValidator(soloNumeros);
    modeloDir = new QFileSystemModel();
    modeloDir->setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
    modeloDir->setRootPath(ruta);
    modeloDir->setReadOnly(true);
    ui->listView->setModel(modeloDir);
    QModelIndex index = modeloDir->index(ruta);
    ui->listView->scrollTo(index);
    ui->listView->setCurrentIndex(index);
    ui->listView->setRootIndex(index);
    this->setWindowTitle("Abrir historia");
    this->setModal(true);
    this->adjustSize();
    this->setFixedSize(this->size());
}

abrirHistoria::~abrirHistoria(){ delete ui; }

void abrirHistoria::on_btnCancelar_clicked(){ close(); }

void abrirHistoria::on_btnAbrir_clicked(){

    QString histSeleccionada = modeloDir->fileName(ui->listView->currentIndex());
    *historia = histSeleccionada;
    *lesion = "";

    close();
}

void abrirHistoria::on_listView_clicked(const QModelIndex &index){

    if(index.isValid()){

        jHistoria.setFileName(ruta + "/" + modeloDir->fileName(ui->listView->currentIndex()) + "/" + "historia.json");
        jHistoria.open(QIODevice::ReadOnly);
        QByteArray jData = jHistoria.readAll();
        QJsonDocument jDoc(QJsonDocument::fromJson(jData));
        QJsonObject jObj = jDoc.object();
        ui->etqInfoCI->setText(jObj["CI"].toString());
        ui->etqInfoNombre->setText(jObj["Nombre"].toString());
        ui->etqInfoApellido->setText(jObj["Apellido"].toString());
        ui->etqInfoSexo->setText(jObj["Sexo"].toString());
        ui->etqInfoFechaNac->setText(jObj["Fecha de nacimiento"].toString());
        jHistoria.close();

        ui->btnAbrir->setEnabled(true);
        ui->etqHistSeleccionada->setText(modeloDir->fileName(ui->listView->currentIndex()));
    }
}

void abrirHistoria::on_cBoxBuscar_currentIndexChanged(int index){

    buscar(index, ui->lineaBuscar->text());
}

void abrirHistoria::on_lineaBuscar_textChanged(const QString &CI){

    buscar(ui->cBoxBuscar->currentIndex(), CI);
}

void abrirHistoria::buscar(int index, const QString &CI){

    modeloDir->setRootPath("");
    modeloDir->setRootPath(ruta);
    QDir dir;
    dir.setPath(ruta);
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
    QStringList lista = dir.entryList();
    int i;
    int n = dir.count();
    QStringList coincidencias, quitar;

    switch (index) {

    case 1:
        for(i = 0; i < n; i++){
            if(lista[i].contains("V - " + CI)){
                coincidencias+= lista[i];
                //qDebug() << lista[i];
            }else
                quitar+= lista[i];
        }
        break;

    case 2:
        for(i = 0; i < n; i++){
            if(lista[i].contains("E - " + CI)){
                coincidencias+= lista[i];
                //qDebug() << lista[i];
            }else
                quitar+= lista[i];
        }
        break;

    default:
        for(i = 0; i < n; i++){
            if(lista[i].contains("V - " + CI) || lista[i].contains("E - " + CI)){
                coincidencias+= lista[i];
                //qDebug() << lista[i];
            }else
                quitar+= lista[i];
        }
        break;
    }
    //actualiza el modelo de vista para que solo muestre las carpetas filtradas
    n = quitar.count();
    modeloDir->removeRow(2, modeloDir->index(ruta));
    for(i = 0; i < n; i++){
        QStringList::const_iterator iter = qFind(lista.begin(), lista.end(), quitar[i]);
        //si el iterador no esta al final de la lista es porque encontro el valor
        if(iter != lista.end()){
            qDebug() << *iter;
        }
    }
}
