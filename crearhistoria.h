#ifndef CREARHISTORIA_H
#define CREARHISTORIA_H

#include <QDialog>
#include <QDir>
#include <QDebug>
#include <QString>

namespace Ui {
class crearHistoria;
}

class crearHistoria : public QDialog
{
    Q_OBJECT

public:
    explicit crearHistoria(QWidget *parent = 0);
    explicit crearHistoria(QString dirRaizExt, QString *historiaExt);
    ~crearHistoria();

private slots:
    void on_btnCancelar_clicked();

    void on_lineaCrearHistoria_textChanged(const QString &nuevaHistoria);

    void on_btnCrearHistoria_clicked();

private:
    Ui::crearHistoria *ui;
    QString dirRaiz;
    QString *historia;
};

#endif // CREARHISTORIA_H
