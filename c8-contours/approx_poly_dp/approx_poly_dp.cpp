/*
 * 用多边形去逼近轮廓
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat img = imread("templ.png", IMREAD_GRAYSCALE);
    resize(img, img, Size(img.cols * 4, img.rows * 4));
    Mat img2 = Mat::zeros(img.size(), CV_8UC3);

    threshold(img, img, 127, 255, THRESH_BINARY_INV);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    //先找轮廓（灰度图）
    findContours(img, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    //存放多边形逼近的点集
    vector<vector<Point>> contours_poly(contours.size());

    approxPolyDP(Mat(contours[0]), contours_poly[0], 3, true);
    /*
     * 多边形逼近算法
     * 第一个参数是要逼近的轮廓
     * 第二个参数是逼近的结果，也是点集
     * 第三个参数是逼近的精度，即原曲线与逼近曲线的距离之差的最大值
     * 第四个参数是是否封闭，true封闭，否则不封闭
    */
    drawContours(img2, contours_poly, 0, Scalar(0, 0, 255), 3, LINE_AA);

    imshow("img", img2);
    waitKey(-1);
}