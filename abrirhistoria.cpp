#include "abrirhistoria.h"
#include "ui_abrirhistoria.h"

abrirHistoria::abrirHistoria(QString *historiaExt, QString *iconExt, QString rutaExt, QWidget *parent) : QDialog(parent), ui(new Ui::abrirHistoria){

    ui->setupUi(this);
    ui->btnAbrir->setEnabled(false);
    historia = historiaExt;
    icon = iconExt;
    ruta = rutaExt;
    QValidator *soloNumeros = new QIntValidator(1, 999999999, this);
    ui->lineaBuscar->setValidator(soloNumeros);
    modelo = new QStringListModel();
    dir.setPath(ruta);
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
    modelo->setStringList(dir.entryList());
    ui->listView->setModel(modelo);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setWindowTitle("Abrir historia");
    this->setModal(true);
    this->adjustSize();
    this->setFixedSize(this->size());
}

abrirHistoria::~abrirHistoria(){ delete ui; }

void abrirHistoria::on_btnCancelar_clicked(){ close(); }

void abrirHistoria::on_btnAbrir_clicked(){

    QString histSeleccionada = (modelo->data(ui->listView->currentIndex(), Qt::DisplayRole)).toString();
    *historia = histSeleccionada;
    *icon = "";

    close();
}

void abrirHistoria::on_listView_clicked(const QModelIndex &index){

    if(index.isValid()){

        jHistoria.setFileName(ruta + "/" + (modelo->data(ui->listView->currentIndex(), Qt::DisplayRole)).toString() + "/" + "historia.json");
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
        ui->etqHistSeleccionada->setText((modelo->data(ui->listView->currentIndex(), Qt::DisplayRole)).toString());
    }
}

void abrirHistoria::on_cBoxBuscar_currentIndexChanged(int index){

    buscar(index, ui->lineaBuscar->text());
}

void abrirHistoria::on_lineaBuscar_textChanged(const QString &CI){

    buscar(ui->cBoxBuscar->currentIndex(), CI);
}

void abrirHistoria::buscar(int index, const QString &CI){

    modelo->setStringList(dir.entryList());
    QFileInfoList infoLista = dir.entryInfoList();
    QFileInfoList infoQuitar;
    int i;
    int n = dir.count();

    switch (index) {

    case 1:
        for(i = 0; i < n; i++){
            if(!(infoLista.at(i).baseName()).contains("V - " + CI)){
                infoQuitar += infoLista.at(i);
            }
        }
        break;

    case 2:
        for(i = 0; i < n; i++){
            if(!(infoLista.at(i).baseName()).contains("E - " + CI)){
                infoQuitar += infoLista.at(i);
            }
        }
        break;

    default:
        for(i = 0; i < n; i++){
            if(!(infoLista.at(i).baseName()).contains("V - " + CI) && !(infoLista.at(i).baseName()).contains("E - " + CI)){
                infoQuitar += infoLista.at(i);
            }
        }
        break;
    }
    //actualiza el modelo de vista para que solo muestre las carpetas filtradas
    QStringList aux;
    QStringList::const_iterator iter;

    while(!infoQuitar.empty()){
        aux = modelo->stringList();
        iter = qFind(aux.begin(), aux.end(), (infoQuitar.front()).baseName());
        modelo->removeRow(iter - aux.begin());
        infoQuitar.pop_front();
    }
}
