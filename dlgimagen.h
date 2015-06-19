#ifndef DLGIMAGEN_H
#define DLGIMAGEN_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>

namespace Ui {
class dlgImagen;
}

class dlgImagen : public QDialog
{
    Q_OBJECT

public:
    explicit dlgImagen(QWidget *parent = 0);
    explicit dlgImagen(QString nombreImagen, QString colorExt, QString rutaExt);
    void actAnotaciones();
    bool getReemplazar();
    ~dlgImagen();

private slots:
    void on_btnAceptar_clicked();

private:
    Ui::dlgImagen *ui;
    QString color;
    QString ruta;
    QFile anotacion;
};

#endif // DLGIMAGEN_H
