/*
*���ļ�ѧϰ����ͼ�����ȺͶԱȶ�
*��Ϊ�����
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

void contrast_and_light(int, void *); //�ص�����

int contrast_value;
int bright_value;

int main()
{
    contrast_value = 0;
    bright_value = 0;

    Mat pic = imread("lena.jpg", IMREAD_COLOR), dst = Mat::zeros(pic.size(), pic.type());
    //ע�⣬�˴�Ҫ��dst����Ϊ0�������ڶ�ȡ����ʱ��������
    vector<Mat *> tup = {&pic, &dst};

    namedWindow("show", WINDOW_NORMAL);
    createTrackbar("contrast", "show", &contrast_value, 300, contrast_and_light, tup.data());
    createTrackbar("bright", "show", &bright_value, 200, contrast_and_light, tup.data());

    imshow("show", pic);
    waitKey();
}

void contrast_and_light(int data, void *temp)
{
    Mat pic = *((Mat **)temp)[0], dst = *((Mat **)temp)[1];

    for (int y = 0; y < pic.rows; y++)
        for (int x = 0; x < pic.cols; x++)
            for (int c = 0; c < 3; c++)
            {
                dst.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(contrast_value * 0.01 * (pic.at<Vec3b>(y, x)[c]) + bright_value);
            }

    imshow("show", dst);
}