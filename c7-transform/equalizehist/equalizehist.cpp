/*
 * ֱ��ͼ���⻯
 * ��ͨ����������ǿ�ȷֲ�����ǿͼ��Աȶȵ�һ�ַ���
 * �����������������������������ȴ������
 * ��ˣ�ԭ���ҶȲ�ͬ�����ؿ��ܱ�ûҶ���ͬ���γ�α����
 * �������⻯��ͼ��Ƶ�׸�����չ����Ч��������0-255��Χ���Աȶ���ǿ
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    Mat img = imread("lena.jpg", IMREAD_COLOR), dst;

    cvtColor(img, img, COLOR_BGR2GRAY);
    imshow("img", img);

    equalizeHist(img, dst);
    imshow("dst", dst);
    waitKey(-1);
}