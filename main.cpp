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
    vector<string> res_v = persona.split("Hola;hola1;hola2;hola3", ';');
    for (auto &i : res_v)
        cout << i << endl;
    persona.escribirArchivo();
    res_v = persona.leerArchivo();
    persona.leerarchivos();
//    for (auto &i : res_v)
//        cout << i << endl;
    Mat img=imread("../img.jpg");
    cout << img.cols << endl;
    if (img.empty()) {
        cout << "Error" << endl;
        return -1;
    }
    imshow("Solo va el nombre", img);
    waitKey(20000);
    return 0;
}