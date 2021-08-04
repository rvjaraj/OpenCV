#include "Procesamiento.h"

Procesamiento procesamiento("Proyecto Interciclo");

void functionTrackbar(int v, void *p) {
}

int val_dil = 3;
int val_thre = 30;

int main(int argc, char *argv[]) {
    Mat frame;
    VideoCapture camera(0);
    VideoCapture video("../video.mp4");
    namedWindow("Frame", WINDOW_AUTOSIZE);
    namedWindow("FONDO GRAY", WINDOW_AUTOSIZE);
    namedWindow("ROI", WINDOW_AUTOSIZE);
    namedWindow("RESTA", WINDOW_AUTOSIZE);
    namedWindow("PROCESADA", WINDOW_AUTOSIZE);
    namedWindow("VIDEO", WINDOW_AUTOSIZE);

    if (camera.isOpened() and video.isOpened()) {
        while (3 == 3) {
            camera >> frame;
            procesamiento.FRAME = frame;
            video >> frame;
            procesamiento.VIDEO = frame;
            procesamiento.graficarRectangulo();
            if (!procesamiento.FONDO.empty()) {
                procesamiento.cortarzonainteres();
                procesamiento.restarfondo();
                procesamiento.procesarimagen(val_dil, val_thre);
                procesamiento.buscarContornos();
                procesamiento.buscarContornoGrande();
                procesamiento.graficarContorno();
                procesamiento.obetenrMomentos();
                procesamiento.graficarCentro();
                procesamiento.unirRecorte();

                imshow("FONDO GRAY", procesamiento.FONDO);
                imshow("ROI", procesamiento.ROI);
                imshow("RESTA", procesamiento.RESTA);
                imshow("PROCESADA", procesamiento.PROCESADA);
                imshow("VIDEO", procesamiento.VIDEO);
            }
            imshow("Frame", procesamiento.FRAME);
            if (waitKey(12) == 97) {
                procesamiento.cortarzonafondo();
                createTrackbar("Dilatacion", "Frame", &val_dil, 30, functionTrackbar, nullptr);
                createTrackbar("Threshold", "Frame", &val_thre, 100, functionTrackbar, nullptr);
            }
            if (waitKey(12) == 27)
                break;
        }
        destroyAllWindows();
    }
    return 0;
}
