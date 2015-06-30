#ifndef DLGINFO_H
#define DLGINFO_H

#include <QDialog>

namespace Ui {
class dlgInfo;
}

class dlgInfo : public QDialog
{
    Q_OBJECT

public:
    explicit dlgInfo(QString mensaje, QString titulo, QWidget *parent = 0);
    ~dlgInfo();

private slots:
    void on_btnAceptar_clicked();

private:
    Ui::dlgInfo *ui;
};

#endif // DLGINFO_H
