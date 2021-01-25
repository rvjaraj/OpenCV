
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

Mat imagen1;
Mat imagen2;
Mat imagen3;
Mat imagen4;
Mat img1;
Mat img2;
int erosion_size = 7;
int dilation_size = 7;

int morph_size = 0;
int morph_size1 = 0;

/*
 *Mato para la suma y resta de imagenes
 * @img1: primera imagen a restar
 * @img2: Segunda imagen a restar
 * @img3: imagen que va a ser sumada con el Residuo de la @img1 - @img2
 * @name: Nombre de la vantana a mostrar la operacion realizada
 */
void suma_rest(Mat img1, Mat img2, Mat img3, String name = "Suma | Resta") {
    Mat resta;
    Mat suma;
    absdiff(img1, img2, resta);//Resta
    addWeighted(img3, 0.5, resta, 0.5, 0, suma);//suma
    imshow(name, suma);
}

void Erosion(int, void *) {
    Mat element = getStructuringElement(MORPH_CROSS, //MORPH_RECT [] MORPH_CROSS + MORPH_ELLIPSE O
                                        Size(2 * erosion_size + 1, 2 * erosion_size + 1),
                                        Point(0, 0));
    erode(imagen1, element, element);
    imshow("Erosion", element);
}


void Dilation(int, void *) {
    Mat element = getStructuringElement(MORPH_ELLIPSE,  //MORPH_RECT [] MORPH_CROSS + MORPH_ELLIPSE O
                                        Size(2 * dilation_size + 1, 2 * dilation_size + 1),
                                        Point(0, 0));
    dilate(imagen2, element, element);
    imshow("Dilation", element);
}

void Morphology_Operations6(int, void *) {
    int operation = 6;
    img1 = getStructuringElement(MORPH_ELLIPSE,  //MORPH_RECT [] MORPH_CROSS + MORPH_ELLIPSE O
                                 Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));
    morphologyEx(imagen2, img1, operation, img1);
    imshow("Back Hat", img1);

    suma_rest(img1, img2, imagen4, "Suma | Resta");
}

void Morphology_Operations5(int, void *) {
    int operation = 5;
    img2 = getStructuringElement(MORPH_ELLIPSE,  //MORPH_RECT [] MORPH_CROSS + MORPH_ELLIPSE O
                                 Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));
    morphologyEx(imagen3, img2, operation, img2);
    imshow("Top Hat", img2);
    suma_rest(img1, img2, imagen4, "Suma | Resta");

}


int main(int argc, char **argv) {

//    namedWindow("Radiografia 1", WINDOW_AUTOSIZE);
//    namedWindow("Erosion", WINDOW_AUTOSIZE);
//    imagen1 = imread("../radio1.jpg", IMREAD_COLOR);
//    resize(imagen1, imagen1, Size(), 0.4, 0.4);
//    imshow("Radiografia 1", imagen1);
//    createTrackbar("Eroicon", "Radiografia 1", &erosion_size, 37, Erosion, nullptr);
//    Erosion(0, nullptr);
//



    namedWindow("Back Hat", WINDOW_AUTOSIZE);
    imagen2 = imread("../radio1.jpg", IMREAD_COLOR);
    resize(imagen2, imagen2, Size(), 0.19, 0.19);
//    Dilation(0, nullptr);

    namedWindow("Radiografia 3", WINDOW_AUTOSIZE);
    imagen3 = imread("../radio1.jpg", IMREAD_COLOR);
    resize(imagen3, imagen3, Size(), 0.19, 0.19);
    imshow("Radiografia 3", imagen3);
    namedWindow("Top Hat", WINDOW_AUTOSIZE);
    createTrackbar("Top Hat", "Radiografia 3", &morph_size, 37, Morphology_Operations5);
    createTrackbar("Back Hat", "Radiografia 3", &morph_size1, 37, Morphology_Operations6);

    img1 = imagen2;
    img2 = imagen3;
    imagen4 = imagen3;
    Morphology_Operations5(0, 0);
    Morphology_Operations6(0, 0);


    namedWindow("Suma | Resta", WINDOW_AUTOSIZE);



    //
    //


    waitKey(0);
    return 0;
}




