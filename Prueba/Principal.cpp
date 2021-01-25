
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int main(int argc, char *argv[]) {
    //Leemos imagnes
    Mat img1 = imread("../JARA_JARA_RICARDO_VINICIO-1.png", COLOR_BGR2GRAY);
    Mat img2 = imread("../JARA_JARA_RICARDO_VINICIO-2.png", COLOR_BGR2GRAY);

    //Clono la primera imagen
    Mat unio = img1.clone();

    namedWindow("Imagen 1", WINDOW_AUTOSIZE);
    namedWindow("Imagen 2", WINDOW_AUTOSIZE);
    namedWindow("Resultado", WINDOW_AUTOSIZE);

    //JARA_JARA_RICARDO_VINICIO{cx = 108 cy = 150 radio = 16}
    //Pinto el circulo con pixele negros
    circle(img1, Point(108, 150), 16, Vec3b(0, 0, 0), -1);

    /*
     * recorremos la imagen
     * Buscamos en la primera imagen los pixeles negros
     * Si hay pixeles negros compiamos el pixel de la segunda imagen en la misma posicion
     */
    for (int y = 0; y < img1.rows; y++) {
        for (int x = 0; x < img1.cols; x++) {
            if (img1.at<Vec3b>(y, x) == Vec3b(0, 0, 0)) {
                unio.at<Vec3b>(y, x) = img2.at<Vec3b>(y, x);
            }
        }
    }
    //grabamos el resultad
    imwrite("../Resultado-Jara.png", unio);

    //Mostramos en pantalla
    imshow("Imagen 1", img1);
    imshow("Imagen 2", img2);
    imshow("Resultado", unio);


    waitKey(0);
    destroyAllWindows();
    return 0;
}

