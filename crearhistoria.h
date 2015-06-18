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
    QString getHistoriaCreada();
    QString getLesionCreada();
    ~crearHistoria();

private slots:
    void on_btnCancelar_clicked();

    void on_lineaCrearHistoria_textChanged(const QString &historia);

    void on_btnCrearHistoria_clicked();

    void on_lineaNuevaLesion_textChanged(const QString &lesion);

private:
    Ui::crearHistoria *ui;
    QString histCreada;
    QString lesionCreada;
    bool histLista, lesionLista;
};

#endif // CREARHISTORIA_H
