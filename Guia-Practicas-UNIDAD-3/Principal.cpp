
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
    t = (t == 100) ? 1 : t;
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


int main(int argc, char *argv[]) {
    Mat img_original = imread("../guitars.jpg", COLOR_BGR2GRAY);
    namedWindow("Original", WINDOW_AUTOSIZE);
    namedWindow("Gris", WINDOW_AUTOSIZE);
    namedWindow("Ruido Sal", WINDOW_AUTOSIZE);
    namedWindow("Ruido Pimienta", WINDOW_AUTOSIZE);
    resize(img_original, img_original, Size(), 0.2, 0.2);
    Mat gris;
    cvtColor(img_original, gris, COLOR_BGR2GRAY);

    Mat imagenRuidoSal = gris.clone();
    Mat imagenRuidoPimienta = gris.clone();
    imshow("Original", img_original);
    imshow("Gris", gris);
    imshow("Ruido Sal", imagenRuidoSal);
    imshow("Ruido Pimienta", imagenRuidoPimienta);

    //Estructura para la imagen de Sal
    data_struc data;
    data.tipe = false;
    data.name = "Ruido Sal";
    data.img_gren = gris;
    createTrackbar("Sal", "Original", 0, 100, bar_sal_or_pimienta, (void *) &data);

    //Estructura para la imagen de pimienta
    data_struc data_;
    data_.tipe = true;
    data_.name = "Ruido Pimienta";
    data_.img_gren = gris;
    createTrackbar("Pimienta", "Original", 0, 100, bar_sal_or_pimienta, (void *) &data_);


    waitKey(0);
    destroyAllWindows();

    return 0;
}


