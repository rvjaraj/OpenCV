
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
    Mat imagen1 = imread("../1.png", COLOR_BGR2GRAY);
    Mat imagen2 = imread("../2.png", COLOR_BGR2GRAY);
    Mat imagenVacia = Mat::zeros(imagen1.size(), CV_8UC3);

    namedWindow("IMG1", WINDOW_AUTOSIZE);
    namedWindow("IMG1", WINDOW_AUTOSIZE);
    namedWindow("NEW", WINDOW_AUTOSIZE);

    vector<Point> points;
    Point point;
    int xmenor = -1, xmayor = imagenVacia.rows * imagenVacia.cols;
    int ymenor = -1, ymayor = imagenVacia.rows * imagenVacia.cols;
    int p_ini = -1;
    int a = 0, b = 0;
    for (int i = 0; i < imagenVacia.rows; i++) {
        for (int j = 0; j < imagenVacia.cols; j++) {

            imagenVacia.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
            if ((imagen1.at<Vec3b>(i, j) != imagen2.at<Vec3b>(i, j))) {
                a = a + 1;
                point = Point(j, i);
                imagenVacia.at<Vec3b>(point) = imagen2.at<Vec3b>(point);
                if (xmenor < point.x) {
                    xmenor = point.x;
                }
                if (ymenor < point.y) {
                    ymenor = point.y;
                }
                if (xmayor > point.x) {
                    xmayor = point.x;
                }
                if (ymayor > point.y) {
                    ymayor = point.y;
                }
                if (p_ini == -1) {
                    p_ini = point.x;
                }
            } else {
                b = b + 1;
            }
        }
    }
    cout << a << " | " << b;

    vector<Point> pointsr;
    pointsr.emplace_back(p_ini, ymayor);
    pointsr.emplace_back(xmenor, ymenor);
    pointsr.emplace_back(xmayor, ymenor);

    Mat mask = Mat::zeros(imagenVacia.size(), CV_8UC1);
    fillConvexPoly(mask, pointsr, Scalar(255));
    Rect rect = boundingRect(pointsr);

    Mat roi = imagenVacia(rect).clone();

    mask = mask(rect).clone();
    Mat srcROI = imagen1(rect);


    roi.copyTo(srcROI, mask);

    imshow("IMG1", imagen1);
    imshow("IMG2", imagen2);
    imshow("NEW", imagenVacia);

    waitKey(0);
    destroyAllWindows();

    return 0;
}


