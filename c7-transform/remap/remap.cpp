/*
 * ��ӳ��
 * ��ӳ����ӳ�����Ӧ��Ҳʮ������
 * ӳ����dst(x,y) = src(h(x),h(y))
 * ��ӳ����dst(x,y) = src(hx(x),hy(y))
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat img = imread("lena.jpg", IMREAD_COLOR), dst;
    Mat map_x, map_y;

    dst.create(img.size(), img.type());
    map_x.create(img.size(), CV_32FC1);
    map_y.create(img.size(), CV_32FC1);

    for (int j = 0; j < img.rows; j++)
        for (int i = 0; i < img.cols; i++)
        {
            map_x.at<float>(j, i) = static_cast<float>(i);
            map_y.at<float>(j, i) = static_cast<float>(img.rows - j);
        }

    remap(img, dst, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));
    /*
     * ��ӳ�䲻֧�־͵ز���
     * ǰ����������������
     * ������������map1�������ֱ�ʾ����
     * ��һ����(x,y)��ӳ��
     * �ڶ�����CV_16SC2/CV_32FC1/CV_32FC2���͵�x��ֵ
     * ���ĸ�������map2�������map1��ѡ��
     * ��map1��(x,y)��ӳ��ʱ��map2����Ч����
     * �����ʾCV_16UC1/CV_32FC1���͵�y
     * ����������ǲ�ֵ��ʽ
     * INTER_NEAREST -- ���ڽ���ֵ
     * INTER_LINEAR -- ˫���Բ�ֵ��Ĭ��ֵ��
     * INTER_CUBIC -- ˫����������ֵ
     * INTER_LANCZOS4 -- �Ǹ���ֵ
     * �����������Ǳ߽�ģʽ
     * ���߸������ǳ����߽�ʹ�õ�ֵ
    */

    imshow("dst", dst);
    waitKey(-1);
}