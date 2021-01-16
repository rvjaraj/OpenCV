#include "iostream"
#include "opencv2/opencv.hpp"
#include "Cabecera.hpp"

using namespace std;
using namespace cv;

int main(int arcg, char *argv[]) {
    Persona persona("Ricardo", "Jara", "0105452171");
    persona.saludar();
    persona.fibonacci();
    bool res = persona.validarCedula();
    cout << "Cedula: " << res << endl;
//    Mat img=imread("../img.jpg");
//    cout << img.cols << endl;
//    if (img.empty()) {
//        cout << "Error" << endl;
//        return -1;
//    }
//    imshow("img.jpg", img);
//    waitKey(20000);
    return 0;
}