#ifndef DLGREEMPLAZAR_H
#define DLGREEMPLAZAR_H

#include <QDialog>

namespace Ui {
class dlgReemplazar;
}

class dlgReemplazar : public QDialog
{
    Q_OBJECT

public:
    explicit dlgReemplazar(QWidget *parent = 0);
    explicit dlgReemplazar(QString color);
    bool getReemplazar();
    ~dlgReemplazar();

private slots:
    void on_btnReemplazar_clicked();
    void on_btnCancelar_clicked();

private:
    Ui::dlgReemplazar *ui;
    bool reemplazar;
};

#endif // DLGREEMPLAZAR_H
