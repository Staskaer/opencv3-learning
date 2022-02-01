/*
 * �ö����ȥ�ƽ�����
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat img = imread("templ.png", IMREAD_GRAYSCALE);
    resize(img, img, Size(img.cols * 4, img.rows * 4));
    Mat img2 = Mat::zeros(img.size(), CV_8UC3);

    threshold(img, img, 127, 255, THRESH_BINARY_INV);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    //�����������Ҷ�ͼ��
    findContours(img, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    //��Ŷ���αƽ��ĵ㼯
    vector<vector<Point>> contours_poly(contours.size());

    approxPolyDP(Mat(contours[0]), contours_poly[0], 3, true);
    /*
     * ����αƽ��㷨
     * ��һ��������Ҫ�ƽ�������
     * �ڶ��������Ǳƽ��Ľ����Ҳ�ǵ㼯
     * �����������Ǳƽ��ľ��ȣ���ԭ������ƽ����ߵľ���֮������ֵ
     * ���ĸ��������Ƿ��գ�true��գ����򲻷��
    */
    drawContours(img2, contours_poly, 0, Scalar(0, 0, 255), 3, LINE_AA);

    imshow("img", img2);
    waitKey(-1);
}