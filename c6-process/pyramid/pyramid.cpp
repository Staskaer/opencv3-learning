/*
 * 图像金字塔
 * 图像金字塔是多尺寸表达方式的一种
 * 主要用于图像分割，是一种以多分辨率解释图像的有效结构
 * 金字塔的底部是高分辨率，顶部是低分辨率的近似
 * 有高斯金字塔和拉普拉斯金字塔
 * 前者用于向下采样，后者用于向上采样从低分辨率图像重建
 * 
 * 向上与向下采样是指图像的尺寸，与金字塔方向相反，且两者不是互逆的
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void resize_function();
void pyr_function();

int main()
{
    pyr_function();
}

void resize_function()
{
    Mat img = imread("lena.jpg", IMREAD_COLOR), dst1;

    resize(img, dst1, Size(img.cols * 2, img.rows * 2), 0, 0, INTER_NEAREST);
    /*
     * resize函数是尺寸变换函数
     * 前两个参数是输入输出
     * 第三个是变换的尺寸、
     * 第四第五是x,y轴的伸缩尺寸
     * 第六个参数是插值方式
     * INSERT_NEAREST -- 最邻近插值
     * INSERT_LINEAR --线性插值（默认）
     * INSERT_AREA -- 区域插值
     * INSERT_CUBIC -- 三次样条插值
     * INSERT_LANCZOS4 -- lanczos插值
     * 其中缩小最好用区域插值，放大用三次样条插值（慢）和线性插值（快）
     * 
     * 调用可以resize(img,dst1,Size(purpose))
     * 也可以resize(img,dst1,Size(),fx,fy)
    */
    imshow("result", dst1);
    waitKey(-1);
}

void pyr_function()
{
    Mat img = imread("lena.jpg", IMREAD_COLOR), dst1, dst2;

    pyrUp(img, dst1, Size(img.cols * 2, img.rows * 2));
    /*
     * 向上采样
     * 与resize非常类似
     * 第三个参数是输出图像尺寸
    */
    imshow("dst1", dst1);
    pyrDown(dst1, dst2, Size(img.cols, img.rows));
    /*
     * 向下采样
    */
    imshow("dst2", dst2);
    waitKey(-1);
}