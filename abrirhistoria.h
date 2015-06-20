#ifndef ABRIRHISTORIA_H
#define ABRIRHISTORIA_H

#include <QDialog>
#include <QFileSystemModel>
#include <QDirModel>
#include <QDebug>

namespace Ui {
class abrirHistoria;
}

class abrirHistoria : public QDialog
{
    Q_OBJECT

public:
    explicit abrirHistoria(QWidget *parent = 0);
    explicit abrirHistoria(QString *historiaExt, QString *lesionExt, QString rutaExt);
    ~abrirHistoria();

private slots:
    void on_btnCancelar_clicked();

    void on_btnAbrir_clicked();

    void on_listView_clicked(const QModelIndex &index);

private:
    Ui::abrirHistoria *ui;
    QString ruta;
    QFileSystemModel *modeloDir;
    QString *historia, *lesion;
};

#endif // ABRIRHISTORIA_H
