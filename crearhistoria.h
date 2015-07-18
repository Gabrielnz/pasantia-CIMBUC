#ifndef CREARHISTORIA_H
#define CREARHISTORIA_H

#include <QDialog>
#include <QDir>
#include <QDebug>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QByteArray>
#include <QMessageBox>

namespace Ui {
class crearHistoria;
}

class crearHistoria : public QDialog
{
    Q_OBJECT

public:
    explicit crearHistoria(QString dirRaizExt, QString *historiaExt, QWidget *parent = 0);
    QString getNombre();
    QString getApellido();
    ~crearHistoria();

private slots:
    void on_btnCancelar_clicked();

    void on_lineaCI_textChanged(const QString &CI);

    void on_btnCrearHistoria_clicked();

    void on_lineaNombre_textChanged(const QString &nombre);

    void on_lineaApellido_textChanged(const QString &apellido);

    void on_radioMasculino_clicked();

    void on_radioFemenino_clicked();

private:
    Ui::crearHistoria *ui;
    QString dirRaiz, *historia, nombre, apellido;
    QFile jHistoria;
};

#endif // CREARHISTORIA_H
