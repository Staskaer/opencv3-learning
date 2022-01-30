/*
 * 直方图均衡化
 * 是通过拉伸像素强度分布来增强图像对比度的一种方法
 * 本质是扩大量化间隔，但量化级别却减少了
 * 因此，原来灰度不同的像素可能变得灰度相同，形成伪轮廓
 * 经过均衡化的图像，频谱更加舒展，有效得利用了0-255范围，对比对增强
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    Mat img = imread("lena.jpg", IMREAD_COLOR), dst;

    cvtColor(img, img, COLOR_BGR2GRAY);
    imshow("img", img);

    equalizeHist(img, dst);
    imshow("dst", dst);
    waitKey(-1);
}