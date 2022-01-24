/*
* ���ļ�ѧϰ�������˲�
* ����ɢ��������ʱ����˹�˲�����ȥ��������ֻ�����������
* ����ֵ�˲�Ч����������
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void media_filter(Mat img, Mat dst);     //��ֵ�˲�
void bilateral_filter(Mat img, Mat dst); //˫���˲�

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
    //��ֵ�˲���ʹ����������Ҷȵ���ֵ���������ر���
    //�ܹ��ܺõ������ߵ������ͽ�������
    //������ֵ�˲��Ŀ����ܴ��Ǿ�ֵ�˲���5������
    //��ֵ�˲���ϸ�ڽ϶��ͼ�񲻺���
    medianBlur(img, dst, 7);
    /*
     * �������ͣ�
     * ǰ����������������������Ǿ����
    */
    imshow("media", dst);
}

void bilateral_filter(Mat img, Mat dst)
{
    //˫���˲�ͬʱ���ǿ�����Ϣ�ͻҶ����ƶ�
    //����������Ե���棬�����˹���ֵ�˲�����ģ��
    //��ͬʱ���Ը�Ƶ�������ܺܺõ�ȥ��
    //����˫���˲�����ĥƤ
    bilateralFilter(img, dst, 25, 25 * 2, 25 / 2);
    /*
     * ����������
     * ǰ�������������
     * ����������������ֱ����������Ϊ�Ǹ���������õ��ĸ������������
     * ���ĸ���������ɫ�ռ��˲�����sigmaֵ������˵��������Լ������ɫ����ϵ�һ��
     * ���������������ռ��˲�����sigmaֵ��Խ��˵�����ԽԶ�����ػ��໥Ӱ��
    */
    imshow("bilatera", dst);
}