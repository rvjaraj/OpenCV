#include "Procesamiento.h"

int val_pim = 10;
int val_sal = 10;
int val_med = 10;
int val_gau = 10;
int umbral = 70;
int radio = 3;

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
        namedWindow("Sovel GX - GY", WINDOW_AUTOSIZE);
        namedWindow("Canny", WINDOW_AUTOSIZE);
        while (3 == 3) {
            video >> img;
            resize(img, img, Size(), 0.8, 0.8);
            //Iniciamos clase
            Procesamiento procesamiento("");
            //Convertmos imaagen a gris
            gris = procesamiento.to_gris(img);
            //metodo con false para sal
            Mat sal = procesamiento.sal_o_pimineta(gris, val_sal, false);
            //metodo con true para pimienta
            Mat pim = procesamiento.sal_o_pimineta(gris, val_pim, true);
            //metodo de medain blue
            Mat media = procesamiento.median_brur(gris, val_med);
            //Metodo de gaunciablur
            Mat gausi = procesamiento.gaussian_blur(gris, val_gau);
            //Usamos suavizado medianblur para una mejor detecion de bordes
            //bordes Sobel de x y y
            Mat gxgy = procesamiento.gxgy(media);
            //bordes con canny
            Mat can = procesamiento.canny(media, umbral, radio);

            imshow("Original", img);
            //agregamos las barras de estado
            createTrackbar("Sal", "Original", &val_sal, 100, functionTrackbar, nullptr);
            createTrackbar("Pimiento", "Original", &val_pim, 100, functionTrackbar, nullptr);
            createTrackbar("MedianBLur", "Original", &val_med, 100, functionTrackbar, nullptr);
            createTrackbar("Gaussian Blur", "Original", &val_gau, 100, functionTrackbar, nullptr);
            createTrackbar("Umbral", "Original", &umbral, 100, functionTrackbar, nullptr);
            createTrackbar("Radio", "Original", &radio, 100, functionTrackbar, nullptr);

            imshow("Gris", gris);
            imshow("Sal", sal);
            imshow("Pimiento", pim);
            imshow("MedianBlur", media);
            imshow("Gaussian Blur", gausi);
            imshow("Sovel GX - GY", gxgy);
            imshow("Canny", can);
            if (waitKey(23) == 27)
                break;


        }
        destroyAllWindows();
    }
    Mat img = imread("../colors.jpg");

    return 0;
}


