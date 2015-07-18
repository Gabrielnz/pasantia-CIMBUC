#include "regicon.h"
#include "ui_regicon.h"

regIcon::regIcon(QString dirRaizExt, QString historiaExt, QString *iconExt, QWidget *parent) : QDialog(parent), ui(new Ui::regIcon){

    ui->setupUi(this);
    dirRaiz = dirRaizExt;
    historia = historiaExt;
    icon = iconExt;
    QRegExp rx("^([a-zA-Z0-9]+\[ ])+$");
    QValidator *val = new QRegExpValidator(rx, this);
    ui->lineaIcon->setValidator(val);
    ui->btnReg->setEnabled(false);
    iconLista = false;
    this->setModal(true);
    this->adjustSize();
    this->setFixedSize(this->size());
}

regIcon::~regIcon(){ delete ui; }

void regIcon::on_lineaIcon_textChanged(const QString &regIcon){

    ui->lineaIcon->setText(regIcon.toUpper());

    if(!regIcon.isEmpty()){
        iconLista = true;
        ui->btnReg->setEnabled(true);
    }else{
        iconLista = false;
        ui->btnReg->setEnabled(false);
    }
}

void regIcon::on_btnCancelar_clicked(){ close(); }

void regIcon::on_btnReg_clicked(){
    QDir dir(dirRaiz + "/" + historia + "/" + ui->lineaIcon->text());

    if(!dir.exists()){

        *icon = ui->lineaIcon->text();
        //crea la estructura de carpetas para la nueva historia y la iconografia
        dir.mkpath(dirRaiz + "/" + historia + "/" + *icon);
        close();
    }else{
        QMessageBox::warning(this, "Error al registrar iconografía", "La iconografía " + ui->lineaIcon->text() + " ya existe, introduzca una nueva.");
        ui->lineaIcon->setText("");
    }
}
