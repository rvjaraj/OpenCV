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

void Procesamiento::tamanio_imagen() {
    cout << this->image.size() << endl;
}

Mat Procesamiento::sal() {
    double t = (this->posicion < 10) ? stod("0.0" + to_string(this->posicion)) :
               stod("0." + to_string(this->posicion));
    t = (this->posicion == 100) ? 1 : t;
    Mat img_trat = this->image.clone();
    int total = (int) (t * img_trat.rows * img_trat.cols);
    int cont = 0, fila = 0, col = 0;
    while (cont < total) {
        fila = rand() % img_trat.rows;
        col = rand() % img_trat.cols;
        cont++;
        img_trat.at<uchar>(fila, col) = (this->type == 0) ? 255 : 0;
    }
    return img_trat;
}