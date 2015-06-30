#ifndef DLGCONFIRMAR_H
#define DLGCONFIRMAR_H

#include <QDialog>

namespace Ui {
class dlgConfirmar;
}

class dlgConfirmar : public QDialog
{
    Q_OBJECT

public:
    explicit dlgConfirmar(QString mensaje, QString titulo, QWidget *parent = 0);
    bool confirmacion();
    ~dlgConfirmar();

private slots:
    void on_btnAceptar_clicked();

    void on_btnCancelar_clicked();

private:
    Ui::dlgConfirmar *ui;
    bool confirmar;
};

#endif // DLGCONFIRMAR_H
