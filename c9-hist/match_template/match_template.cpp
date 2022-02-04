/*
 * ģ��ƥ��
 * ģ��ƥ������һ��ͼ����Ѱ������һ����ƥ��ͼ�����ƥ��Ĳ���
 * ����һ��������ƥ������
 * ģ��ƥ�䲻�ǻ���ֱ��ͼ��������ͼ���ϻ���
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat img, template_img, dst;
int method = 0;

void on_match(int, void *); //ģ��ƥ��Ļص�����

int main()
{
    img = imread("raw.jpg", 1);
    template_img = imread("template.png");

    namedWindow("raw", WINDOW_FREERATIO);
    namedWindow("dst", WINDOW_FREERATIO);

    createTrackbar("type", "raw", &method, 5, on_match, 0);

    on_match(0, 0);

    waitKey(-1);
}

void on_match(int, void *)
{
    Mat src;
    img.copyTo(src);

    //��ʼ������������
    int result_rows = img.rows - template_img.rows + 1;
    int result_cols = img.cols - template_img.cols + 1;
    dst.create(result_rows, result_cols, CV_32FC1);

    //ƥ��ͱ�׼��
    matchTemplate(src, template_img, dst, method);
    /*
     * ģ��ƥ�亯��
     * ��һ�������Ǵ�����ͼ��
     * �ڶ���ͼ��ʱ����ģ�壬��Դͼ����һ�������ݽṹ����
     * ����������ʱ���ͼ��λ32λ��ͨ������
     * ���ͼ��ߴ�W*H��ģ��ߴ�w*h����Ϊ��W-w+1)*(H-h+1)
     * ���ĸ�������ƥ��ķ�������6��
     * TM_SQDIFF -- ƽ����ƥ��
     * TM_SQDIFF_NORMED -- ��һ��ƽ����ƥ��
     * TM_CCORR -- ���ƥ��
     * TM_CCORR_NORMED -- ��һ�����ƥ��
     * TM_CCOEFF -- ϵ��ƥ��
     * TM_CCOEFF_NORMED -- ��һ����ϵ��ƥ��
    */
    normalize(dst, dst, 0, 1, NORM_MINMAX, -1, Mat());

    //��λ���ƥ��λ��
    double min_value, max_value;
    Point min_location, max_location, match_location;
    minMaxLoc(dst, &min_value, &max_value, &min_location, &max_location);

    //�еķ�������ֵԽСԽ��׼���е����෴
    if (method == TM_SQDIFF || method == TM_SQDIFF_NORMED)
        match_location = min_location;
    else
        match_location = max_location;

    rectangle(src, match_location, Point(match_location.x + template_img.cols, match_location.y + template_img.rows), Scalar(0, 0, 255), 2, 8, 0);
    rectangle(dst, match_location, Point(match_location.x + template_img.cols, match_location.y + template_img.rows), Scalar(0, 0, 255), 8, 0);

    imshow("dst", dst);
    imshow("raw", src);
}