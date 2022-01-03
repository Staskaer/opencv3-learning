/*
*���ļ�ѧϰ����ͼ���е�����
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <windows.h>
using namespace cv;
using namespace std;

void lut_(void);                                            //lut���������ʹ��
void time_(void);                                           //��ʱϵͳ
void pixel(Mat &input, Mat &output, int div, int type = 0); //���ַ�ʽ����ͼ��������

int main()
{
    Mat pic = imread("lena.jpg", IMREAD_COLOR), dst;
    dst.create(pic.rows, pic.cols, pic.type());
    double time0 = static_cast<double>(getTickCount()); //��ʱ��ʼ
    pixel(pic, dst, 32, 1);
    time0 = (static_cast<double>(getTickCount()) - time0) / getTickFrequency();
    cout << "ʱ�� : " << time0 << endl;
    imshow("pic", pic);
    waitKey(-1);
}

void lut_(void)
{
    Mat pic = imread("lena.jpg", IMREAD_COLOR), res;
    //�����ͼƬ������ɫ����ʱ
    //���Ƚ���������Ȼ��ֱ�Ӳ��
    //��ͼƬ�ϴ�ʱ�����ٶȺܿ�

    Mat look_up_table(1, 256, CV_8UC1);
    //��ͨ��lut����
    uchar *p = look_up_table.data;
    for (int i = 0; i < 256; i++)
    {
        p[i] = (i / 100) * 100;
    }

    LUT(pic, look_up_table, res);
    //lut������������������ɫӳ���������
    //��һ��������ԭ���ݣ�Ҫ�������8λ
    //�ڶ���ͨ��ʱӳ�����飬����Ϊ��ͨ�����ͨ��
    //Ϊ��ͨ��ʱ��ʾԭ����ÿ��ͨ�������մ˽���ӳ��
    imshow("look_up_table", res);

    Mat look_up_mutitable(1, 256, CV_8UC3);
    p = look_up_mutitable.data;
    for (int i = 0; i < 256; i++)
    {
        p[3 * i] = 95 + i / 100 * 100;
        p[3 * i + 1] = 52 + i / 100 * 100;
        p[3 * i + 2] = 63 + i / 100 * 100;
    }
    //��ͨ����mat���ݴ���ʱ��ÿ�߼���ʵ����ռ��ͨ������������
    LUT(pic, look_up_mutitable, pic);
    imshow("pic_muti", pic);

    waitKey(-1);
}

void time_(void)
{
    double time0 = static_cast<double>(getTickCount());
    //�˺���������ĳ��ʱ�̣���������cpuʱ��������
    Mat pic = imread("lena.jpg", IMREAD_COLOR);
    time0 = (static_cast<double>(getTickCount()) - time0) / getTickFrequency();
    cout << "ʱ�� : " << time0 << endl;
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
        //ʹ��ָ�����Ԫ�أ��ٶ����
        //��ͨ���ľ�����ָ�����ʱ��������ͨ����*�߼���
        //���������ַ�ʽ��ͨ�����������߼����У�ʹ���±����
        {
            cols = cols * output.channels();
            for (int i = 0; i < rows; i++)
            {
                uchar *data = output.ptr<uchar>(i);
                //����������ص�i�е��׵�ַ
                for (int j = 0; j < cols; j++)
                {
                    data[j] = data[j] / div * div + div / 2;
                }
            }
        }
        break;

    case 1:
        //ʹ�õ���������
        //�������Ǵӵ�һ��Ԫ�ط��ʵ����һ��Ԫ��
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
        //ʹ�ö�̬��ַ,at����
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
