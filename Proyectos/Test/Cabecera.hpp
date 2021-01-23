

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <fstream>
#include <cmath>
#include <dirent.h>

using namespace std;

#include <cstring>

class Persona {
private:
    string cedula;
public:
    string nombres;
    string apellidos;
    double edad;

    void fibonacci(int = 137);

    void saludar();

    bool validarCedula(string = "0105452172");
    vector<string> split(string, char=';');

    bool escribirArchivo(string="prueba.txt");

    vector<string> leerArchivo(string="prueba.txt");
    void leerarchivos(string=".");
    Persona(string, string, string);
    ~Persona();
};

