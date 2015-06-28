#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QTextDocument>
#include <QtCore>
#include <QDebug>
#include <QDesktopServices>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "acercade.h"
#include "crearhistoria.h"
#include "dlgimagen.h"
#include "dlgconfirmar.h"
#include "dlginfo.h"
#include "crearlesion.h"
#include "abrirhistoria.h"
#include "abrirlesion.h"
#include "eliminarhistoria.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setDirRaiz(QString raiz);
    void setHistoria(QString historia);
    QString getDirRaiz();
    QString getHistoria();
    void revision();
    ~MainWindow();

public slots:
    void procesarCuadroActualizarGUI();/*Procedimiento donde la magia sucede :b*/

private slots:

    void on_actionAcerca_de_triggered();

    void on_actionSalir_triggered();

    void on_actionConectar_camara_triggered();

    void on_actionDesconectar_camara_triggered();

    void on_actionCrear_historia_triggered();

    void on_actionCerrar_historia_triggered();

    void on_cBoxModo_currentIndexChanged(int index);

    void setBotones(bool flag);

    void accionBotones(QString color);

    void setColorDisponible(int colorIndex);

    void on_btnRojo_clicked();

    void on_btnVerde_clicked();

    void on_btnAzul_clicked();

    void on_btnCyan_clicked();

    void on_btnMagenta_clicked();

    void on_btnAmarillo_clicked();

    void on_btnBlanco_clicked();

    void on_actionCerrar_lesion_triggered();

    void on_btnGenerarReporte_clicked();

    void on_actionNueva_lesion_triggered();

    void on_actionAbrir_historia_triggered();

    void on_actionAbrir_lesion_triggered();

    void on_actionEliminar_historia_triggered();

    void on_actionEliminar_lesion_triggered();

    void on_btnAbrirCarpeta_clicked();

private:
    Ui::MainWindow *ui;
    cv::VideoCapture capWebcam;
    cv::Mat matOriginal;
    QImage qimg;
    QTimer *tmrTimer;
    QString dirRaiz;
    QString *historia, *lesion;
    QString fecha, *fechaLesion;
    QLockFile *locker;
};

#endif // MAINWINDOW_H
