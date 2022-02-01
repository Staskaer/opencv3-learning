/*
 * 学习图像的矩
 * 矩集通常描述了图像的全局特征
 * 并提供了大量的关于该图像不同类型的几何特征信息
 * 可以用于各种图像处理系统中
 * 
 * 矩是一种具有平移旋转尺度不变特征
 * 普通的几何矩是基于原点计算
 * p+q阶普通矩mpq = Σ Σ x^p*y^qf(x,y)  在x,y范围内求和（也就是行列）
 * 零阶矩m00就是面积
 * 一阶矩m01和m10是x，y轴的矩，可以用来确定质心
 * 
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat img, dst, gray;
int thres = 100;
int max_thres = 255;
RNG rng(123456);
Mat canny_out;
vector<Vec4i> hierarchy;
vector<vector<Point>> contours;

void on_thres_change(int, void *);

int main()
{
    system("color 1e");
    img = imread("lena.jpg", IMREAD_COLOR);

    //灰度模糊化
    cvtColor(img, gray, COLOR_BGR2GRAY);
    blur(gray, gray, Size(3, 3));

    namedWindow("img", WINDOW_AUTOSIZE);
    imshow("img", img);

    createTrackbar("thres", "img", &thres, max_thres, on_thres_change);
    on_thres_change(0, 0);

    waitKey(0);
    return 0;
}

void on_thres_change(int, void *)
{
    Canny(gray, canny_out, thres, 2 * thres, 3);

    //寻找边界
    findContours(canny_out, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

    //开始计算矩
    vector<Moments> mu(contours.size());
    for (size_t i = 0; i < contours.size(); i++)
        mu[i] = moments(contours[i], false);
    /*
         * moment函数可以是计算最高三阶的所有矩
         * 第一个参数是轮廓，
        */

    //计算中心矩
    vector<Point2f> mc(contours.size());
    for (size_t i = 0; i < contours.size(); i++)
        mc[i] = Point2f(static_cast<float>(mu[i].m10 / mu[i].m00), static_cast<float>(mu[i].m01 / mu[i].m00));

    //绘制轮廓
    Mat drawing = Mat::zeros(canny_out.size(), CV_8UC3);
    for (size_t i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        drawContours(drawing, contours, i, color, 2, LINE_AA, hierarchy);
        circle(drawing, mc[i], 4, color, -1, LINE_AA, 0);
    }

    namedWindow("dst", WINDOW_AUTOSIZE);
    imshow("dst", drawing);
}