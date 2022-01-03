/*
*本文件学习访问图像中的像素
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <windows.h>
using namespace cv;
using namespace std;

void lut_(void);                                            //lut批量处理的使用
void time_(void);                                           //计时系统
void pixel(Mat &input, Mat &output, int div, int type = 0); //多种方式访问图像中像素

int main()
{
    Mat pic = imread("lena.jpg", IMREAD_COLOR), dst;
    dst.create(pic.rows, pic.cols, pic.type());
    double time0 = static_cast<double>(getTickCount()); //计时开始
    pixel(pic, dst, 32, 1);
    time0 = (static_cast<double>(getTickCount()) - time0) / getTickFrequency();
    cout << "时长 : " << time0 << endl;
    imshow("pic", pic);
    waitKey(-1);
}

void lut_(void)
{
    Mat pic = imread("lena.jpg", IMREAD_COLOR), res;
    //当想对图片进行颜色放缩时
    //可先建立放缩表，然后直接查表
    //当图片较大时这样速度很快

    Mat look_up_table(1, 256, CV_8UC1);
    //单通道lut数组
    uchar *p = look_up_table.data;
    for (int i = 0; i < 256; i++)
    {
        p[i] = (i / 100) * 100;
    }

    LUT(pic, look_up_table, res);
    //lut函数用于批量处理颜色映射这类操作
    //第一个参数的原数据，要求必须是8位
    //第二个通道时映射数组，可以为单通道或多通道
    //为单通道时表示原矩阵每个通道都按照此进行映射
    imshow("look_up_table", res);

    Mat look_up_mutitable(1, 256, CV_8UC3);
    p = look_up_mutitable.data;
    for (int i = 0; i < 256; i++)
    {
        p[3 * i] = 95 + i / 100 * 100;
        p[3 * i + 1] = 52 + i / 100 * 100;
        p[3 * i + 2] = 63 + i / 100 * 100;
    }
    //多通道的mat数据处理时，每逻辑列实际上占据通道数个数组列
    LUT(pic, look_up_mutitable, pic);
    imshow("pic_muti", pic);

    waitKey(-1);
}

void time_(void)
{
    double time0 = static_cast<double>(getTickCount());
    //此函数返回自某个时刻（如启动后）cpu时钟周期数
    Mat pic = imread("lena.jpg", IMREAD_COLOR);
    time0 = (static_cast<double>(getTickCount()) - time0) / getTickFrequency();
    cout << "时长 : " << time0 << endl;
    system("pause");
}

void pixel(Mat &input, Mat &output, int div, int type)
{
    int rows = output.rows;
    int cols = output.cols;
    cout << cols << endl;
    switch (type)
    {
    case 0:
        //使用指针访问元素，速度最快
        //多通道的矩阵用指针访问时的列数是通道数*逻辑列
        //而其他两种方式的通道被包含在逻辑列中，使用下标访问
        {
            cols = cols * output.channels();
            for (int i = 0; i < rows; i++)
            {
                uchar *data = output.ptr<uchar>(i);
                //这个函数返回第i行的首地址
                for (int j = 0; j < cols; j++)
                {
                    data[j] = data[j] / div * div + div / 2;
                }
            }
        }
        break;

    case 1:
        //使用迭代器处理
        //迭代器是从第一个元素访问到最后一个元素
        {
            Mat_<Vec3b>::iterator it_begin = output.begin<Vec3b>();
            Mat_<Vec3b>::iterator it_end = output.end<Vec3b>();

            for (; it_begin != it_end; it_begin++)
            {
                (*it_begin)[0] = (*it_begin)[0] / div * div + div / 2;
                (*it_begin)[1] = (*it_begin)[1] / div * div + div / 3;
                (*it_begin)[2] = (*it_begin)[2] / div * div + div / 4;
            }
        }
        break;

    case 2:
        //使用动态地址,at方法
        {
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    output.at<Vec3b>(i, j)[0] = output.at<Vec3b>(i, j)[0] / div * div + div / 2;
                    output.at<Vec3b>(i, j)[1] = output.at<Vec3b>(i, j)[1] / div * div + div / 2;
                    output.at<Vec3b>(i, j)[2] = output.at<Vec3b>(i, j)[2] / div * div + div / 2;
                }
            }
        }
    }
}
