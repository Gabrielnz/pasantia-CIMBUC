#ifndef CREARLESION_H
#define CREARLESION_H

#include <QDialog>
#include <QDir>

namespace Ui {
class crearLesion;
}

class crearLesion : public QDialog
{
    Q_OBJECT

public:
    explicit crearLesion(QWidget *parent = 0);
    explicit crearLesion(QString dirRaizExt, QString historiaExt, QString *lesionExt);
    ~crearLesion();

private slots:
    void on_lineaLesion_textChanged(const QString &nuevaLesion);

    void on_btnCancelar_clicked();

    void on_btnAceptar_clicked();

private:
    Ui::crearLesion *ui;
    QString dirRaiz;
    QString historia;
    QString *lesion;
    bool lesionLista;
};

#endif // CREARLESION_H
