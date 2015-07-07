#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QTextDocument>
#include <QtCore>
#include <QLabel>
#include <QDebug>
#include <QDesktopServices>
#include <QtConcurrent>
#include <QCameraInfo>
#include <QPainter>
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
#include "objcaptura.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void revisionBtns();
    void habilitarColores(bool flag);
    void disponibilidadColores();
    ~MainWindow();

signals:
    void on_stop();

private slots:
    void on_actionAcerca_de_triggered();
    void on_actionSalir_triggered();
    void on_actionDesconectar_camara_triggered();
    void on_actionCrear_historia_triggered();
    void on_actionCerrar_historia_triggered();
    void on_actionCerrar_icon_triggered();
    void on_actionRegistrar_Iconografia_triggered();
    void on_actionAbrir_historia_triggered();
    void on_actionAbrir_icon_triggered();
    void on_btnAbrirCarpeta_clicked();
    void on_actionVer_historia_triggered();
    void on_actionActualizar_triggered();
    void conectar(int num);
    void on_cBoxModo_activated(int index);
    void accionColores(QString color);
    void conexionInterrumpida();
    void limpiarVista();

    void on_checkMicroM_toggled(bool checked);

public slots:
    void procesar_imagen(QPixmap pixOriginal);

private:
    Ui::MainWindow *ui;
    QImage img;
    QString dirRaiz, *historia, *icon, fecha, *fechaIcon;
    int indexCam, numCams;
    QList<QAction*> accionesDinamicas;
    QSignalMapper camsMapper, coloresMapper;
    QString txtCamara, txtVistaPrev;
    QStringList colores;
    QList<QPushButton*> btnsColores;
    objCaptura captura;
    QFuture<void> hiloCaptura;
    bool conectado, microMarca;
    int w, h;
};

#endif // MAINWINDOW_H
