#ifndef REGICON_H
#define REGICON_H

#include <QDialog>
#include <QDir>
#include "dlginfo.h"

namespace Ui {
class regIcon;
}

class regIcon : public QDialog
{
    Q_OBJECT

public:
    explicit regIcon(QString dirRaizExt, QString historiaExt, QString *iconExt, QWidget *parent = 0);
    ~regIcon();

private slots:
    void on_lineaIcon_textChanged(const QString &regIcon);

    void on_btnCancelar_clicked();

    void on_btnReg_clicked();

private:
    Ui::regIcon *ui;
    QString dirRaiz, historia, *icon;
    bool iconLista;
};

#endif // REGICON_H
