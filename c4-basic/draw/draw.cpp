/*
*���ļ�ѧϰ��������ͼ�εĲ���
*����ֱ�ߣ���Բ��Բ�����κ��������
*/

#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

constexpr int WINDOW_WIDTH = 720;

void draw_ellipse(Mat &pic, double angle);        //ѧϰ������Բ
void draw_filled_circle(Mat &pic, Point center);  //ѧϰ���Ʒ��������ɫ
void draw_line(Mat &pic, Point start, Point end); //����ֱ��

int main(int argc, char *argv[])
{
    Mat pic(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
    draw_line(pic, Point(WINDOW_WIDTH / 16, WINDOW_WIDTH / 16), Point(WINDOW_WIDTH / 4, WINDOW_WIDTH / 4));
    imshow("pic", pic);
    waitKey(-1);
}

void draw_ellipse(Mat &pic, double angle)
{

    ellipse(pic,
            Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2),
            Size(WINDOW_WIDTH / 4, WINDOW_WIDTH / 16),
            angle,
            0,
            360,
            Scalar(0, 222, 123),
            2,
            LINE_8);
    //������Բ��������
    /*
    *��һ�����������ͼ��
    *�ڶ�����������Բ���ĵ�����
    *������������������Բ�Ĵ�С��λ�ڴ˾����ڣ�y��x)
    *���ĸ�����Բ��ת�Ƕ�0-360
    *����������ǻ��ƵĻ�����ʼ�Ƕ�0-360
    *�����������ǻ��ƵĻ��Ľ����Ƕ�0-360
    *���߸���ɫ���ڰ˸��߿��ھŸ�����
    */
}

void draw_filled_circle(Mat &pic, Point center)
{
    circle(
        pic,
        center,
        WINDOW_WIDTH / 32,
        Scalar(0, 255, 0),
        -1,
        LINE_8);
    /*
    *����˵��
    *��һ��������ͼ��
    *�ڶ���������ԭ����
    *�����������ǰ뾶
    *ʣ��Ϊ��ɫ��ϸ����
    *���߿�Ϊ-1ʱ��ʵ��
    */
}

void draw_line(Mat &pic, Point start, Point end)
{
    line(
        pic,
        start,
        end,
        Scalar::all(255),
        2,
        LINE_8);
}