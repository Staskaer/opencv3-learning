/*
* 本文件学习非线性滤波
* 出现散粒的噪声时，高斯滤波不能去除噪声，只能让其变得柔和
* 而中值滤波效果更加优秀
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void media_filter(Mat img, Mat dst);     //中值滤波
void bilateral_filter(Mat img, Mat dst); //双边滤波

int main()
{
    Mat img = imread("lena.jpg", IMREAD_COLOR), dst;
    imshow("raw", img);
    media_filter(img, dst);
    bilateral_filter(img, dst);
    waitKey(-1);
}

void media_filter(Mat img, Mat dst)
{
    //中值滤波是使用像素邻域灰度的中值来代替像素本身
    //能够很好的消除斑点噪声和椒盐噪声
    //但是中值滤波的开销很大，是均值滤波的5倍左右
    //中值滤波对细节较多的图像不合适
    medianBlur(img, dst, 7);
    /*
     * 参数解释：
     * 前两个是输入输出，第三个是卷积核
    */
    imshow("media", dst);
}

void bilateral_filter(Mat img, Mat dst)
{
    //双边滤波同时考虑空域信息和灰度相似度
    //可以做到边缘保存，不像高斯或均值滤波导致模糊
    //但同时，对高频噪声不能很好的去除
    //超，双边滤波可以磨皮
    bilateralFilter(img, dst, 25, 25 * 2, 25 / 2);
    /*
     * 参数解析：
     * 前两个是输入输出
     * 第三个参数是邻域直径，若设置为非负数，则会用第四个参数来计算出
     * 第四个参数是颜色空间滤波器的sigma值，愈大说明领域内约宽广的颜色被混合到一起
     * 第五个参数是坐标空间滤波器的sigma值，越大说明相距越远的像素会相互影响
    */
    imshow("bilatera", dst);
}