#ifndef VERHISTORIA_H
#define VERHISTORIA_H

#include <QDialog>
#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QByteArray>

namespace Ui {
class verHistoria;
}

class verHistoria : public QDialog
{
    Q_OBJECT

public:
    explicit verHistoria(QString ruta, QString historia, QWidget *parent = 0);
    ~verHistoria();

private slots:
    void on_btnAceptar_clicked();

private:
    Ui::verHistoria *ui;
};

#endif // VERHISTORIA_H
