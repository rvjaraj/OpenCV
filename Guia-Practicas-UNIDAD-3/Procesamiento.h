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

/*
 * @name: no necesaria
 * Metodos de procesamiento de imagne
 */
class Procesamiento {
public:
    String name;

    void tamanio_imagen();

    Mat sal_o_pimineta(Mat, int, bool);

    Mat to_gris(Mat);

    Mat gaussian_blur(Mat, int);

    Mat median_brur(Mat, int);

    Mat gxgy(Mat);

    Mat canny(Mat, int, int);

    Procesamiento(string);

};

