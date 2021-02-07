#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * Calculamos el histogram del color rojo
 */
int *historgrama(Mat imagen) {
    int *histo = new int[256];

    for (int i = 0; i < 256; i++)
        histo[i] = 0;

    Vec3b pixel;
    for (int i = 0; i < imagen.rows; i++) {
        for (int j = 0; j < imagen.cols; j++) {
            //Solo tomanos el pixel 2 por el color rojo
            histo[imagen.at<Vec3b>(i, j)[2]]++;
        }
    }

    return histo;
}

/*
 * Calculamos la distancia euclidiana segun codigo del profe
 */
double euclidea(int *m1, int *m2) {
    double suma = 0.0;
    for (int i = 0; i < 256; i++) {
        suma += (m1[i] - m2[i]) * (m1[i] - m2[i]);
    }
    return sqrt(suma);
}


int main(int argc, char *argv[]) {
    /*
     * Inicio Parte 1
     */

    //leer nombreas
    vector<string> lista_imagnes;
    for (int i = 1; i < 57; ++i) {
        string k = i > 9 ? "00" : "000";
        lista_imagnes.push_back("../CORPUS-IMAGENES-1/image_" + k + to_string(i) + ".jpg");
    }
    //Variables necesarias
    int *his1;
    int *his2;
    Mat imagen1;
    Mat imagen2;
    double distancia = 0.0;
    double menor = 999 * 999 + 0.99;
    string numero;
    string nombre = "../CORPUS-IMAGENES-1/image_00";
    for (int i = 0; i < 56; i++) {
        if (i % 2 == 0) {
            imagen1 = imread(lista_imagnes[i]);
            imagen2 = imread(lista_imagnes[i + 1]);
            his1 = historgrama(imagen1);
            his2 = historgrama(imagen2);
            distancia = (double) euclidea(his1, his2);
            if (distancia < menor){
                menor = distancia;
            }

            cout << lista_imagnes[i] << "  |  " << lista_imagnes[i + 1] << " Distancia: " << distancia << endl;
        }
    }
    cout << "Parte 1: Distancia: " << menor << endl;
    /*
     * Fin Parte 1
     *
     *
     * Inicio Parte 2
     */

    double suma = 0.0;//Suma de pixeles
    Mat img1 = imread("../CORPUS-IMAGENES-1/image_0053.jpg", IMREAD_GRAYSCALE);
    for (int i = 0; i < img1.rows; i++) {//recorremos la imagen
        for (int j = 0; j < img1.cols; j++) {
            suma += img1.at<uchar>(i, j);
        }
    }
    double total = suma / (img1.rows * img1.channels() * img1.cols);
    cout << "Parte 2: Promedio: " << total << endl;

    /*
     * Fin part 2
     *
     * Inicio parte 3
     */
    //Generamos imagen
    uchar data[4][4] = {{123, 97, 10,  91},
                        {89,  47, 19,  101},
                        {7,   3,  250, 28},
                        {13,  1,  0,   200}};
    Mat img(4, 4, CV_8UC1, &data);
    Mat binaria;
    threshold(img, binaria, 12, 1, THRESH_BINARY);//usamos el metodo especificado
    Moments momentos = moments(binaria, true);
    double momento = (double) momentos.m10;//Calculamos el moento
    cout << "Parte 3: Momento 10: " << momento << endl;
    /*
     * Fin part 3
     *
     */
    return 0;
}

