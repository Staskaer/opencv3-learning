/*
 * 本文件学习寻找轮廓并绘制
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

Mat img = imread("home.jpg", IMREAD_COLOR), gray, dst;
vector<vector<Point>> contours;
vector<Vec4i> hierarchy;
int thres = 80;
RNG rng(123456);

void on_thres_change(int, void *);

int main(int argc, char *argv[])
{
    namedWindow("img", WINDOW_AUTOSIZE);
    system("color 1f");

    cvtColor(img, gray, COLOR_BGR2GRAY);
    blur(gray, gray, Size(3, 3));

    createTrackbar("thres", "img", &thres, 255, on_thres_change);
    on_thres_change(0, 0);
    waitKey(-1);
}

void on_thres_change(int, void *)
{
    Canny(gray, dst, thres, thres * 2, 3);

    findContours(dst, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

    Mat drawing = Mat::zeros(dst.size(), CV_8UC3);

    for (int i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
    }
    imshow("img", drawing);
}