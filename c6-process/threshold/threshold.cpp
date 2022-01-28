/*
 * 阈值操作
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat img = imread("lena.jpg", IMREAD_GRAYSCALE), dst1, dst2;

    threshold(img, dst1, 127, 255, THRESH_TOZERO);
    /*
     * 阈值函数，前两个是输入输出
     * 第三个参数是阈值，第四个参数是阈值溢出值（跟类型有关）
     * 第五个参数:
     * THRESH_BINARY -- 二值化，大于阈值取阈值溢出值，否则为0
     * THRESH_BINARY_INV -- 反二值化，大于阈值取0，否则为阈值溢出值
     * THRESH_TRUNC -- 大于阈值为阈值溢出值，否则为本身
     * THRESH_TOZERO -- 大于阈值为本身，小于阈值为0
     * THRESH_TOZERO_INV -- 大于阈值为0 小于阈值为本身
    */

    adaptiveThreshold(img, dst2, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 3, 5);
    /*
     * 上面的阈值是全局阈值，此处是自适应阈值
     * 因为同一张图像中不同局部应用不同的阈值更加有效
     * 前两个参数是输入输出
     * 第三个参数是maxValue（后面根据结合参数不同效果不同）
     * 第四个参数是自适应阈值算法类型： ADAPTIVE_THRESH_GAUSSIAN_C或ADAPTIVE_THRESH_MEAN_C
     * 第五个参数只能是THRESH_BINARY或THRESH_BINARY_INV
     * 
     * 第六个参数是计算阈值时的邻域尺寸，为奇数
     * 第七个参数是一个常数，一般为正数，用于做偏置用被减数
     * 
     * 具体步骤：
     * 当第五个参数是THRESH_BINARY时，dst(x,y) = maxValue if(src(x,y)>T(x,y)) else dst(x,y) = 0
     * 当第五个参数是THRESH_BINARY_INV时，dst(x,y) = 0 if(src(x,y)>T(x,y)) else dst(x,y) = maxValue
     * 其中T(x,y)取决于第四个参数设置的自适应算法
     * 当第四个参数为ADAPTIVE_THRESH_MEAN_C时，T(x,y)为(x,y)邻域减去偏置常数再求均值
     * 当第四个参数为ADAPTIVE_THRESH_GAUSSIAN_C时，T(x,y)为(x,y)邻域与减去偏置常数再与高斯核卷积的加权平均
     * 
    */

    imshow("dst2", dst2);
    imshow("threshold", dst1);
    waitKey(-1);
}