#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

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
    void revisionHistoria();
    ~MainWindow();

public slots:
    void procesarCuadroActualizarGUI();/*Procedimiento donde la magia sucede :b*/

private slots:

    void on_actionAcerca_de_triggered();

    void on_actionSalir_triggered();

    void on_actionIniciar_camara_triggered();

    void on_actionDetener_camara_triggered();

    void on_actionOpciones_triggered();

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

private:
    Ui::MainWindow *ui;
    cv::VideoCapture capWebcam;
    cv::Mat matOriginal;
    QImage qimg;
    QTimer *tmrTimer;
    QString dirRaiz;
    QString historia;
    QString fecha;
};

#endif // MAINWINDOW_H
