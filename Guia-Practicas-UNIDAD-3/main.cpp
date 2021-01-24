#include "Procesamiento.h"

int val_pim = 10;
int val_sal = 10;
int val_med = 10;
int val_gau = 10;

void functionTrackbar(int v, void *p) {
}


int main(int argc, char *argv[]) {
    VideoCapture video("../video.mp4");
    if (video.isOpened()) {
        Mat img;
        Mat gris;
        namedWindow("Original", WINDOW_AUTOSIZE);
        namedWindow("Gris", WINDOW_AUTOSIZE);
        namedWindow("Sal", WINDOW_AUTOSIZE);
        namedWindow("Pimiento", WINDOW_AUTOSIZE);
        namedWindow("MedianBlur", WINDOW_AUTOSIZE);
        namedWindow("Gaussian Blur", WINDOW_AUTOSIZE);
        while (3 == 3) {
            video >> img;
            resize(img, img, Size(), 0.7, 0.7);
            Procesamiento procesamiento("");

            gris = procesamiento.to_gris(img);
            Mat sal = procesamiento.sal_o_pimineta( gris, val_sal, false);
            Mat pim = procesamiento.sal_o_pimineta(gris, val_pim, true);
            Mat media = procesamiento.median_brur(gris,val_med);
            Mat gausi = procesamiento.median_brur(gris,val_gau);

            createTrackbar("Sal", "Original", &val_sal, 100, functionTrackbar);
            createTrackbar("Pimiento", "Original", &val_pim, 100, functionTrackbar);
            createTrackbar("MedianBLur", "Original", &val_med, 100, functionTrackbar);
            createTrackbar("Gaussian Blur", "Original", &val_gau, 100, functionTrackbar);

            imshow("Original", img);
            imshow("Gris", gris);
            imshow("Sal", sal);
            imshow("Pimiento", pim);
            imshow("MedianBlur", media);
            imshow("Gaussian Blur", gausi);
            if (waitKey(23) == 27)
                break;


        }
        destroyAllWindows();
    }
    Mat img = imread("../colors.jpg");

    return 0;
}


