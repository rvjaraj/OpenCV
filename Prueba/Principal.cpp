
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int main(int argc, char *argv[]) {
    Mat orig = imread("../JARA_JARA_RICARDO_VINICIO-1.png");
    Mat img1 = imread("../JARA_JARA_RICARDO_VINICIO-1.png");
    Mat img2 = imread("../JARA_JARA_RICARDO_VINICIO-2.png");

    Mat rest = Mat::zeros(img1.size(), CV_8UC3);

    namedWindow("Original", WINDOW_AUTOSIZE);
    namedWindow("IMG1", WINDOW_AUTOSIZE);
    namedWindow("IMG2", WINDOW_AUTOSIZE);
    namedWindow("IMG3", WINDOW_AUTOSIZE);

    //JARA_JARA_RICARDO_VINICIO{cx = 108 cy = 150 radio = 16}

    circle(img1, Point(108, 150), 16, Vec3b(255, 255, 255), -1);

    for (int y = 0; y < img1.rows; y++) {
        for (int x = 0; x < img1.cols; x++) {
            if (img1.at<Vec3b>(y, x) == Vec3b(255, 255, 255)) {
                rest.at<Vec3b>(y, x) = img2.at<Vec3b>(y, x);
            } else {
                //rest.at<Vec3b>(y, x) = img1.at<Vec3b>(y, x);
            }
        }
    }

    imshow("Original", orig);
    imshow("IMG1", img1);
    imshow("IMG2", img2);
    imshow("IMG3", rest);
    waitKey(0);
    destroyAllWindows();
    return 0;
}

