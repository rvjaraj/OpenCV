#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
Mat imgThreshold;
Mat catedral;

int umbral = 255;
Point a = Point(300, 13);
Point b = Point(625, 299);
int minH = 0, minS = 0, minV = 11;
int maxH = 25, maxS = 255, maxV = 255;


void trackBarEvent(int v, void *p) {
    threshold(catedral, imgThreshold, umbral, 255, THRESH_BINARY);
    imshow("Threshold", imgThreshold);
}

void trackBarEventHSV(int v, void *p) {
}

void my_mouse_callback(int event, int x, int y, int flags, void *param) {
    if (event == EVENT_LBUTTONDBLCLK) {
        a = Point(x, y);
        cout << a << endl;
    }
    if (event == EVENT_RBUTTONDBLCLK) {
        b = Point(x, y);
        cout << b << endl;
    }
}

int main(int argc, char *argv[]) {


    VideoCapture video(0);
    //VideoCapture video("../video.mp4");

    if (video.isOpened()) {
//        namedWindow("Frame", WINDOW_AUTOSIZE);
//        namedWindow("BG", WINDOW_AUTOSIZE);
//        namedWindow("ROI", WINDOW_AUTOSIZE);
//        namedWindow("ROI_GRAY", WINDOW_AUTOSIZE);
//        namedWindow("RESTA", WINDOW_AUTOSIZE);
//        namedWindow("TH", WINDOW_AUTOSIZE);

        Mat bg;
        Mat ROI;
        Mat grayROI;
        Mat bgROI;
        Mat roi_bg;
        Mat frame;
        Mat dif;
        Mat th;
        vector<vector<Point> > contours;
        vector<vector<Point> > contours1;
        vector<Point> cot;
        RNG rng(12345);
        Moments M;
        int pixel = 0;

        while (3 == 3) {
            vector<Point> pointsr;
            pointsr.emplace_back(a);
            pointsr.emplace_back(b);
            Rect rect = boundingRect(pointsr);

            video >> frame;

            setMouseCallback("Frame", my_mouse_callback, &frame);

            rectangle(frame, a, b, Vec3b(50, 50, 200), 1);


            if (!bg.empty()) {
                imshow("BG", roi_bg);
                ROI = frame(rect).clone();
                cvtColor(ROI, grayROI, COLOR_BGR2GRAY);
                bgROI = bg(rect).clone();
                absdiff(grayROI, bgROI, dif);
                threshold(dif, th, 30, 255, THRESH_BINARY);
                medianBlur(th, th, 7);
                Mat element = getStructuringElement(MORPH_CROSS, //MORPH_RECT [] MORPH_CROSS + MORPH_ELLIPSE O
                                                    Size(2 * 3 + 1, 2 * 3 + 1),
                                                    Point(0, 0));
                dilate(th, th, element);
                findContours(th, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
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
                if (!contours.empty()) {
                    contours1.emplace_back(contours[index]);
                    drawContours(ROI, contours1, -1, (0, 0, 255), 2, LINE_AA);

                }
                for (auto &contour : contours1) {
                    M = moments(contour);
                    if (M.m00 == 0) {
                        M.m00 = 1;
                    }
                    int x = int(M.m10) / M.m00;
                    int y = int(M.m01) / M.m00;
                    circle(ROI, Point(x, y), 5, Vec3b(255, 0, 255), -1);
                    Point yMin = Point(0, 0);
                    yMin.x = x;
                    yMin.y = 99 * 999 * 99;
                    index = -1;

                    for (int i = 0; i < contour.size(); ++i) {
                        if (contour[i].y < yMin.y) {
                            index = i;
                            yMin.y = contour[i].y;
                        }
                    }
                    circle(ROI, yMin, 5, Vec3b(0, 0, 255), -1);
                    vector<vector<Point> > hull(contours1.size());
                    convexHull(contour, hull[0]);
                    drawContours(ROI, hull, 0, Vec3b(100, 100, 100), 2);

                    vector<vector<int> > hull2(contours1.size());
                    convexHull(contour, hull2[0], false, true);
                    vector<vector<Vec4i>> defects(contours1.size());
                    if (hull2[0].size() > 3) {
                        convexityDefects(contour, hull2[0], defects[0]);
                    }
                    vector<Point> inicio;
                    vector<Point> fin;
                    int dedos = 0;
                    for (const Vec4i &v : defects[0]) {
                        float depth = v[3] / 256;
                        if (depth > 10) {
                            int startidx = v[0];
                            Point ptStart(contour[startidx]);
                            int endidx = v[1];
                            Point ptEnd(contour[endidx]);
                            int faridx = v[2];
                            Point ptFar(contour[faridx]);
                            double dis = norm(ptStart - ptEnd);

                            double a = norm(ptFar - ptEnd);
                            double b = norm(ptFar - ptStart);
                            double c = norm(ptStart - ptEnd);

                            double angulo = acos(((pow(a, 2)) + pow(b, 2) - pow(c, 2)) / (2 * a * b));
                            angulo = (angulo) * (180.0 / 3.141592653589793238463);
                            int ang = (int) angulo;

                            if (dis > 10 and v[4] > 50 and ang < 70) {
                                inicio.push_back(ptStart);
                                fin.push_back(ptEnd);

                                putText(ROI, std::to_string(ang), ptFar, 1, 1, Scalar(204, 204, 0), 2, LINE_AA);
                                putText(ROI, std::to_string(dis), ptEnd, 1, 1, Scalar(204, 204, 0), 2, LINE_AA);
                                circle(ROI, ptStart, 5, Scalar(204, 204, 0), 2);
                                circle(ROI, ptEnd, 5, Scalar(204, 0, 204), 2);
                                circle(ROI, ptFar, 7, Scalar(0, 255, 255), -1);

                                line(ROI, ptStart, ptEnd, Scalar(0, 255, 0), 1);
                                line(ROI, ptStart, ptFar, Scalar(0, 255, 0), 1);
                                line(ROI, ptEnd, ptFar, Scalar(0, 255, 0), 1);
                            }
                        }
                    }
                    if (inicio.empty() and norm(yMin - Point(x, y)) > 85) {
                        putText(frame, "UN DEDO", a, 1, 4,
                                Scalar(250, 150, 250), 3, LINE_AA);
                    }
                    if (inicio.size() == 1) {
                        putText(frame, "DOS DEDOS", a, 1, 4,
                                Scalar(250, 150, 250), 2, LINE_AA);
                    }
                    if (inicio.size() == 2) {
                        putText(frame, "TRES DEDOS", a, 1, 4,
                                Scalar(250, 150, 250), 2, LINE_AA);
                    }
                    if (inicio.size() == 3) {
                        putText(frame, "CUATRO DEDOS", a, 1, 4,
                                Scalar(250, 150, 250), 2, LINE_AA);
                    }
                    if (inicio.size() == 4) {
                        putText(frame, "CINCO DEDOS", a, 1, 4,
                                Scalar(250, 150, 250), 2, LINE_AA);
                    }

                }
                contours1.clear();
                imshow("ROI", ROI);
                imshow("ROI_GRAY", grayROI);
                imshow("RESTA", dif);
                imshow("TH", th);
            }


            imshow("Frame", frame);

            if (waitKey(12) == 97) {
                cvtColor(frame, bg, COLOR_BGR2GRAY);
                roi_bg = bg(rect).clone();
            }

            if (waitKey(12) == 27)
                break;
        }

        destroyAllWindows();
    }

    return 0;
}
