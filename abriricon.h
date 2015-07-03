#ifndef ABRIRICON_H
#define ABRIRICON_H

#include <QDialog>
#include <QFileSystemModel>
#include <QDirModel>
#include <QDate>
#include <QDebug>

namespace Ui {
class abrirIcon;
}

class abrirIcon : public QDialog
{
    Q_OBJECT

public:
    explicit abrirIcon(QString *iconExt, QString rutaExt, QString *fechaIconExt, QWidget *parent = 0);
    ~abrirIcon();

private slots:
    void on_btnCancelar_clicked();

    void on_btnAbrir_clicked();

    void on_iconList_clicked(const QModelIndex &indexIn);

    void on_fechaIconList_clicked(const QModelIndex &indexIn);

private:
    Ui::abrirIcon *ui;
    QString ruta, *icon, *fechaIcon, fechaSeleccionada;
    QFileSystemModel *modeloIcon, *modeloFecha;
};

#endif // ABRIRICON_H
