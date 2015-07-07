#ifndef ABRIRHISTORIA_H
#define ABRIRHISTORIA_H

#include <QDialog>
#include <QFile>
#include <QStringListModel>
#include <QDirModel>
#include <QDebug>
#include <QDate>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QByteArray>

namespace Ui {
class abrirHistoria;
}

class abrirHistoria : public QDialog
{
    Q_OBJECT

public:
    explicit abrirHistoria(QString *historiaExt, QString *iconExt, QString rutaExt, QWidget *parent = 0);
    QString getNombre();
    QString getApellido();
    ~abrirHistoria();

private slots:
    void on_btnCancelar_clicked();

    void on_btnAbrir_clicked();

    void on_listView_clicked(const QModelIndex &index);

    void on_cBoxBuscar_currentIndexChanged(int index);

    void on_lineaBuscar_textChanged(const QString &CI);

    void buscar(int index, const QString &CI);

private:
    Ui::abrirHistoria *ui;
    QString ruta, *historia, *icon, nombre, apellido;
    QDir dir;
    QStringListModel *modelo;
    QFile jHistoria;
};

#endif // ABRIRHISTORIA_H
