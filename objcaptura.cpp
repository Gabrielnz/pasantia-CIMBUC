#include "objcaptura.h"

objCaptura::objCaptura(QObject *parent) : QObject(parent){

    detenerse = false;
}

void objCaptura::start(int id){

    detenerse = false;
    cam.open(id);
    int w, h;
    w = cam.get(CV_CAP_PROP_FRAME_WIDTH);
    h = cam.get(CV_CAP_PROP_FRAME_HEIGHT);
    cv::Point p1(w/1.3, h/1.05);
    cv::Point p2(w/1.1, h/1.05);
    cv::Scalar color(0, 104, 255);
    cv::HersheyFonts fuente(cv::FONT_HERSHEY_PLAIN);

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

/////////////////////////////////////
        //matMicroM.release();
        mat.copyTo(matMicroM);
        //se prepara la imagen para convertirla de BGR A RGB para que Qt pueda manejarla
        //cv::putText(matMicroM, "micromarca", p1, fuente, 1, color, 1, cv::LINE_AA );
        cv::line(matMicroM, p1, p2, color, 1, cv::LINE_8);
        imgMicroM = QImage((uchar*)matMicroM.data, matMicroM.cols, matMicroM.rows, matMicroM.step, QImage::Format_RGB888);
/////////////////////////////////////
        if(!img.allGray()){
            emit nueva_imagen(QPixmap::fromImage(img), QPixmap::fromImage(imgMicroM));
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

