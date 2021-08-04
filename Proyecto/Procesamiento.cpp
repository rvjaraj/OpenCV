//
// Created by vinic on 1/24/2021.
//

#include "Procesamiento.h"


Procesamiento::Procesamiento(string name) {
    this->name = name;
    cout << this->name << endl;
}

void Procesamiento::graficarRectangulo() {
    rectangle(this->FRAME, this->incio, this->fin, Vec3b(50, 50, 200), 1);
}

void Procesamiento::cortarzonafondo() {
    this->pointRect.clear();
    this->pointRect.emplace_back(this->incio);
    this->pointRect.emplace_back(this->fin);
    Rect rect = boundingRect(this->pointRect);
    cvtColor(this->FRAME, this->FONDO, COLOR_BGR2GRAY);
    this->FONDO = this->FONDO(rect).clone();
    this->ROI = this->FRAME(rect).clone();
}

void Procesamiento::cortarzonainteres() {
    Rect rect = boundingRect(this->pointRect);
    this->ROI = this->FRAME(rect).clone();
}

void Procesamiento::restarfondo() {
    cvtColor(ROI, this->ROI_GRAY, COLOR_BGR2GRAY);
    absdiff(this->ROI_GRAY, this->FONDO, this->RESTA);
}

void Procesamiento::procesarimagen(int val_dil) {
    threshold(this->RESTA, this->PROCESADA, 30, 255, THRESH_BINARY);
    medianBlur(this->PROCESADA, this->PROCESADA, 7);
    Mat element = getStructuringElement(MORPH_CROSS, //MORPH_RECT [] MORPH_CROSS + MORPH_ELLIPSE O
                                        Size(2 * val_dil + 1, 2 * val_dil + 1),
                                        Point(0, 0));
    dilate(this->PROCESADA, this->PROCESADA, element);
}

void Procesamiento::buscarContornos() {
    findContours(this->PROCESADA, this->contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
}

void Procesamiento::buscarContornoGrande() {
    if (!this->contours.empty()) {
        vector<vector<Point> > contoursAux;
        vector<Point> contorsPly;
        double maxArea = 0.0;
        int index = 0;
        for (int i = 0; i < contours.size(); ++i) {
            approxPolyDP(Mat(contours[i]), contorsPly, 3, true);
            double corruArea = contourArea(contorsPly);
            if (corruArea > maxArea) {
                index = i;
                maxArea = corruArea;
            }
        }
        contoursAux.emplace_back(contours[index]);
        this->contours = contoursAux;
    }
}

void Procesamiento::graficarContorno() {
    if (!this->contours.empty()) {
        drawContours(this->ROI, this->contours, -1, Vec3b(100, 0, 255), 2, LINE_AA);
    }
}

void Procesamiento::obetenrMomentos() {
    for (auto &contour : this->contours) {
        this->momentos = moments(contour);
    }
}

void Procesamiento::graficarCentro() {
    if (this->momentos.m00 == 0) {
        this->momentos.m00 = 1;
    }
    this->centro.x = int(this->momentos.m10) / this->momentos.m00;
    this->centro.y = int(this->momentos.m01) / this->momentos.m00;
    circle(this->ROI, centro, 5, Vec3b(255, 0, 255), -1);

}



void Procesamiento::guardarMomentos(int val_save) {
    double huMoments[7];
    Moments momentos = moments(this->PROCESADA, true);
    HuMoments(momentos, huMoments);
    cout << "Gesto: " << val_save << endl;
    for (int i = 0; i < 7; i++)
        cout << huMoments[i] << ",";
    cout << endl;
    switch (val_save) {
        case 0 :
            HuMoments(momentos, this->huGesto0);
            break;
        case 1 :
            HuMoments(momentos, this->huGesto1);
            break;
        case 2 :
            HuMoments(momentos, this->huGesto2);
            break;
        case 3 :
            HuMoments(momentos, this->huGesto3);
            break;
        case 4 :
            HuMoments(momentos, this->huGesto4);
            break;
        case 5 :
            HuMoments(momentos, this->huGesto5);
            break;
    }
}

double distancia(double m1[7], double m2[7]) {
    double suma = 0.0;
    for (int i = 0; i < 7; i++) {
        suma += (m1[i] - m2[i]) * (m1[i] - m2[i]);
    }
    suma = sqrt(suma);
    return suma;
}

void Procesamiento::detectarMomento(int val_save) {
    if (val_save > 0) {
        double huMoments[7];
        Moments momentos = moments(this->PROCESADA, true);
        HuMoments(momentos, huMoments);
        double dist = 99 * 99 * 99;
        double aux = 99 * 99 * 99;
        int gest = -1;
        for (int i = 0; i < 6; ++i) {
            switch (i) {
                case 0 :
                    aux = distancia(huMoments, this->huGesto0);
                    if (aux < dist) {
                        dist = aux;
                        gest = dist < 0.03 ? 0 : gest;
                    }
                    break;
                case 1 :
                    aux = distancia(huMoments, this->huGesto1);
                    if (aux < dist) {
                        dist = aux;
                        gest = dist < 0.03 ? 1 : gest;
                    }
                    break;
                case 2 :
                    aux = distancia(huMoments, this->huGesto2);
                    if (aux < dist) {
                        dist = aux;
                        gest = dist < 0.03 ? 2 : gest;
                    }
                    break;
                case 3 :
                    aux = distancia(huMoments, this->huGesto3);
                    if (aux < dist) {
                        dist = aux;
                        gest = dist < 0.03 ? 3 : gest;
                    }
                    break;
                case 4 :
                    aux = distancia(huMoments, this->huGesto4);
                    if (aux < dist) {
                        dist = aux;
                        gest = dist < 0.03 ? 4 : gest;
                    }
                    break;
                case 5 :
                    aux = distancia(huMoments, this->huGesto5);
                    if (aux < dist) {
                        dist = aux;
                        gest = dist < 0.03 ? 5 : gest;
                    }
                    break;
            }
        }

        //cout << "Distancia: " << dist << endl;

        int cx = momentos.m10 / momentos.m00;
        int cy = momentos.m01 / momentos.m00;
        circle(this->ROI, Point(cx, cy), 7, Scalar(10, 10, 203), 3);
        putText(this->FRAME, "GESTO " + std::to_string(gest), incio, FONT_ITALIC, 2,
                Scalar(250, 150, 250), 2, LINE_AA);
    }
}
