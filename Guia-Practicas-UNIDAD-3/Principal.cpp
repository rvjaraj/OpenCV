
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

Mat imagen;
int erosion_size = 0;
int dilation_size = 0;

void Erosion(int, void *) {
    Mat element = getStructuringElement(MORPH_ELLIPSE, //MORPH_RECT MORPH_CROSS MORPH_ELLIPSE
                                        Size(2 * erosion_size + 1, 2 * erosion_size + 1));
    erode(imagen, element, element);
    imshow("Erosion Demo", element);
}


void Dilation(int, void *) {
    Mat element = getStructuringElement(MORPH_ELLIPSE, //MORPH_RECT MORPH_CROSS MORPH_ELLIPSE
                                        Size(2 * dilation_size + 1, 2 * dilation_size + 1));
    dilate(imagen, element, element);
    imshow("Dilation Demo", element);
}

int main(int argc, char **argv) {
    imagen = imread("../LinuxLogo.jpg", IMREAD_COLOR);
    namedWindow("Erosion Demo", WINDOW_AUTOSIZE);
    namedWindow("Dilation Demo", WINDOW_AUTOSIZE);

    Erosion(0, 0);
    Dilation(0, 0);
    createTrackbar("Kernel 2n +1", "Erosion Demo", &erosion_size, 20,Erosion, nullptr);
    createTrackbar("Kernel 2n +1", "Dilation Demo", &dilation_size, 20, Dilation, nullptr);


    waitKey(0);
    return 0;
}




