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
    this->TOTAL = this->FRAME(rect).clone();
}

void Procesamiento::cortarzonainteres() {
    Rect rect = boundingRect(this->pointRect);
    this->ROI = this->FRAME(rect).clone();
    this->TOTAL = this->FRAME(rect).clone();
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

void Procesamiento::unirRecorte() {
    for (int y = 0; y < this->TOTAL.rows; y++) {
        for (int x = 0; x < this->TOTAL.cols; x++) {
            if (this->PROCESADA.at<Vec3b>(y, x) == Vec3b(255, 255, 255)) {
                this->TOTAL.at<Vec3b>(y, x) = this->RESTA.at<Vec3b>(y, x);
            }else{
                this->TOTAL.at<Vec3b>(y, x) = this->VIDEO.at<Vec3b>(y, x);
            }
        }
    }
}



