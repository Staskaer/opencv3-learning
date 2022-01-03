/*
*���ļ�ѧϰROI��ز���
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;

void get_roi(void);                     //�����ַ�����ȡROI
void roi_add(void);                     //��roi��дԴͼ��ָ������
void linear_add(void);                  //���Ի�ϲ���
void bar_callback(int bar, void *temp); //trackbar�ص�����

int main()
{
    linear_add();
}

void get_roi(void)
{
    Mat pic = imread("lena.jpg", IMREAD_COLOR);
    //�����ַ�����ȡROI
    //��һ����ʹ��rect������������
    Mat picRoi = pic(Rect(400, 250, 100, 200));
    imshow("roi", picRoi);
    waitKey(-1);

    //Ҳ����ʹ��Range�໮�ֳ���Χ�����к���
    picRoi = pic(Range(250, 450), Range(400, 500));
    imshow("roi", picRoi);
    waitKey(-1);
}

void roi_add(void)
{
    //��roi����дԴͼ���ָ������

    Mat pic_raw = imread("lena.jpg", IMREAD_COLOR);
    Mat pic_roi = pic_raw(Rect(0, 0, 200, 200));

    Mat mask; //����Ҷ���ģ���˴�û�õ�
    cvtColor(pic_roi, mask, COLOR_BGR2GRAY);

    pic_roi.copyTo(pic_raw(Rect(200, 200, 200, 200)));
    //copyto������self���Ƶ�ָ������
    //��һ������ģ�����أ���������ĻҶ���ģ�����Խ��հ�������Դͼ��

    imshow("result", pic_raw);
    waitKey(-1);
}

void linear_add(void)
{
    //���Ի��ʹ��addweighted������֮ǰ����
    //Ҫ��ͬ�ߴ������ͼ����ָ���������
    //�˴��ǽ�roi���Ի��

    Mat pic1 = imread("left.jpg", IMREAD_COLOR), pic2 = imread("right.jpg", IMREAD_COLOR), copy;
    Mat roi1 = pic1(Rect(100, 100, 500, 500)), roi2 = pic2(Rect(100, 100, 500, 500));
    roi1.copyTo(copy);
    vector<Mat *> tup = {&pic1, &pic2, &roi1, &roi2, &copy};

    int alpha = 10;
    namedWindow("addweighted", WINDOW_NORMAL);
    createTrackbar("bar", "addweighted", &alpha, 100, bar_callback, tup.data());

    waitKey(-1);
}

void bar_callback(int bar, void *temp)
{
    double alpha_value, beta_value;
    alpha_value = double(bar) / 100;
    beta_value = 1.0 - alpha_value;

    Mat pic1 = *((Mat **)temp)[0],
        pic2 = *((Mat **)temp)[1],
        roi1 = *((Mat **)temp)[2],
        roi2 = *((Mat **)temp)[3],
        copy = *((Mat **)temp)[4];
    addWeighted(copy, alpha_value, roi2, beta_value, 0.0, roi1);
    imshow("addweighted", pic1);
}