/*
 * 本文件学习如何使用多边形将图像包围
 * 有用不同的形状去拟合二维点集的函数
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void bound_rect(Mat points, Mat &img);   //用矩形去拟合
void bound_rect_r(Mat points, Mat &img); //用旋转的矩形去拟合
void min_circle(Mat points, Mat &img);   //用圆去拟合
void fit_ellipse(Mat points, Mat &img);  //用椭圆去拟合

void on_do(int type, void *);

int main()
{

    RNG &rng = theRNG();
    //是线程安全的一个方法
    Mat img(600, 600, CV_8UC3);
    vector<Mat *> data = {&img};
    namedWindow("img");
    int type = 0;
    createTrackbar("type", "img", &type, 3, on_do, data.data());
    //创建滑条

    while (1)
    {
        //先初始化点
        char key;
        int count = (unsigned)rng % 100 + 10;
        vector<Point> points;

        for (int i = 0; i < count; i++)
        {
            Point point;
            point.x = rng.uniform(img.cols / 4, img.cols / 4 * 3);
            point.y = rng.uniform(img.rows / 4, img.rows / 4 * 3);

            points.push_back(point);
        }

        //绘制点
        img = Scalar::all(0);
        for (auto point : points)
            circle(img, point, 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), FILLED, LINE_AA);

        //显示调用回调函数
        Mat p = (Mat)points;
        data[1] = &p;
        on_do(type, data.data());

        key = waitKey();
        if (key == 27)
            break;
    }
}

void bound_rect(Mat points, Mat &img)
{
    Rect rect = boundingRect(points);
    /*
     * 此函数时寻找最小包围的矩形的函数
     * 仅有一个输入，为点集，可以是mat或vector
    */

    rectangle(img, rect, Scalar(123, 42, 84), 2);
    imshow("img", img);
}

void bound_rect_r(Mat points, Mat &img)
{

    RotatedRect rect = minAreaRect(points);
    /*
     * 同样只有一个输入点集
     * 但要求如果是mat数组只能是两列
    */

    Point2f vex[4];
    rect.points(vex);

    for (int i = 0; i < 4; i++)
    {
        line(img, vex[i], vex[(i + 1) % 4], Scalar(123, 31, 186), 2, LINE_AA);
    }
    imshow("img", img);
}

void min_circle(Mat points, Mat &img)
{
    Point2f center;
    float r;
    minEnclosingCircle(points, center, r);
    /*
     * 寻找最小圆
     * 输入、圆心、半径
    */

    circle(img, center, r, Scalar(123, 54, 185), 2, LINE_AA);
    imshow("img", img);
}

void fit_ellipse(Mat points, Mat &img)
{
    RotatedRect box = fitEllipse(points);
    /*
     * 用椭圆拟合
    */
    ellipse(img, box, Scalar(54, 74, 63));
    imshow("img", img);
}

void on_do(int type, void *meta)
{
    Mat img = *((Mat **)meta)[0], points = *((Mat **)meta)[1];
    switch (type)
    {
    case 0:
        bound_rect(points, img);
        break;
    case 1:
        bound_rect_r(points, img);
        break;
    case 2:
        min_circle(points, img);
        break;
    case 3:
        fit_ellipse(points, img);
        break;
    }
}