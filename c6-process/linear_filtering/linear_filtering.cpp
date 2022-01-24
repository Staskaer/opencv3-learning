/*
* ���ļ�ѧϰ�����˲���������ͨ�˲�����ͨ�˲�����ͨ�˲��������˲���
*���е�ͨ�˲���ģ������ͨ�˲�����

*�������ӣ����ø���������Χ������������������
*������ͼ��ֲ����ص������˲�

*opencv���ṩ�����ֳ��õ��˲�������
*�����˲�boxblur()
*��ֵ�˲�blur()
*��˹�˲�GaussianBlur()
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void box_filter(Mat img, Mat dst);    //�����˲�
void blur_(Mat img, Mat dst);         //��ֵ�˲�
void gaussian_blur(Mat img, Mat dst); //��˹�˲�

int main()
{
    Mat img = imread("lena.jpg", IMREAD_COLOR), dst;
    imshow("raw", img);
    box_filter(img, dst);
    blur_(img, dst);
    gaussian_blur(img, dst);
    waitKey(-1);
}

void box_filter(Mat img, Mat dst)
{
    boxFilter(img, dst, -1, Size(3, 3), Point(-1, -1), false, BORDER_DEFAULT);
    /*
     * ����˵����ǰ������������������
     * ���������������ͼ����ȣ�-1����ʹ��ԭͼ�����
     * ���ĸ��������ں˴�С
     * �����������ê�㣬����ƽ�����Ǹ��㣬ȡ��ֵ������
     * �������������Ƿ��һ������һ��ʱ���Ǿ�ֵ�˲�
     * ���߸��������ùܣ�����߽�ģʽ
    */
    imshow("box_filter", dst);
}

void blur_(Mat img, Mat dst)
{
    blur(img, dst, Size(5, 5), Point(-1, -1));
    //��ֵ�˲���api��������boxfilter��apiһ��
    //���ǹ�һ��ʱ��boxfilter
    imshow("blur", dst);
}
void gaussian_blur(Mat img, Mat dst)
{
    GaussianBlur(img, dst, Size(5, 5), 0, 0);
    /*
     * ��������
     * ǰ�������������
     * ������������ksize������Ϊ��������������sigma����õ�
     * ���ĵ������������X,Y�����ϵ�ƫ��ֵ
    */
    imshow("gaussian", dst);
}