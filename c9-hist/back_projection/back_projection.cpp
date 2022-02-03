/*
 * ����ͶӰ
 * ����ֱ��ͼ���Կ�����һ�����ʺ�����λĳ����������ĳ������ĸ���
 * ����ͶӰ��һ�ּ�¼����ͼ�������ص������Ӧֱ��ͼģ�͵����طֲ�
 * ���ȼ���ĳһ������ֱ��ͼ��Ȼ��ʹ��ģ��ȥѰ��ͼ���д��ڸ������ķ���
 * 
 * ��ʹ��ģ��ͼ����ֱ��ͼ
 * Ȼ��Բ���ͼ���ÿ������p(i,j)����ȡɫ�����ݲ��ҵ���ɫ��(hij,sij)��ֱ��ͼ��bin��λ��
 * Ȼ�����bin����ֵ����洢�ڷ���ͶӰͼ����
 * ��ÿ�������ظ����ϲ��裬�õ�ȫ���ķ���ͶӰͼ��
 * 
 * ���������ڽϴ������ͼ���������ҽ�С��ģ��ͼ��λģ��ͼ���λ��
 * 
 * ���԰ѷ���ͶӰͼ�񿴳��Ƕ�ά�������顢��ά���󡢵�ͨ������ͼ��
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat img, hsv, dst, hue;
int bins = 30;

void on_bin_change(int, void *);

int main()
{
    img = imread("left.jpg", IMREAD_COLOR);
    cvtColor(img, hsv, COLOR_BGR2HSV);

    hue.create(hsv.size(), hsv.depth());
    int ch[] = {0, 0};
    mixChannels(&hsv, 1, &hue, 1, ch, 1);
    /*
     * ͨ�����ƺ���
     * �������������ĳͨ��������������ض�ͨ����
     * �����ֱ���������󣬾�����Ŀ��������󣬾�����Ŀ��fromto���飬fromto����Ĵ�С-1
    */

    namedWindow("img", WINDOW_AUTOSIZE);
    createTrackbar("bins", "img", &bins, 180, on_bin_change, 0);
    on_bin_change(0, 0);

    imshow("img", img);
    waitKey(-1);
}

void on_bin_change(int, void *)
{
    MatND hist;
    int hist_size = MAX(bins, 2);
    float hue_range[] = {0, 180};
    const float *ranges = {hue_range};

    calcHist(&hue, 1, 0, Mat(), hist, 1, &hist_size, &ranges, true, false);
    /*
     * ����ֱ��ͼ
    */
    normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());
    /*
     * ��һ������
    */

    MatND backproj;
    calcBackProject(&hue, 1, 0, hist, backproj, &ranges, 1, true);
    /*
     * ���㷴��ͶӰ
     * ��һ�������������ͼ�񣨴��Ƚϵ�ͼ�������������鼯��������ͬ�ߴ�����
     * �ڶ�����������������ߴ�
     * ��������������Ҫͳ�Ƶ�ͨ������������0��ʼ��
     * ���ĸ�����������ֱ��ͼ
     * �����������Ŀ�귴��ͶӰ���У�����Ϊ��ͨ��
     * ������������ÿһά��ֵ��ȡֵ��Χ
     * ���߸���������������
     * �ڰ˸�������ֱ��ͼ�Ƿ���ȱ�־λ
    */

    imshow("img", backproj);

    //����ֱ��ͼ
    int w = 400, h = 400;
    int bin_w = cvRound((double)w / hist_size);
    Mat hist_img = Mat::zeros(w, h, CV_8UC3);

    for (int i = 0; i < bins; i++)
    {
        rectangle(hist_img, Point(i * bin_w, h), Point((i + 1) * bin_w, h - cvRound(hist.at<float>(i) * h / 255.0)), Scalar(100, 123, 255), -1);
    }
    imshow("hist", hist_img);
}