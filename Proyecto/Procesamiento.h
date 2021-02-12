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
    Point incio = Point(300, 13);
    Point fin = Point(625, 299);
    Point centro = Point(0, 0);
    Point alto = Point(0, 0);
    vector<Point> pointRect;
    vector<Point> ptsinicio;
    vector<Point> ptsfin;

    Mat FRAME;
    Mat FONDO;
    Mat ROI;
    Mat ROI_GRAY;
    Mat RESTA;
    Mat PROCESADA;

    vector<vector<Point> > contours;
    vector<vector<Vec4i>> defectos;

    Moments momentos;

    double huGesto0[7] = {1.308081, 1.0140784, 0.0274963, 0.00766985, 7.005e-005, -0.000412655, 8.65971e-005,};
    double huGesto1[7] = {1.363926, 1.0165625, 0.0470586, 0.0405827, 0.00169976, 0.00342234, -0.000506084};
    double huGesto2[7] = {1.350629, 1.00260514, 0.05463, 0.0143281, 0.000384134, 0.000197463, -0.000114605};
    double huGesto3[7] = {1.290316, 1.00316313, 0.0154033, 0.00391379, 2.91957e-005, -0.000124053, -8.42886e-006};
    double huGesto4[7] = {1.253104, 1.00466763, 0.00862564, 0.00266378, 1.27435e-005, 1.20071e-005, 8.01484e-007};
    double huGesto5[7] = {1.234323, 1.000994549, 0.00827551, 0.00355117, 1.89792e-005, 7.69953e-005, -3.22432e-006};

    Procesamiento(string name);

    void graficarRectangulo();

    void cortarzonafondo();

    void cortarzonainteres();

    void restarfondo();

    void procesarimagen(int val_dil);

    void buscarContornos();

    void buscarContornoGrande();

    void graficarContorno();

    void obetenrMomentos();

    void graficarCentro();

    void graficarAlto();

    void graficarCasco();

    void calcularDefectos();

    void graficarDefectos();

    void contarDedos();

    void guardarMomentos(int val_save);

    void detectarMomento(int val_save);


};

