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
    /*
     * 寻找轮廓的函数
     * 第一个参数是输入，要是二值化的灰度图像
     * 第二个参数是轮廓，每个轮廓是一个点向量（vector<vector<Point>>类型）
     * 第三个参数是可选的输出参数，是轮廓的拓扑结构，是一个四元组
     * 其中hierarchy[i][0-3]分别对应后一个、前一个、父、内嵌轮廓
     * 第四个参数是轮廓检索模式
     * RETR_EXTERNAL -- 只检测最外层轮，且hierarchy[i][2-3]为-1
     * RETR_LIST -- 提取所有轮廓，并放在list中，但不建立等级关系
     * RETR_CCOMP -- 提取所有轮廓，并将其组织结构为双层结构（外层为边界，内层为孔）
     * RETR_TREE -- 提取所有轮廓，并建立网状结构
     * 第五个参数是轮廓近似方法
     * CHAIN_APPROX_SIMPLE -- 压缩水平、垂直、对角线方向，只保留方向终点坐标
     * CHAIN_APPROX_NONE -- 提取轮廓每个像素，相邻两点像素差不超过1
     * CHAIN_APPROX_TC89_L1、CHAIN_APPROX_TC89_KCOS -- 链逼近算法
     * 第六个参数是每个轮廓点偏移值，当在roi中提取轮廓并在整个图像中分析时用到
    */

    Mat drawing = Mat::zeros(dst.size(), CV_8UC3);

    for (int i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
        /*
         * 第一个参数是输出
         * 第二个参数是全部轮廓的集合
         * 第三个参数是绘制的轮廓，当为负值时绘制所有轮廓
         * 第四个参数是轮廓颜色
         * 第五个参数是粗细
         * 第六个参数是线的类型
         * 8/4 -- 8/4连通线
         * LINE_AA -- 抗锯齿线
         * 第七个参数时拓扑结构
         * 第八个参数时绘制的轮廓最大等级
         * 第九个参数时点偏移值
        */
    }
    imshow("img", drawing);
}