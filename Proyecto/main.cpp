#include "Procesamiento.h"

Procesamiento procesamiento("Proyecto Interciclo");

void click_mouse(int event, int x, int y, int flags, void *param) {
    if (event == EVENT_LBUTTONDBLCLK) {
        procesamiento.incio = Point(x, y);
        cout << procesamiento.incio << endl;
    }
    if (event == EVENT_RBUTTONDBLCLK) {
        procesamiento.fin = Point(x, y);
        cout << procesamiento.fin << endl;
    }
}

void functionTrackbar(int v, void *p) {
}

int val_dil = 3;

int main(int argc, char *argv[]) {


    Mat frame;
    VideoCapture video(0);
    namedWindow("Frame", WINDOW_AUTOSIZE);
    namedWindow("FONDO GRAY", WINDOW_AUTOSIZE);
    namedWindow("ROI", WINDOW_AUTOSIZE);
    namedWindow("RESTA", WINDOW_AUTOSIZE);
    namedWindow("PROCESADA", WINDOW_AUTOSIZE);

    if (video.isOpened()) {
        while (3 == 3) {
            video >> frame;
            procesamiento.FRAME = frame;
            procesamiento.graficarRectangulo();
            setMouseCallback("Frame", click_mouse, nullptr);
            if (!procesamiento.FONDO.empty()) {
//                createTrackbar("Dilatacion", "Frame", &val_dil, 30, functionTrackbar, nullptr);

                procesamiento.cortarzonainteres();
                procesamiento.restarfondo();
                procesamiento.procesarimagen(val_dil);
                procesamiento.buscarContornos();
                procesamiento.buscarContornoGrande();
                procesamiento.graficarContorno();
                procesamiento.obetenrMomentos();
                procesamiento.graficarCentro();
                procesamiento.graficarAlto();
                procesamiento.graficarCasco();
                procesamiento.calcularDefectos();
                procesamiento.graficarDefectos();
                procesamiento.contarDedos();

                imshow("FONDO GRAY", procesamiento.FONDO);
                imshow("ROI", procesamiento.ROI);
                imshow("RESTA", procesamiento.RESTA);
                imshow("PROCESADA", procesamiento.PROCESADA);
            }

            imshow("Frame", procesamiento.FRAME);

            if (waitKey(12) == 97) {
                procesamiento.cortarzonafondo();
            }

            if (waitKey(12) == 27)
                break;
        }
        destroyAllWindows();
    }
    return 0;
}
