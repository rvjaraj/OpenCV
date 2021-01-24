//
// Created by vinic on 1/24/2021.
//

#include "Procesamiento.h"

Mat catedral = imread("../colors.png", IMREAD_GRAYSCALE);

Procesamiento::Procesamiento(string n, Mat img, int p, bool t) {
    this->name = n;
    this->image = img;
    this->posicion = p;
    this->type = t;
}

Procesamiento::Procesamiento(string n) {
    this->name = n;
}

void Procesamiento::tamanio_imagen() {
    cout << this->name << endl;
}

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

Mat Procesamiento::to_gris(Mat img) {
    Mat gris;
    cvtColor(img, gris, COLOR_BGR2GRAY);
    return gris;
}

Mat Procesamiento::gaussian_blur(Mat im, int k) {
    k = (k % 2 != 1) ? k - 1 : k;
    k = (k < 1) ? 1 : k;
    Mat img;
    GaussianBlur(im, img, Size(k, k), 2, 2);
    return img;

}

Mat Procesamiento::median_brur(Mat im, int k) {
    k = (k % 2 != 1) ? k - 1 : k;
    k = (k < 1) ? 1 : k;

    Mat img;
    medianBlur(im, img, k);
    return img;

}