/*
 * ��ֵ����
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
     * ��ֵ������ǰ�������������
     * ��������������ֵ�����ĸ���������ֵ���ֵ���������йأ�
     * ���������:
     * THRESH_BINARY -- ��ֵ����������ֵȡ��ֵ���ֵ������Ϊ0
     * THRESH_BINARY_INV -- ����ֵ����������ֵȡ0������Ϊ��ֵ���ֵ
     * THRESH_TRUNC -- ������ֵΪ��ֵ���ֵ������Ϊ����
     * THRESH_TOZERO -- ������ֵΪ����С����ֵΪ0
     * THRESH_TOZERO_INV -- ������ֵΪ0 С����ֵΪ����
    */

    adaptiveThreshold(img, dst2, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 3, 5);
    /*
     * �������ֵ��ȫ����ֵ���˴�������Ӧ��ֵ
     * ��Ϊͬһ��ͼ���в�ͬ�ֲ�Ӧ�ò�ͬ����ֵ������Ч
     * ǰ�����������������
     * ������������maxValue��������ݽ�ϲ�����ͬЧ����ͬ��
     * ���ĸ�����������Ӧ��ֵ�㷨���ͣ� ADAPTIVE_THRESH_GAUSSIAN_C��ADAPTIVE_THRESH_MEAN_C
     * ���������ֻ����THRESH_BINARY��THRESH_BINARY_INV
     * 
     * �����������Ǽ�����ֵʱ������ߴ磬Ϊ����
     * ���߸�������һ��������һ��Ϊ������������ƫ���ñ�����
     * 
     * ���岽�裺
     * �������������THRESH_BINARYʱ��dst(x,y) = maxValue if(src(x,y)>T(x,y)) else dst(x,y) = 0
     * �������������THRESH_BINARY_INVʱ��dst(x,y) = 0 if(src(x,y)>T(x,y)) else dst(x,y) = maxValue
     * ����T(x,y)ȡ���ڵ��ĸ��������õ�����Ӧ�㷨
     * �����ĸ�����ΪADAPTIVE_THRESH_MEAN_Cʱ��T(x,y)Ϊ(x,y)�����ȥƫ�ó��������ֵ
     * �����ĸ�����ΪADAPTIVE_THRESH_GAUSSIAN_Cʱ��T(x,y)Ϊ(x,y)�������ȥƫ�ó��������˹�˾���ļ�Ȩƽ��
     * 
    */

    imshow("dst2", dst2);
    imshow("threshold", dst1);
    waitKey(-1);
}