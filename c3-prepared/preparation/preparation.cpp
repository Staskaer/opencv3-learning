//��¼opencv c++��̵Ļ�������
//��ȡͼƬ��Mat���飬��ʾ
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

int main()
{
    Mat pic(320, 640, 0, Scalar(100));
    //������mat����

    Mat image = imread("lena.jpg", IMREAD_COLOR);
    /*
    *imread��������һ����·��
    *�ڶ�������flag�ж��ȡֵ�����Դ���int�����ö��
    *���λ�� | ����
    *IMREAD_ANYCOLOR | IMREAD_ANYDEPTH �Ǵ�������ͼ��
    *flags���븺ֵ��������alphaͨ����Ĭ���ǲ������
    */

    imshow("show", image);
    waitKey(-1);
    destroyAllWindows();
    /*
    *imshow������һ��������������ڵ�id
    *���������Ĭ��ֵ�����ģ�����ʾԭʼ�ߴ磬���򽫽�������
    *����ԭ��uint8 -- ԭʼ�ߴ�
    *uint16��uint32 -- ��[0��255*256]ӳ�䵽[0,255]
    *float32 -- ��[0,1]ӳ�䵽[0��255]
    */

    system("pause");
}