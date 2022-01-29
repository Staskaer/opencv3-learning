/*
* 本文件学习hough变换
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

void hough_line();   //标准hough变换
void hough_line_p(); //累计概率hough变换

int main()
{
    hough_line_p();
}

void hough_line()
{
    Mat img = imread("sudoku.png", IMREAD_COLOR);
    Mat gray, edge;

    cvtColor(img, gray, COLOR_BGR2GRAY);
    Canny(gray, edge, 50, 200, 3); //先灰度后求边缘

    vector<Vec2f> lines; //存放线集合
    HoughLines(edge, lines, 1, CV_PI / 180, 150, 0, 0);
    /*
     * 标准hough变换
     * 第一个参数事二值化的边缘图像
     * 第二个参数事vector数组，存放线集合，每个元素为（rho，theta）格式的线
     * 第三个参数是像素为单位的距离精度rho
     * 第四个参数是以弧度为单位的角度精度theta
     * 第五个参数是累加到平面的阈值参数，即分辨线的最小阈值
     * 第六个参数是多尺度hough变换下的第三个参数rho的除数距离（？）
     * 第七个参数是多尺度hough变换下的第四个参数theta的除数距离
     * 当这两个参数都是0时，表示使用经典hough变换
    */
    for (auto x : lines)
    {
        //lines中每个元素第一个是rho，第二个是theta
        float rho = x[0], theta = x[1];
        Point p1, p2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;

        //以下是几何变换
        p1.x = cvRound(x0 + (-b * 1000));
        p1.y = cvRound(y0 + 1000 * a);
        p2.x = cvRound(x0 - 1000 * (-b));
        p2.y = cvRound(y0 - 1000 * a);

        line(img, p1, p2, Scalar(0, 255, 0), 2);
    }
    imshow("edge", edge);
    imshow("dst", img);
    waitKey(-1);
}

void hough_line_p()
{
    Mat img = imread("sudoku.png", IMREAD_COLOR);
    Mat gray, edge;

    cvtColor(img, gray, COLOR_BGR2GRAY);
    Canny(gray, edge, 50, 200, 3); //先灰度后求边缘

    vector<Vec4i> lines; //存放线集合
    HoughLinesP(edge, lines, 1, CV_PI / 180, 80, 50, 10);
    /*
     * 概率hough变换与标准hough变换不同之处是概率返回的lines结构是4元组，
     * 对应了笛卡尔坐标系下的两点坐标；而标准hough返回极坐标系的rho，theta
     * 
     * 第一个参数是边缘
     * 第二个参数是四元组整形结构，存储线
     * 第三个第四个参数是标准Hough中的参数
     * 第五个参数是累加阈值
     * 第六个参数是线段最低长度
     * 第七个参数是允许将同一行点连接起来的最多数目
     */

    for (auto x : lines)
    {
        Vec4i l = x; //注意类型

        //不需要几何变换
        line(img, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 255, 0), 1);
    }

    imshow("dst", img);
    waitKey(-1);
}