/*
*本文件学习离散傅里叶变换
*/

/*========离散傅里叶变换原理
*离散傅里叶变换将图像从时空域转换到频域
*显示转换后的傅里叶图像需要用到幅度图像和相位图像
*由于幅度图像包含大部分需要的信息，可以只保留幅度
*但是想通过逆变换还原，则需要保留两张图像

*变换的目的是把原始图像种亮度变化快和慢的部分分开
（通过将灰度图像矩阵中行列分别看成波的离散数值）
*亮度变化慢则对低频产生贡献，变化快则对高频产生贡献
*/
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void dft_test(void); //使用dft

int main()
{
    Mat pic = imread("lena.jpg", 0);
    namedWindow("raw", 0);
    imshow("raw", pic);

    int m = getOptimalDFTSize(pic.rows);
    //这个函数返回dft的最佳尺寸
    //将行，列分别输入得到dft对应的行列尺寸，可以生成size
    int n = getOptimalDFTSize(pic.cols);

    Mat padd;
    copyMakeBorder(pic, padd, 0, m - pic.rows, 0, n - pic.cols, BORDER_CONSTANT, Scalar::all(0));
    //这个函数扩充图像边界，目的是扩充到最快的尺寸
    //中间4个参数分别代表（top,bottom,left,right）扩充的尺寸
    //第七个参数是边界类型，一般取BORDER_CONSTANT
    //剩下的颜色一般有默认值0

    //为实部虚部分配空间
    //即原来图像上的每个值，dft会产生两个值，而且数值很大要用float存储
    Mat planes[] = {Mat_<float>(padd), Mat::zeros(padd.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI); //将planes合并成多通道数组

    dft(complexI, complexI);

    //再分解回去,将复数转化成幅值
    split(complexI, planes);
    magnitude(planes[0], planes[1], planes[0]);
    //这个函数将前两个复数下坐标转化成幅值
    Mat magnitudePic = planes[0];

    //进行log尺度变换,m = log(1+m)
    magnitudePic += Scalar::all(1);
    log(magnitudePic, magnitudePic);

    //进行裁剪和分割图像
    magnitudePic = magnitudePic(Rect(0, 0, magnitudePic.cols & -2, magnitudePic.rows & -2));

    int cx = magnitudePic.cols / 2;
    int cy = magnitudePic.rows / 2;

    Mat q0(magnitudePic, Rect(0, 0, cx, cy));   //左上
    Mat q1(magnitudePic, Rect(cx, 0, cx, cy));  //右上
    Mat q2(magnitudePic, Rect(0, cy, cx, cy));  //左下
    Mat q3(magnitudePic, Rect(cx, cy, cx, cy)); //右下

    Mat temp; //交换象限
    q0.copyTo(temp);
    q3.copyTo(q0);
    temp.copyTo(q3);

    q1.copyTo(temp);
    q2.copyTo(q1);
    temp.copyTo(q2);

    //归一化
    normalize(magnitudePic, magnitudePic, 0, 1, NORM_MINMAX);

    imshow("dft", magnitudePic);

    waitKey(-1);
}
