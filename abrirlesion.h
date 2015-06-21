#ifndef ABRIRLESION_H
#define ABRIRLESION_H

#include <QDialog>
#include <QFileSystemModel>
#include <QDirModel>
#include <QDate>
#include <QDebug>

namespace Ui {
class abrirLesion;
}

class abrirLesion : public QDialog
{
    Q_OBJECT

public:
    explicit abrirLesion(QWidget *parent = 0);
    explicit abrirLesion(QString *lesionExt, QString rutaExt, QString *fechaLesionExt);
    ~abrirLesion();

private slots:
    void on_btnCancelar_clicked();

    void on_btnAbrir_clicked();

    void on_lesionList_clicked(const QModelIndex &indexIn);

    void on_fechaLesionList_clicked(const QModelIndex &indexIn);

private:
    Ui::abrirLesion *ui;
    QString ruta;
    QFileSystemModel *modeloLesion, *modeloFecha;
    QString *lesion;
    QString *fechaLesion, fechaSeleccionada;
};

#endif // ABRIRLESION_H
