/*
*本文件学习形态学滤波的基本功能
*形态学操作是基于形状进行变化的图像处理。

*此处涉及膨胀和腐蚀
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat img = imread("lena.jpg", IMREAD_COLOR), dst1, dst2;

    //膨胀
    /*
    膨胀就是求局部最大值，将区域与卷积核做乘积运算
    然后将运算的最大值赋值给锚点
    是将高亮区域扩张
    */

    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15), Point(-1, -1));
    /*
    这个函数能够返回指定形状核尺寸的内核矩阵，配合膨胀核腐蚀来使用
    其中第一个参数可以是：MORPH_RECT，MORPH_CROSS,MORPH_ELLIPSE
    分别是矩形，交叉形，椭圆

    除了十字形依赖锚点来确定形状外，其余锚点只是影响形态学运算的结果偏移
    */
    dilate(img, dst1, element);
    /*
     * 前两个参数是输入输出
     * 第三个参数是核矩阵
     * 第四个参数是锚点
     * 第五个参数是迭代次数
     * 第六、七个参数是边界相关参数，一般不管
    */

    //腐蚀
    /*
    腐蚀是膨胀的反变化，将最小值赋值给锚点
    将高亮区域缩减
    */
    erode(img, dst2, element);
    /*
     * 与dilate参数基本类似
     * 一般只考虑前三个参数，且与getStructuringElement配合使用
    */

    imshow("raw", img);
    imshow("dilate", dst1);
    imshow("erode", dst2);
    waitKey(-1);
}