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

using namespace std;
using namespace cv;


class Procesamiento {
public:
    String name;
    Mat image;
    int posicion;
    bool type;

    void tamanio_imagen();

    Mat sal_o_pimineta();

    Mat to_gris(Mat);

    Mat median_brur(Mat, int);

    Procesamiento(string, Mat, int, bool);

    Procesamiento(string);

};

