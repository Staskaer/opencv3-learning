/*
* ���ļ�ѧϰhough�任
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

void hough_line();   //��׼hough�任
void hough_line_p(); //�ۼƸ���hough�任

int main()
{
    hough_line_p();
}

void hough_line()
{
    Mat img = imread("sudoku.png", IMREAD_COLOR);
    Mat gray, edge;

    cvtColor(img, gray, COLOR_BGR2GRAY);
    Canny(gray, edge, 50, 200, 3); //�ȻҶȺ����Ե

    vector<Vec2f> lines; //����߼���
    HoughLines(edge, lines, 1, CV_PI / 180, 150, 0, 0);
    /*
     * ��׼hough�任
     * ��һ�������¶�ֵ���ı�Եͼ��
     * �ڶ���������vector���飬����߼��ϣ�ÿ��Ԫ��Ϊ��rho��theta����ʽ����
     * ����������������Ϊ��λ�ľ��뾫��rho
     * ���ĸ��������Ի���Ϊ��λ�ĽǶȾ���theta
     * ������������ۼӵ�ƽ�����ֵ���������ֱ��ߵ���С��ֵ
     * �����������Ƕ�߶�hough�任�µĵ���������rho�ĳ������루����
     * ���߸������Ƕ�߶�hough�任�µĵ��ĸ�����theta�ĳ�������
     * ����������������0ʱ����ʾʹ�þ���hough�任
    */
    for (auto x : lines)
    {
        //lines��ÿ��Ԫ�ص�һ����rho���ڶ�����theta
        float rho = x[0], theta = x[1];
        Point p1, p2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;

        //�����Ǽ��α任
        p1.x = cvRound(x0 + (-b * 1000));
        p1.y = cvRound(y0 + 1000 * a);
        p2.x = cvRound(x0 - 1000 * (-b));
        p2.y = cvRound(y0 - 1000 * a);

        line(img, p1, p2, Scalar(0, 255, 0), 2);
    }
    imshow("edge", edge);
    imshow("dst", img);
    waitKey(-1);
}

void hough_line_p()
{
    Mat img = imread("sudoku.png", IMREAD_COLOR);
    Mat gray, edge;

    cvtColor(img, gray, COLOR_BGR2GRAY);
    Canny(gray, edge, 50, 200, 3); //�ȻҶȺ����Ե

    vector<Vec4i> lines; //����߼���
    HoughLinesP(edge, lines, 1, CV_PI / 180, 80, 50, 10);
    /*
     * ����hough�任���׼hough�任��֮ͬ���Ǹ��ʷ��ص�lines�ṹ��4Ԫ�飬
     * ��Ӧ�˵ѿ�������ϵ�µ��������ꣻ����׼hough���ؼ�����ϵ��rho��theta
     * 
     * ��һ�������Ǳ�Ե
     * �ڶ�����������Ԫ�����νṹ���洢��
     * ���������ĸ������Ǳ�׼Hough�еĲ���
     * ������������ۼ���ֵ
     * �������������߶���ͳ���
     * ���߸�����������ͬһ�е����������������Ŀ
     */

    for (auto x : lines)
    {
        Vec4i l = x; //ע������

        //����Ҫ���α任
        line(img, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 255, 0), 1);
    }

    imshow("dst", img);
    waitKey(-1);
}