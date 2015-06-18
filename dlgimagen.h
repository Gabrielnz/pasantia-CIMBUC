#ifndef DLGIMAGEN_H
#define DLGIMAGEN_H

#include <QDialog>

namespace Ui {
class dlgImagen;
}

class dlgImagen : public QDialog
{
    Q_OBJECT

public:
    explicit dlgImagen(QWidget *parent = 0);
    explicit dlgImagen(QString nombreImagen);
    bool getReemplazar();
    ~dlgImagen();

private:
    Ui::dlgImagen *ui;
};

#endif // DLGIMAGEN_H
