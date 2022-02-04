/*
 * ���ļ�ѧϰ�ǵ����е�harris�ǵ���
 * ͼ����������������¼��ࣺ
 * ��Ե���ǵ㣨����Ȥ�ĵ㣩���ߵ㣨����Ȥ������
 * 
 * ���У����ĳһ������һ�����΢С�䶯��������ܴ�ĻҶȱ仯����Ϊ�ǵ�
 * �ǵ�λ��������Ե�Ľǵ㣬������������Ե�仯�����ϵĵ�
 * �Ǿ�ȷ��λ�Ķ�ά����
 * 
 * �ǵ���������¼���������
 * һ�׵������Ҷ��ݶȣ��ľֲ�����Ӧ���ص�
 * �������������ϱ�Ե�Ľ���
 * ͼ�����ݶ�ֵ���ݶȷ���ı仯���ʶ��ܸߵĵ�
 * �ǵ㴦һ�׵���󣬶��׵�Ϊ0���������Ե�仯�������ķ���
 */

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat img, img_l, gray;
int thres = 30;
constexpr int max_thres = 175;

void on_corner_harris(int, void *);

int main()
{
    img = imread("test.jpg", IMREAD_COLOR);
    img_l = img.clone();

    cvtColor(img_l, gray, COLOR_BGR2GRAY);

    namedWindow("dst", WINDOW_FREERATIO);
    createTrackbar("thres", "dst", &thres, max_thres, on_corner_harris, 0);

    on_corner_harris(0, 0);

    waitKey(-1);
}

void on_corner_harris(int, void *)
{
    Mat dst, norm_img, scale_img; //�������һ��ͼ�����Ա任��8λ�޷���ͼ��

    dst = Mat::zeros(img.size(), CV_32FC1);
    img_l = img.clone();

    cornerHarris(gray, dst, 2, 3, 0.04, BORDER_DEFAULT);
    /*
     * harris�ǵ��⺯��
     * ����harris�ǵ������������нǵ���
     * ��һ������������ͼ�񣬵�ͨ��8λ�򸡵�ͼ��
     * �ڶ��������������ֵ����Դͼ��һ���ĳߴ�����
     * �����������������С
     * ���ĸ�������sobel���ӵĿ׾���С
     * �����������harris����
     * �����������Ǳ߽�
    */

    normalize(dst, norm_img, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
    convertScaleAbs(norm_img, scale_img); //����һ��ͼ��ת��λ8λ�޷�������

    for (int j = 0; j < norm_img.rows; j++)
        for (int i = 0; i < norm_img.cols; i++)
        {
            if ((int)norm_img.at<float>(j, i) > thres + 80)
            {
                circle(img_l, Point(i, j), 5, Scalar(0, 0, 255), 2, 8, 0);
                circle(scale_img, Point(i, j), 5, Scalar(0, 0, 255), 2, 8, 0);
            }
        }
    imshow("dst", img_l);
    imshow("scale", scale_img);
}