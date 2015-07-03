#ifndef REGABRIRICON_H
#define REGABRIRICON_H

#include <QDialog>

namespace Ui {
class regAbrirIcon;
}

class regAbrirIcon : public QDialog
{
    Q_OBJECT

public:
    explicit regAbrirIcon(bool nueva, bool abrir, QWidget *parent = 0);
    bool opcionNueva();
    bool opcionAbrir();
    bool selecciono();
    ~regAbrirIcon();

private slots:
    void on_btnReg_clicked();

    void on_btnAbrir_clicked();

private:
    Ui::regAbrirIcon *ui;
    bool abrir, nueva, seleccionoAlgo;
};

#endif // REGABRIRICON_H
