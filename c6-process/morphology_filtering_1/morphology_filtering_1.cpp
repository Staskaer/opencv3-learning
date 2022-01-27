/*
*���ļ�ѧϰ��̬ѧ�˲��Ļ�������
*��̬ѧ�����ǻ�����״���б仯��ͼ����

*�˴��漰���ͺ͸�ʴ
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat img = imread("lena.jpg", IMREAD_COLOR), dst1, dst2;

    //����
    /*
    ���;�����ֲ����ֵ�����������������˻�����
    Ȼ����������ֵ��ֵ��ê��
    �ǽ�������������
    */

    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15), Point(-1, -1));
    /*
    ��������ܹ�����ָ����״�˳ߴ���ں˾���������ͺ˸�ʴ��ʹ��
    ���е�һ�����������ǣ�MORPH_RECT��MORPH_CROSS,MORPH_ELLIPSE
    �ֱ��Ǿ��Σ������Σ���Բ

    ����ʮ��������ê����ȷ����״�⣬����ê��ֻ��Ӱ����̬ѧ����Ľ��ƫ��
    */
    dilate(img, dst1, element);
    /*
     * ǰ�����������������
     * �����������Ǻ˾���
     * ���ĸ�������ê��
     * ����������ǵ�������
     * �������߸������Ǳ߽���ز�����һ�㲻��
    */

    //��ʴ
    /*
    ��ʴ�����͵ķ��仯������Сֵ��ֵ��ê��
    ��������������
    */
    erode(img, dst2, element);
    /*
     * ��dilate������������
     * һ��ֻ����ǰ��������������getStructuringElement���ʹ��
    */

    imshow("raw", img);
    imshow("dilate", dst1);
    imshow("erode", dst2);
    waitKey(-1);
}