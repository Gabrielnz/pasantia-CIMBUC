#ifndef OBJCAPTURA_H
#define OBJCAPTURA_H

#include <QImage>
#include <QPixmap>
#include <QObject>
#include <QDebug>
#include <QThread>
#include <QCamera>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class objCaptura : public QObject
{
    Q_OBJECT
public:
    explicit objCaptura(QObject *parent = 0);
    void start(int id);
    ~objCaptura();

signals:
    void nueva_imagen(QPixmap pixOriginal, QPixmap pixMicroM);
    void interrumpirConexion();
    void limpiarVista();

public slots:
    void stop();

private:
    bool detenerse;
    cv::VideoCapture cam;
    cv::Mat mat, matMicroM;
    QImage img, imgMicroM;
};

#endif // OBJCAPTURA_H
