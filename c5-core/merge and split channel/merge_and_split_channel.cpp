/*
*���ļ�ѧϰͨ������ɫ�����ͼ����
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;

void split_pic(void); //��ͼƬͨ�����зֽ�
void merge_pic(void); //ͼƬͨ���ϲ�

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
    *split������ͨ�����зֽ⣬����һ��ʹ��vector����
    *�ֽ���vector����ͨ������mat���󣬰���bgr��˳������
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
    *��������ǽ�vector�����е�����ͨ���ϲ���ͼ��
    *����mat����ľ������ǹ��еģ��ʴ˴�ֱ�Ӹ��ļ���
    */

    imshow("pic", pic);
    waitKey(-1);
}
