#ifndef ELIMINARHISTORIA_H
#define ELIMINARHISTORIA_H

#include <QDialog>
#include <QFileSystemModel>
#include <QDirModel>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QByteArray>
#include "dlginfo.h"

namespace Ui {
class eliminarHistoria;
}

class eliminarHistoria : public QDialog
{
    Q_OBJECT

public:
    explicit eliminarHistoria(QString rutaExt, QString *historiaExt, QString *lesionExt, QWidget *parent = 0);
    ~eliminarHistoria();

private slots:
    void on_btnCancelar_clicked();

    void on_btnEliminar_clicked();

private:
    Ui::eliminarHistoria *ui;
    QString ruta, *historia, *lesion;
    QFile jHistoria;
};

#endif // ELIMINARHISTORIA_H
