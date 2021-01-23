
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


int main(int argc, char *argv[]) {
    Mat img_original = imread("../colors.jpg", COLOR_BGR2GRAY);
    namedWindow("Original", WINDOW_AUTOSIZE);
    namedWindow("Ruido Sal", WINDOW_AUTOSIZE);
    namedWindow("Gris", WINDOW_AUTOSIZE);
    resize(img_original, img_original, Size(), 0.2, 0.2);
    Mat gris;
    cvtColor(img_original, gris, COLOR_BGR2GRAY);
    Mat imagenRuidoSal = gris.clone();

    int total = (int) (0.5 * gris.rows * gris.cols);
    cout << "Total: " << total << endl;
    int cont = 0;
    int fila = 0;
    int col = 0;

    srand(time(0));
    while (cont < total) {
        fila = rand() % gris.rows;
        col = rand() % gris.cols;

        cont++;
        imagenRuidoSal.at<uchar>(fila, col) = 1;
    }

    imshow("Original", img_original);
    imshow("Gris", gris);
    imshow("Ruido Sal", imagenRuidoSal);
    waitKey(0);
    destroyAllWindows();

    return 0;
}


