
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
using namespace cv; // Espacio de nombres de OpenCV (Contiene funciones y definiciones de varios elementos de OpenCV)


int main(int argc, char *argv[]) {
    // En OpenCV las imágenes a color se representan como BGR:

    // Leemos la imagen y la guardamos en una matriz llamada "imagen"
    Mat imagen1 = imread("../img1.png");//, COLOR_BGR2GRAY);
    Mat imagen2 = imread("../img2.png");//, COLOR_BGR2GRAY);
    Mat imagenVacia = Mat::zeros(Size(779, 527), CV_8UC3);

    cout << imagen1.cols << " | " << imagen2.cols << " | " << imagenVacia.cols << " | " << endl;
    cout << imagen1.rows << " | " << imagen2.rows << " | " << imagenVacia.rows << " | " << endl;
    namedWindow("IMG1", WINDOW_AUTOSIZE);
    namedWindow("IMG1", WINDOW_AUTOSIZE);
    namedWindow("NEW", WINDOW_AUTOSIZE);

    vector<Point> points;
    //int c = 0, b = 0;
    for (int i = 0; i < imagenVacia.rows; i++) {
        for (int j = 0; j < imagenVacia.cols; j++) {
            if (!(imagen1.at<Vec3b>(i, j) != imagen2.at<Vec3b>(i, j))) continue;
            points.emplace_back(j, i);
        }
    }
    int xmenor = -1, xmayor = imagenVacia.rows * imagenVacia.cols;
    int ymenor = -1, ymayor = imagenVacia.rows * imagenVacia.cols;

    for (auto &point : points) {
        imagenVacia.at<Vec3b>(point) = Vec3b(255, 255, 255);
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
    }
    circle(imagenVacia, Point(xmenor, ymenor), 32.0, Scalar(0, 0, 255), 1, 8);
    circle(imagenVacia, Point(xmayor, ymenor), 32.0, Scalar(0, 0, 255), 1, 8);
    circle(imagenVacia, Point(points[0].x, ymayor), 32.0, Scalar(0, 0, 255), 1, 8);

    cout << Point(xmenor, ymenor) << endl;
    cout << Point(xmayor, ymenor) << endl;
    cout << Point(points[0].x, ymayor) << endl;

    vector<Point> pointsr;


    pointsr.push_back(Point(points[0].x , ymayor ));
    pointsr.push_back(Point(xmenor, ymenor));
    pointsr.push_back(Point(xmayor, ymenor));

    Mat mask = Mat::zeros(imagenVacia.size(), CV_8UC1);
    fillConvexPoly(mask, pointsr, Scalar(255));

    Rect rect = boundingRect(pointsr);
    Mat roi = imagenVacia(rect).clone();
    mask = mask(rect).clone();


    Mat srcROI = imagen1(rect);
    roi.copyTo(srcROI, mask);


    cout << xmenor << " | " << ymenor << endl;
    imshow("IMG1", imagen1);
    imshow("IMG2", imagen2);
    imshow("NEW", imagenVacia);

    waitKey(0);
    destroyAllWindows();

    return 0;
}


