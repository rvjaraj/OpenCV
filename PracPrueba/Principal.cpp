
// Librerías que contienen funciones estándar de C++
#include <iostream>
#include <cstdlib>


// Librería que contiene funciones matemáticas
#include <cmath>

// Librerías de OpenCV

// Se pueden cargar todas las Librerías incluyendo
//#include <opencv2/opencv.hpp>

// Contiene las definiciones fundamentales de las matrices e imágenes
#include <opencv2/core/core.hpp>
// Procesamiento de imágenes
#include <opencv2/imgproc/imgproc.hpp>
// Códecs de imágenes
#include <opencv2/imgcodecs/imgcodecs.hpp>
// Manejo de ventanas y eventos de ratón, teclado, etc.
#include <opencv2/highgui/highgui.hpp>
// Lectura de video
#include <opencv2/video/video.hpp>
// Escritura de video
#include <opencv2/videoio/videoio.hpp>

using namespace std;
using namespace cv;


int main(int argc, char *argv[]) {
    Mat img = imread("../1.png", COLOR_BGR2GRAY);
    namedWindow("IMG1", WINDOW_AUTOSIZE);
    int _row = img.rows;
    int _row2 = _row / 2;
    for (double j = 0; j < img.cols; j = j + 0.08) {
        //saco el punto en las columnas
        Point p1(j * 30, (sin(j) * 30) + _row2);
        //Salo el punto 2 sumano el siguinete p
        Point p2((j + 0.08) * 30, (sin((j + 0.08)) * 30) + _row2);
        //linea de grafico sel seno
        line(img, p1, p2, Vec3b(1, 1, 1), 2);

        //linea desde el punto del ceno hasta el final de la img
        Point p3(j * 30, _row);
        line(img, p1, p3, Vec3b(1, 1, 1), 2);

    }
    imwrite("../imgTransformada.png", img);
    imshow("IMG1", img);
    waitKey(0);
    destroyAllWindows();

    return 0;
}


