//
// Created by vinic on 1/24/2021.
//

#include "Procesamiento.h"


Procesamiento::Procesamiento(string n) {
    this->name = n;
}

void Procesamiento::tamanio_imagen() {
    cout << this->name << endl;
}

/*
 * Metodo para calcular un porcentaje de sal o pimienta
 * @img: Imagen de entrada
 * @k: porcentaje de procesamienta
 * @type: true = sal | false = pimienta
 * pasamos @k de [0-100] a [0-1]
 * calculamos el porcentaje en base a columnas y filas
 * recorremos el numero de pixeles a cambia: true: pixel blanco | false: pixel negro
 *
 * @return: imagen procesado
 */
Mat Procesamiento::sal_o_pimineta(Mat img, int k, bool type) {
    double t = (k < 10) ? stod("0.0" + to_string(k)) :
               stod("0." + to_string(k));
    t = (k == 100) ? 1 : t;
    Mat img_trat = img.clone();
    int total = (int) (t * img_trat.rows * img_trat.cols);
    int cont = 0, fila = 0, col = 0;
    while (cont < total) {
        fila = rand() % img_trat.rows;
        col = rand() % img_trat.cols;
        cont++;
        img_trat.at<uchar>(fila, col) = (type == 0) ? 255 : 0;
    }
    return img_trat;
}

/*
 * Convertir imagen de color a escala de grises
 * @imagen de entrdad
 * @return imagen procesada en escala de grises
 */
Mat Procesamiento::to_gris(Mat img) {
    Mat gris;
    cvtColor(img, gris, COLOR_BGR2GRAY);
    return gris;
}
/*
 * usamos gausian blur
 * @img: Imagen a procesar
 * @k: valor del kerne
 *
 * validamos que k sea impar
 * validamos que k sea mayor a 0
 */
Mat Procesamiento::gaussian_blur(Mat im, int k) {
    k = (k % 2 != 1) ? k - 1 : k;
    k = (k < 1) ? 1 : k;
    Mat img;
    GaussianBlur(im, img, Size(k, k), 2, 2);
    return img;

}
/*
 * Usando medianblur procesamos el filtro de una imagen
 * @img: imagen a procesar
 * @k: valor del kernel
 */
Mat Procesamiento::median_brur(Mat im, int k) {
    k = (k % 2 != 1) ? k - 1 : k;
    k = (k < 1) ? 1 : k;

    Mat img;
    medianBlur(im, img, k);
    return img;

}
/*
 * Img >> sobel uniendo X y Y
 * @img: Imagen a procesar
 * procesmos imagen con x
 * procesmos imagen con y
 * unimos las imagenes en x y y
 * @return: imagen procesado
 */
Mat Procesamiento::gxgy(Mat img) {
    Mat gX, gY;
    Mat gXAbs, gYAbs;
    Mat sobelBordes;
    Sobel(img, gX, CV_16S, 1, 0, 3);
    Sobel(img, gY, CV_16S, 0, 1, 3);
    convertScaleAbs(gX, gXAbs);
    convertScaleAbs(gY, gYAbs);
    addWeighted(gXAbs, 0.5, gYAbs, 0.5, 0, sobelBordes);
    return sobelBordes;
}
/*
 * Procesamiento con canny
 * @img: imagen a procesar
 * @return imagen procesada
 */
Mat Procesamiento::canny(Mat img, int umbral, int radio) {
    Mat can;
    Canny(img, can, umbral, umbral * (double) radio, 3);
    return can;
}