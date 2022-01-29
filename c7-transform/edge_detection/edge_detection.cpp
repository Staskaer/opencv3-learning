/*
 * 学习使用canny/sobel/laplacian算子和scharr滤波器进行边缘检测
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void canny_edge();     //canny算子使用
void sobel_edge();     //sobel算子使用
void laplacian_edge(); //laplacian算子使用
void scharr_filter();  //scharr滤波器的使用

int main()
{
    scharr_filter();
}

void canny_edge()
{
    //使用canny算子检测边缘
    Mat img = imread("lena.jpg", IMREAD_COLOR), gray, mask, dst;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    blur(gray, mask, Size(3, 3));
    Canny(mask, mask, 3, 9, 3);
    /*
     * canny只能用于灰度图，且应经过滤波
    */
    img.copyTo(dst, mask);
    //copyTo能在copy时使用掩模
    imshow("img", dst);
    waitKey(-1);
}

void sobel_edge()
{
    /*
     * sobel算子是一种用于检测边缘的离散算子
     * 在图像的x，y方向上分别求导（即将图像和基数大小的核做卷积）
     * 然后将导数合并
    */

    Mat img = imread("lena.jpg", IMREAD_COLOR), grad_x, grad_y, dst;
    Mat abs_grad_x, abs_grad_y;
    Sobel(img, grad_x, CV_16S, 1, 0);
    /*
     * 此算法可以用来计算x,y方向上的导数
     * 前两个参数是输出输出
     * 第三个参数是深度，一般有以下对应关系
     * CV_8U --->-1/CV_16S/CV_32F/CV_64F
     * CV_16U/CV_16S --->-1/CV_32F/CV_64F
     * CV_32F --->-1/CV_32F/CV_64F
     * CV_64F --->-1/CV_64F
     * 第四、五个参数是dx、dy，即x、y方向上的导数阶数
     * 第六个参数是核尺寸为1、3、5、7中一个
     * 第七个参数是缩放因子，一般不缩放
     * 第八个参数是delta值，是存放在dst之前会使用到
     * 第九个参数是边界，不管
     * 
     * 一般都用ksize*ksize来作为核尺寸，除了ksize=1时，此时是1*3的矩阵，且不进行高斯模糊
     * 一般用dx=1、dy=0来计算x方向上导数；dx=0、dy=1来计算y方向上的导数
    */
    Sobel(img, grad_y, CV_16S, 0, 1);
    convertScaleAbs(grad_x, abs_grad_x);
    convertScaleAbs(grad_y, abs_grad_y);

    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
    imshow("raw", img);
    imshow("x", abs_grad_x);
    imshow("y", abs_grad_y);
    imshow("dst", dst);
    waitKey(-1);
}

void laplacian_edge()
{
    /*
     * laplacian算子定义：laplace(f) = d2f/dx2 + d2f/dy2
     * 由于使用了图像梯度，所以内部是用sobel实现的
    */

    Mat img = imread("lena.jpg", IMREAD_COLOR), gray, dst, absdst;
    GaussianBlur(img, gray, Size(3, 3), 0, 0);

    cvtColor(gray, gray, COLOR_BGR2GRAY);

    Laplacian(gray, dst, CV_16S, 3, 1, 0);
    /*
     * 前两个参数是输入输出
     * 第三个参数是输出的深度（与上面的对应关系相同）
     * 第四个参数是ksize，用于计算二阶导滤波器的尺寸
     * 第五个参数是scale，可选的比例因子
     * 第六个参数是delta，在存入dst之前使用
     * 第七个参数是边界类型
    */

    convertScaleAbs(dst, absdst);
    //获取绝对值，并将结果转换成8位

    imshow("dst", absdst);
    waitKey(-1);
}

void scharr_filter()
{
    Mat img = imread("lena.jpg", IMREAD_COLOR), dst;
    Mat grad_x, grad_y, abs_grad_x, abs_grad_y;

    Scharr(img, grad_x, CV_16S, 1, 0, 1, 0); //x方向导数
    /*
     * 前两个是输入输出，第三个是深度
     * 第四个参数是x方向上的导数阶数
     * 第五个是y方向上导数阶数
     * 第六个是缩放因子
     * 第七个是delta值
     * 第八个事边界
     */
    convertScaleAbs(grad_x, abs_grad_x);

    Scharr(img, grad_y, CV_16S, 0, 1, 1, 0); //y方向导数
    convertScaleAbs(grad_y, abs_grad_y);

    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);

    imshow("x", abs_grad_x);
    imshow("y", abs_grad_y);
    imshow("dst", dst);
    waitKey(-1);
}