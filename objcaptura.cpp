#include "objcaptura.h"

objCaptura::objCaptura(QObject *parent) : QObject(parent){

    detenerse = false;
}

void objCaptura::start(int id){

    detenerse = false;
    cam.open(id);

    for(int i = 0; i < 3; ++i){
        cam >> mat;
    }

    for(;;){

        if(detenerse){
            cam.release();
            emit limpiarVista();
            return;
        }

        mat.release();
        cam >> mat;

        //se prepara la imagen para convertirla de BGR A RGB para que Qt pueda manejarla
        cv::cvtColor(mat, mat, CV_BGR2RGB);
        //ocurre la conversion de cv mat a qimage. Investigar sobre cual QImage::Format_ es mas apropiado
        img = QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);

        if(!img.allGray()){
            emit nueva_imagen(QPixmap::fromImage(img));
        }else{
            //si la imagen que contiene la matriz es negra, revisa que la camara este conectada
            cam.release();
            cam.open(id);
            //trata de reconectar la camara, si falla en el proceso, significa que efectivamente la camara se desconecto
            if(!cam.isOpened()){
                emit interrumpirConexion();
                return;
            }else{
                //en caso de que la camara no se haya desconectado, captura 3 imagenes para "limpiar" la matriz donde se almacenan las imagenes de cualquier imagen negra
                for(int i = 0; i < 3; ++i){
                    cam >> mat;
                }
            }
        }
    }
}

objCaptura::~objCaptura()
{

}

void objCaptura::stop(){

    detenerse = true;
}

