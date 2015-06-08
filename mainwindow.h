#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    ~MainWindow();

public slots:
    void procesarCuadroActualizarGUI();/*Procedimiento donde la magia sucede :b*/

private slots:

    void on_actionAcerca_de_triggered();
    void on_actionSalir_triggered();

    void on_actionIniciar_camara_triggered();

    void on_actionDetener_camara_triggered();

    void on_btnCapturar_clicked();

private:
    Ui::MainWindow *ui;

    cv::VideoCapture capWebcam;
    cv::Mat matOriginal;
    QImage qimg;
    QTimer *tmrTimer;
};

#endif // MAINWINDOW_H
