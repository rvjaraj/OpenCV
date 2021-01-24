
#include <iostream>
#include <cstdlib>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/videoio/videoio.hpp>

using namespace std;
using namespace cv;

/**
 * Estructura de datos que pasara como parámetros en la barra de sal o pimienta
 * @tipe: true == pimienta | false == sal
 * @name: Nombre de la ventana a cambiar
 * @img_gren: Imagen original en escala de grises
 */
struct data_struc {
    bool tipe;
    String name;
    Mat img_gren;
};

/**Método que cambia un porcentaje de pixeles de la imagen a blanco (sal) o negro(pimienta)
   * @v: valor de la barra
   * @userdata Estrcutra que llega
   */
void bar_sal_or_pimienta(int v, void *userdata) {
    //Convertimo de memoria a nuestra estructura
    data_struc data = *((data_struc *) userdata);
    //Pasamos el valor de V [0-100] a [0-1] Y usar porcentaje entre el 1%-100%
    double t = (v < 10) ? stod("0.0" + to_string(v)) :
               stod("0." + to_string(v));
    t = (v == 100) ? 1 : t;
    Mat img_trat = data.img_gren.clone();
    int total = (int) (t * img_trat.rows * img_trat.cols);
    int cont = 0, fila = 0, col = 0;
    while (cont < total) {
        fila = rand() % img_trat.rows;
        col = rand() % img_trat.cols;
        cont++;
        //Validamos si es true para pixel blanco o false para pixel negro
        img_trat.at<uchar>(fila, col) = (data.tipe == 0) ? 255 : 0;
    }
    imshow(data.name, img_trat);
}

Mat imagenMediana;
Mat imagen;
Mat imagenGaussiana;


void functionTrackbar(int v, void *p) {

    if (v % 2 == 1) {
        medianBlur(imagen, imagenMediana, v);
        GaussianBlur(imagen, imagenGaussiana, Size(v, v), 2, 2);
        imshow("Mediana", imagenMediana);
        imshow("GaussianBlur", imagenGaussiana);
    }
}

int k = 10;
int k1 = 10;

int main(int argc, char *argv[]) {
    VideoCapture video("../video.mp4");
    if (video.isOpened()) {
        Mat frame;
        Mat gris;
        namedWindow("Original", WINDOW_AUTOSIZE);
        namedWindow("Gris", WINDOW_AUTOSIZE);
        namedWindow("Ruido Sal", WINDOW_AUTOSIZE);
        namedWindow("Ruido Pimienta", WINDOW_AUTOSIZE);


        while (3 == 3) {
            video >> frame;
            resize(frame, frame, Size(), 0.5, 0.5);
            cvtColor(frame, gris, COLOR_BGR2GRAY);

            Mat imagenRuidoSal = gris.clone();
            Mat imagenRuidoPimienta = gris.clone();


            data_struc data;
            data.tipe = false;
            data.name = "Ruido Sal";
            data.img_gren = gris;
            createTrackbar("Sal", "Original", &k, 100, bar_sal_or_pimienta, (void *) &data);

            double t = (k < 10) ? stod("0.0" + to_string(k)) :
                       stod("0." + to_string(k));
            t = (k == 100) ? 1 : t;

            Mat img_trat = gris.clone();
            int total = (int) (t * img_trat.rows * img_trat.cols);
            int cont = 0, fila = 0, col = 0;
            while (cont < total) {
                fila = rand() % img_trat.rows;
                col = rand() % img_trat.cols;
                cont++;
                //Validamos si es true para pixel blanco o false para pixel negro
                img_trat.at<uchar>(fila, col) = (data.tipe == 0) ? 255 : 0;
            }

            //Estructura para la imagen de pimienta
            data_struc data_;
            data_.tipe = true;
            data_.name = "Ruido Pimienta";
            data_.img_gren = gris;

            createTrackbar("Pimienta", "Original", &k1, 100, bar_sal_or_pimienta, (void *) &data_);

            imshow("Original", frame);
            imshow("Gris", gris);
            imshow("Ruido Sal", img_trat );
            imshow("Ruido Pimienta", imagenRuidoPimienta);

            if (waitKey(23) == 27)
                break;
        }

        destroyAllWindows();
    } else {
        cout << "No hay video" << endl;
    }


//    Mat img_original = imread("../guitars.jpg", COLOR_BGR2GRAY);
//
//
//
//
//
//


    //waitKey(0);
//    destroyAllWindows();
//    imagen = imread("../guitars.jpg", IMREAD_GRAYSCALE);
//    resize(imagen, imagen, Size(), 0.1, 0.1);
//    medianBlur(imagen, imagenMediana, k);
//    GaussianBlur(imagen, imagenGaussiana, Size(k, k), 2, 2);
//    namedWindow("Original", WINDOW_AUTOSIZE);
//    namedWindow("Mediana", WINDOW_AUTOSIZE);
//    namedWindow("GaussianBlur", WINDOW_AUTOSIZE);
//
//    imshow("Original", imagen);
//    imshow("Mediana", imagenMediana);
//    imshow("GaussianBlur", imagenGaussiana);
//    createTrackbar("Kernel", "Original", 0,100, functionTrackbar);
//    waitKey(0);
    return 0;
}


