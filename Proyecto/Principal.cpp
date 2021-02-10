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
        namedWindow("Frame", WINDOW_AUTOSIZE);
        namedWindow("BG", WINDOW_AUTOSIZE);
        namedWindow("ROI", WINDOW_AUTOSIZE);
        namedWindow("ROI_GRAY", WINDOW_AUTOSIZE);
        namedWindow("RESTA", WINDOW_AUTOSIZE);
        namedWindow("TH", WINDOW_AUTOSIZE);

        Mat bg;
        Mat ROI;
        Mat grayROI;
        Mat bgROI;
        Mat roi_bg;
        Mat frame;
        Mat dif;
        Mat th;
        vector<vector<Point> > contours;
        RNG rng(12345);

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
                threshold(dif,th,30,255,THRESH_BINARY);
                medianBlur(th, th, 7);
                findContours(th,contours,RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
                Mat drawing = Mat::zeros( ROI.size(), CV_8UC3 );
                for( size_t i = 0; i< contours.size(); i++ )
                {
                    Scalar color = Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
                    drawContours( drawing, contours, (int)i, color, 2, LINE_8 );
                }
                imshow( "Contours", drawing );
                imshow("ROI", ROI);
                imshow("ROI_GRAY", grayROI);
                imshow("RESTA", dif);
                imshow("TH", th);
            }


            imshow("Frame", frame);

            if (waitKey(23) == 97) {
                cvtColor(frame, bg, COLOR_BGR2GRAY);
                roi_bg = bg(rect).clone();
            }

            if (waitKey(23) == 27)
                break;
        }

        destroyAllWindows();
    }

    return 0;
}
