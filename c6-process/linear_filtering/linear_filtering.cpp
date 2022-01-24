/*
* 本文件学习线性滤波，包括低通滤波，高通滤波，带通滤波，带阻滤波等
*其中低通滤波是模糊，高通滤波是锐化

*邻域算子：利用给定像素周围的像素来计算输出结果
*可用于图像局部像素调整和滤波

*opencv中提供了三种常用的滤波函数：
*方框滤波boxblur()
*均值滤波blur()
*高斯滤波GaussianBlur()
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void box_filter(Mat img, Mat dst);    //方框滤波
void blur_(Mat img, Mat dst);         //均值滤波
void gaussian_blur(Mat img, Mat dst); //高斯滤波

int main()
{
    Mat img = imread("lena.jpg", IMREAD_COLOR), dst;
    imshow("raw", img);
    box_filter(img, dst);
    blur_(img, dst);
    gaussian_blur(img, dst);
    waitKey(-1);
}

void box_filter(Mat img, Mat dst)
{
    boxFilter(img, dst, -1, Size(3, 3), Point(-1, -1), false, BORDER_DEFAULT);
    /*
     * 参数说明：前两个是输入和输出矩阵
     * 第三个参数是输出图像深度，-1代表使用原图像深度
     * 第四个参数是内核大小
     * 第五个参数是锚点，代表被平滑的那个点，取负值是中心
     * 第六个参数是是否归一化，归一化时就是均值滤波
     * 第七个参数不用管，代表边界模式
    */
    imshow("box_filter", dst);
}

void blur_(Mat img, Mat dst)
{
    blur(img, dst, Size(5, 5), Point(-1, -1));
    //均值滤波的api基本上与boxfilter的api一致
    //就是归一化时的boxfilter
    imshow("blur", dst);
}
void gaussian_blur(Mat img, Mat dst)
{
    GaussianBlur(img, dst, Size(5, 5), 0, 0);
    /*
     * 参数解析
     * 前两个是输入输出
     * 第三个参数是ksize，必须为正数和奇数，由sigma计算得到
     * 第四第五个参数是在X,Y方向上的偏移值
    */
    imshow("gaussian", dst);
}