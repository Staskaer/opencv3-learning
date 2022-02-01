/*
 * ѧϰͼ��ľ�
 * �ؼ�ͨ��������ͼ���ȫ������
 * ���ṩ�˴����Ĺ��ڸ�ͼ��ͬ���͵ļ���������Ϣ
 * �������ڸ���ͼ����ϵͳ��
 * 
 * ����һ�־���ƽ����ת�߶Ȳ�������
 * ��ͨ�ļ��ξ��ǻ���ԭ�����
 * p+q����ͨ��mpq = �� �� x^p*y^qf(x,y)  ��x,y��Χ����ͣ�Ҳ�������У�
 * ��׾�m00�������
 * һ�׾�m01��m10��x��y��ľأ���������ȷ������
 * 
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat img, dst, gray;
int thres = 100;
int max_thres = 255;
RNG rng(123456);
Mat canny_out;
vector<Vec4i> hierarchy;
vector<vector<Point>> contours;

void on_thres_change(int, void *);

int main()
{
    system("color 1e");
    img = imread("lena.jpg", IMREAD_COLOR);

    //�Ҷ�ģ����
    cvtColor(img, gray, COLOR_BGR2GRAY);
    blur(gray, gray, Size(3, 3));

    namedWindow("img", WINDOW_AUTOSIZE);
    imshow("img", img);

    createTrackbar("thres", "img", &thres, max_thres, on_thres_change);
    on_thres_change(0, 0);

    waitKey(0);
    return 0;
}

void on_thres_change(int, void *)
{
    Canny(gray, canny_out, thres, 2 * thres, 3);

    //Ѱ�ұ߽�
    findContours(canny_out, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

    //��ʼ�����
    vector<Moments> mu(contours.size());
    for (size_t i = 0; i < contours.size(); i++)
        mu[i] = moments(contours[i], false);
    /*
         * moment���������Ǽ���������׵����о�
         * ��һ��������������
        */

    //�������ľ�
    vector<Point2f> mc(contours.size());
    for (size_t i = 0; i < contours.size(); i++)
        mc[i] = Point2f(static_cast<float>(mu[i].m10 / mu[i].m00), static_cast<float>(mu[i].m01 / mu[i].m00));

    //��������
    Mat drawing = Mat::zeros(canny_out.size(), CV_8UC3);
    for (size_t i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        drawContours(drawing, contours, i, color, 2, LINE_AA, hierarchy);
        circle(drawing, mc[i], 4, color, -1, LINE_AA, 0);
    }

    namedWindow("dst", WINDOW_AUTOSIZE);
    imshow("dst", drawing);
}