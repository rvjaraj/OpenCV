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
Point a = Point(342, 225);
Point b = Point(577, 450);
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
        Mat bg;
        Mat frame;
        Mat roi;
        Mat roi_gray;

        namedWindow("Frame", WINDOW_AUTOSIZE);
        namedWindow("BG", WINDOW_AUTOSIZE);
        namedWindow("ROI", WINDOW_AUTOSIZE);
        namedWindow("ROI_GRAY", WINDOW_AUTOSIZE);
        int pixel = 0;

        while (3 == 3) {
            vector<Point> pointsr;
            pointsr.emplace_back(a);
            pointsr.emplace_back(b);
            Rect rect = boundingRect(pointsr);

            video >> frame;
            if (waitKey(23) == 97) {
                cvtColor(frame, bg, COLOR_BGR2GRAY);
                bg = bg(rect).clone();
            }

            if (!bg.empty()) {
                imshow("BG", bg);
            }

            setMouseCallback("Frame", my_mouse_callback, &frame);

            rectangle(frame, a, b, Vec3b(50, 50, 200), 1);


            roi = frame(rect).clone();
            cvtColor(roi, roi_gray, COLOR_BGR2GRAY);

            imshow("Frame", frame);
            imshow("ROI", roi);
            imshow("ROI_GRAY", roi_gray);

            if (waitKey(23) == 27)
                break;
        }

        destroyAllWindows();
    }

    return 0;
}
