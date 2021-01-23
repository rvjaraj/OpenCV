//
// Created by vinic on 1/15/2021.
//

#include "Cabecera.hpp"

Persona::Persona(string n, string a, string c) {
    this->nombres = n;
    this->apellidos = a;
    this->cedula = c;

}

void Persona::saludar() {
    cout << "Hola: " << nombres << " " << apellidos << " " << endl;

}

void Persona::fibonacci(int limite) {
    int a = 0;
    int b = 1;
    int c = a + b;
    cout << "a:" << a << " b: " << b << " c: " << c;
    while (c <= limite) {
        a = b;
        b = c;
        c = a + b;
        cout << "," << c;
    }
    cout << endl;
}

bool Persona::validarCedula(string ced) {
    int digito = -1;
    int suma = 0;
    int resta = -1;
    for (int i = 0; i < ced.length(); ++i) {
        digito = ced.at(i) - 48;
        if (i % 2 == 0)
            digito = (digito * 2) > 9 ? (digito * 2) - 9 : digito * 2;
        if (i < ced.size() - 1)
            suma += digito;

    }
    suma = suma % 10;
    resta = (digito == 0) ? suma : 10 - suma;
    return (resta == digito);
}

vector<string> Persona::split(string cad, char sep) {
    stringstream ss;
    ss << cad;
    vector<string> datos;
    string token;
    while ((getline(ss, token, sep))) {
        datos.push_back(token);
    }
    return datos;
}

bool Persona::escribirArchivo(string cad) {
    ofstream archivo(cad, ios::out);
    for (double i = 0; i < M_PI; i += 0.1) {
        archivo << "Valor: " << cos(i) << endl;
    }
    archivo.close();
    return true;
}

vector<string> Persona::leerArchivo(string cad) {
    ifstream archivo(cad, ios::in);
    string liena;
    vector<string> datos;
    while ((getline(archivo, liena, '\n'))) {
        datos.push_back(liena);
    }
    return datos;
}

void Persona::leerarchivos(string path) {
    DIR *pDIR = opendir(path.c_str());
    struct dirent *entry;

    while ((entry = readdir(pDIR)) != NULL) {
        cout << entry->d_name << endl;
    }
    closedir(pDIR);
}

Persona::~Persona() {
    //cout << " Destructor";
}