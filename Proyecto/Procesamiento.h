//
// Created by vinic on 1/24/2021.
//


#include <iostream>
#include <cstdlib>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 * @name: no necesaria
 * Metodos de procesamiento de imagne
 */
class Procesamiento {
public:
    String name;
    Point incio = Point(0, 0);
    Point fin = Point(625, 299);
    Point centro = Point(0, 0);
    vector<Point> pointRect;

    Mat FRAME;
    Mat FONDO;
    Mat ROI;
    Mat ROI_GRAY;
    Mat RESTA;
    Mat PROCESADA;
    Mat VIDEO;
    Mat IMGORG;

    vector<vector<Point> > contours;

    Moments momentos;


    Procesamiento(string name);

    void graficarRectangulo();

    void cortarzonafondo();

    void cortarzonainteres();

    void restarfondo();

    void procesarimagen(int val_dil, int val_thre);

    void buscarContornos();

    void buscarContornoGrande();

    void graficarContorno();

    void obetenrMomentos();

    void graficarCentro();

    void unirRecorte();


};

