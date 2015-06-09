#ifndef OPCIONES_H
#define OPCIONES_H

#include <QDialog>

namespace Ui {
class Opciones;
}

class Opciones : public QDialog
{
    Q_OBJECT

public:
    explicit Opciones(QWidget *parent = 0);
    ~Opciones();

private:
    Ui::Opciones *ui;
};

#endif // OPCIONES_H
