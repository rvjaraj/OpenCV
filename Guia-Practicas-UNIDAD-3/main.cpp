#include "Procesamiento.h"

int k = 10;

int main(int argc, char *argv[]) {
    Mat img = imread("../colors.jpg");
    resize(img, img, Size(), 0.3, 0.3);
    cvtColor(img, img, COLOR_BGR2GRAY);
    Procesamiento procesamiento_sal("Sal", img, k, true);
    procesamiento_sal.tamanio_imagen();
    Mat sal = procesamiento_sal.sal();

    Procesamiento procesamiento_pim("Sal", img, k, false);
    procesamiento_pim.tamanio_imagen();
    Mat pim = procesamiento_pim.sal();

    namedWindow("Original", WINDOW_AUTOSIZE);
    namedWindow("Gris", WINDOW_AUTOSIZE);
    namedWindow("Pim", WINDOW_AUTOSIZE);

    imshow("Original", img);
    imshow("Gris", sal);
    imshow("Pim", pim);
    waitKey(0);
    destroyAllWindows();
    return 0;
}


