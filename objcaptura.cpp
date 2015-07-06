#include "objcaptura.h"

objCaptura::objCaptura(QObject *parent) : QObject(parent){

    detenerse = false;
}

void objCaptura::start(int id){

    detenerse = false;
    cam.open(id);

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
            //captura unas cuantas imagenes mas, para asegurarse de que que la camara si esta desconectada
            for(int i = 0; i < 3; ++i){
                cam >> mat;
                cv::cvtColor(mat, mat, CV_BGR2RGB);
                img = QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
            }

            if(img.allGray()){
                emit interrumpirConexion();
                return;
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

