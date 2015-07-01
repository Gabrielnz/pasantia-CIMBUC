#ifndef DLGIMAGEN_H
#define DLGIMAGEN_H

#include <QDialog>
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QByteArray>

namespace Ui {
class dlgImagen;
}

class dlgImagen : public QDialog
{
    Q_OBJECT

public:
    explicit dlgImagen(QString nombreImagen, QString colorExt, QString rutaExt, QString fechaExt, QWidget *parent = 0);
    void actAnotaciones();
    bool getReemplazar();
    ~dlgImagen();

private slots:
    void on_btnAceptar_clicked();

private:
    Ui::dlgImagen *ui;
    QString color, ruta, fecha;
    QFile jAnotaciones;
};

#endif // DLGIMAGEN_H
