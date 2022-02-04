/*
 * 本文件学习角点检测中的harris角点检测
 * 图像的特征类型有以下几类：
 * 边缘、角点（感兴趣的点）、斑点（感兴趣的区域）
 * 
 * 其中，如果某一点在任一方向的微小变动都能引起很大的灰度变化，则为角点
 * 角点位于两条边缘的角点，代表了两个边缘变化方向上的点
 * 是精确定位的二维特征
 * 
 * 角点可以有以下几种描述：
 * 一阶导数（灰度梯度）的局部最大对应像素点
 * 两条及两条以上边缘的交点
 * 图像中梯度值和梯度方向的变化速率都很高的点
 * 角点处一阶导最大，二阶导为0，是物体边缘变化不连续的方向
 */

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat img, img_l, gray;
int thres = 30;
constexpr int max_thres = 175;

void on_corner_harris(int, void *);

int main()
{
    img = imread("test.jpg", IMREAD_COLOR);
    img_l = img.clone();

    cvtColor(img_l, gray, COLOR_BGR2GRAY);

    namedWindow("dst", WINDOW_FREERATIO);
    createTrackbar("thres", "dst", &thres, max_thres, on_corner_harris, 0);

    on_corner_harris(0, 0);

    waitKey(-1);
}

void on_corner_harris(int, void *)
{
    Mat dst, norm_img, scale_img; //输出，归一化图像，线性变换后8位无符号图像

    dst = Mat::zeros(img.size(), CV_32FC1);
    img_l = img.clone();

    cornerHarris(gray, dst, 2, 3, 0.04, BORDER_DEFAULT);
    /*
     * harris角点检测函数
     * 运行harris角点检测算子来进行角点检测
     * 第一个参数是输入图像，单通道8位或浮点图像
     * 第二个参数是输出数值，和源图像一样的尺寸和深度
     * 第三个参数是领域大小
     * 第四个参数是sobel算子的孔径大小
     * 第五个参数是harris参数
     * 第六个参数是边界
    */

    normalize(dst, norm_img, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
    convertScaleAbs(norm_img, scale_img); //将归一化图像转化位8位无符号整型

    for (int j = 0; j < norm_img.rows; j++)
        for (int i = 0; i < norm_img.cols; i++)
        {
            if ((int)norm_img.at<float>(j, i) > thres + 80)
            {
                circle(img_l, Point(i, j), 5, Scalar(0, 0, 255), 2, 8, 0);
                circle(scale_img, Point(i, j), 5, Scalar(0, 0, 255), 2, 8, 0);
            }
        }
    imshow("dst", img_l);
    imshow("scale", scale_img);
}