#include "Procesamiento.h"

int val_pim = 10;
int val_sal = 10;
int val_med = 10;

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
        namedWindow("Pimineta", WINDOW_AUTOSIZE);
        namedWindow("MedianBlur", WINDOW_AUTOSIZE);
        while (3 == 3) {
            video >> img;
            resize(img, img, Size(), 0.7, 0.7);
            Procesamiento procesamiento("");
            gris = procesamiento.to_gris(img);
            Procesamiento procesamiento_sal("Sal", gris, val_sal, false);


            Mat sal = procesamiento_sal.sal_o_pimineta();
            Procesamiento procesamiento_pim("Pimienta", gris, val_pim, true);
            Mat pim = procesamiento_pim.sal_o_pimineta();


            Mat media = procesamiento.median_brur(gris,val_med);

            createTrackbar("Sal", "Original", &val_sal, 100, functionTrackbar);
            createTrackbar("Pimienta", "Original", &val_pim, 100, functionTrackbar);
            createTrackbar("MedianBLur", "Original", &val_med, 100, functionTrackbar);

            imshow("Original", img);
            imshow("Gris", gris);
            imshow("Sal", sal);
            imshow("Pimineta", pim);
            imshow("MedianBlur", media);
            if (waitKey(23) == 27)
                break;


        }
        destroyAllWindows();
    }
    Mat img = imread("../colors.jpg");

    return 0;
}


