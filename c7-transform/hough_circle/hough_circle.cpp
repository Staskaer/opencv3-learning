/*
 * ѧϰhoughԲ����㷨
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

int main()
{
    Mat img = imread("detect_blob.png", IMREAD_COLOR);
    Mat gray, edge;

    cvtColor(img, gray, COLOR_BGR2GRAY);
    GaussianBlur(gray, gray, Size(9, 9), 2, 2);

    vector<Vec3f> circles; //����������x��y��r

    HoughCircles(gray, circles, HOUGH_GRADIENT, 1.5, 10, 200, 100, 0, 0);
    /*
     * ǰ��������������������������Ԫ��
     * �����������Ǽ�ⷽ����ֻ���ݶ�����
     * ���ĸ�����dp���������Բ���ۼ���ͼ��ֱ���������ͼ��֮�ȵ���������
     * ��dp = 1ʱ���ۼ���������ͼ��ֱ�����ͬ��dp = 2ʱ���ۼ����ķֱ���ֻ��һ��
     * ���������ʱԲ��֮����С����
     * �������������ڲ�canny��Ե����㷨����ֵ������ֵ�Ǹ���ֵ��һ��
     * ���߸��������ݶȷ��Ĳ�����ԽС���ܼ�����Բ��Խ�����ԲԽ�ӽ�����
     * �ڰ˸�������Բ��С�뾶
     * �ھŸ�����Բ���뾶
     * 
     * ���⣬�˺���ֻ�ʺ��ҵ�Բ�ģ����ʺϼ���뾶0
    */

    for (auto x : circles)
    {
        Point center(cvRound(x[0]), cvRound(x[1]));
        int r = cvRound(x[2]);

        circle(img, center, r, Scalar(0, 255, 255), 2);
    }
    imshow("img", img);
    waitKey(-1);
}