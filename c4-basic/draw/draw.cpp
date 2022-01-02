/*
*本文件学习基本绘制图形的操作
*包括直线，椭圆，圆，矩形和填充多边形
*/

#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

constexpr int WINDOW_WIDTH = 720;

void draw_ellipse(Mat &pic, double angle);        //学习绘制椭圆
void draw_filled_circle(Mat &pic, Point center);  //学习绘制封闭区域上色
void draw_line(Mat &pic, Point start, Point end); //绘制直线

int main(int argc, char *argv[])
{
    Mat pic(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
    draw_line(pic, Point(WINDOW_WIDTH / 16, WINDOW_WIDTH / 16), Point(WINDOW_WIDTH / 4, WINDOW_WIDTH / 4));
    imshow("pic", pic);
    waitKey(-1);
}

void draw_ellipse(Mat &pic, double angle)
{

    ellipse(pic,
            Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2),
            Size(WINDOW_WIDTH / 4, WINDOW_WIDTH / 16),
            angle,
            0,
            360,
            Scalar(0, 222, 123),
            2,
            LINE_8);
    //绘制椭圆函数解析
    /*
    *第一个参数是输出图像
    *第二个参数是椭圆中心点坐标
    *第三个参数限制了椭圆的大小，位于此矩形内（y，x)
    *第四个是椭圆旋转角度0-360
    *第五个参数是绘制的弧的起始角度0-360
    *第六个参数是绘制的弧的结束角度0-360
    *第七个颜色，第八个线宽，第九个线型
    */
}

void draw_filled_circle(Mat &pic, Point center)
{
    circle(
        pic,
        center,
        WINDOW_WIDTH / 32,
        Scalar(0, 255, 0),
        -1,
        LINE_8);
    /*
    *参数说明
    *第一个参数是图像
    *第二个参数是原中心
    *第三个参数是半径
    *剩下为颜色粗细线型
    *当线宽为-1时是实心
    */
}

void draw_line(Mat &pic, Point start, Point end)
{
    line(
        pic,
        start,
        end,
        Scalar::all(255),
        2,
        LINE_8);
}