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
    suma = suma%10;
    resta = (digito ==0)?suma:10-suma;
    return (resta==digito);
}

Persona::~Persona() {
    //cout << " Destructor";
}