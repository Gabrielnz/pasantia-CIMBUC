#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QTextDocument>
#include <QtCore>
#include <QLabel>
#include <QDebug>
#include <QDesktopServices>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "acercade.h"
#include "crearhistoria.h"
#include "dlgimagen.h"
#include "dlgconfirmar.h"
#include "dlginfo.h"
#include "regicon.h"
#include "abrirhistoria.h"
#include "abriricon.h"
#include "verhistoria.h"
#include "regabriricon.h"

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

private slots:
    void procesarCuadroActualizarGUI();/*Procedimiento donde la magia sucede :b*/

    void on_actionAcerca_de_triggered();

    void on_actionSalir_triggered();

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

    void on_actionCerrar_icon_triggered();

    void on_actionRegistrar_Iconografia_triggered();

    void on_actionAbrir_historia_triggered();

    void on_actionAbrir_icon_triggered();

    void on_btnAbrirCarpeta_clicked();

    void conectarCamaras(int num);

    void on_actionVer_historia_triggered();

    void on_actionActualizar_triggered();

private:
    Ui::MainWindow *ui;
    cv::VideoCapture cam;
    cv::Mat mat;
    QImage qimg;
    QTimer *tmrTimer;
    QString dirRaiz, *historia, *icon, fecha, *fechaIcon;
    int indexCam, numCams;
    QList<QAction*> accionesDinamicas;
    QSignalMapper *signalMapper;
    QString txtCamara, txtVistaPrev;
};

#endif // MAINWINDOW_H
