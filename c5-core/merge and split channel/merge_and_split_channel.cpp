/*
*本文件学习通道的颜色分离和图像混合
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;

void split_pic(void); //将图片通道进行分解
void merge_pic(void); //图片通道合并

int main()
{
    merge_pic();
}

void split_pic(void)
{
    vector<Mat> channels;
    Mat B, G, R, pic;

    pic = imread("lena.jpg", IMREAD_COLOR);
    split(pic, channels);
    /*
    *split函数将通道进行分解，其中一般使用vector容器
    *分解后的vector内有通道数个mat对象，按照bgr的顺序排列
    */

    B = channels.at(0);
    G = channels.at(1);
    R = channels.at(2);

    imshow("B", B);
    imshow("G", G);
    imshow("R", R);
    waitKey(-1);
}

void merge_pic(void)
{
    vector<Mat> channels;
    Mat B, G, R, pic;

    pic = imread("lena.jpg", IMREAD_COLOR);
    split(pic, channels);

    B = channels.at(0);
    G = channels.at(1);
    R = channels.at(2);

    addWeighted(B(Rect(100, 100, 300, 300)),
                0.3,
                G(Rect(250, 250, 300, 300)),
                0.4,
                0.0,
                R(Rect(0, 0, 300, 300)));

    merge(channels, pic);
    /*
    *这个函数是将vector容器中的若干通道合并成图像
    *由于mat数组的矩阵体是共有的，故此处直接更改即可
    */

    imshow("pic", pic);
    waitKey(-1);
}
