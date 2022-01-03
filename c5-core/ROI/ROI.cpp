/*
*本文件学习ROI相关操作
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;

void get_roi(void);                     //用两种方法获取ROI
void roi_add(void);                     //用roi覆写源图像指定区域
void linear_add(void);                  //线性混合操作
void bar_callback(int bar, void *temp); //trackbar回调函数

int main()
{
    linear_add();
}

void get_roi(void)
{
    Mat pic = imread("lena.jpg", IMREAD_COLOR);
    //有两种方法获取ROI
    //第一种是使用rect类框出矩形区域
    Mat picRoi = pic(Rect(400, 250, 100, 200));
    imshow("roi", picRoi);
    waitKey(-1);

    //也可以使用Range类划分出范围，先行后列
    picRoi = pic(Range(250, 450), Range(400, 500));
    imshow("roi", picRoi);
    waitKey(-1);
}

void roi_add(void)
{
    //将roi区域覆写源图像的指定区域

    Mat pic_raw = imread("lena.jpg", IMREAD_COLOR);
    Mat pic_roi = pic_raw(Rect(0, 0, 200, 200));

    Mat mask; //自身灰度掩模，此处没用到
    cvtColor(pic_roi, mask, COLOR_BGR2GRAY);

    pic_roi.copyTo(pic_raw(Rect(200, 200, 200, 200)));
    //copyto函数将self复制到指定区域
    //有一个带掩模的重载，传入自身的灰度掩模，可以将空白区域保留源图像

    imshow("result", pic_raw);
    waitKey(-1);
}

void linear_add(void)
{
    //线性混合使用addweighted函数，之前讲过
    //要求同尺寸的两张图按照指定参数混合

    Mat pic1 = imread("left.jpg", IMREAD_COLOR), pic2 = imread("right.jpg", IMREAD_COLOR), dst;
    vector<Mat *> tup = {&pic1, &pic2, &dst};

    int alpha = 70;
    namedWindow("addweighted", WINDOW_NORMAL);
    createTrackbar("bar", "addweighted", &alpha, 100, bar_callback, tup.data());

    waitKey(-1);
}

void bar_callback(int bar, void *temp)
{
    double alpha_value, beta_value;
    alpha_value = double(bar) / 100;
    beta_value = 1.0 - alpha_value;

    Mat pic1 = *((Mat **)temp)[0], pic2 = *((Mat **)temp)[1], dst = *((Mat **)temp)[2];
    addWeighted(pic1, alpha_value, pic2, beta_value, 0.0, dst);
    imshow("addweighted", dst);
}