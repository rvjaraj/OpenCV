

#include <iostream>
#include <cstdlib>

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

    Persona(string, string, string);
    ~Persona();
};

