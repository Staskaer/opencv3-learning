/*
 * ����ֱ��ͼ
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void calc_hist_2d();  //�����ά�ֲ�ֱ��ͼ
void calc_hist();     //����һά�ֲ�ֱ��ͼ
void calc_hist_rgb(); //����rgb��ͨ���ķֲ�ֱ��ͼ

int main()
{
    calc_hist_rgb();
}

void calc_hist_2d()
{
    Mat img = imread("lena.jpg", IMREAD_COLOR);
    cvtColor(img, img, COLOR_BGR2HSV);

    int hue_bin_num = 30;        //����ֱ��ͼֱ����Ŀ
    int saturation_bin_num = 32; //���Ͷ�ֱ��ͼֱ����Ŀ
    int hist_size[] = {hue_bin_num, saturation_bin_num};

    float hue_range[] = {0, 180};        //����ɫ���任��Χ
    float saturation_range[] = {0, 256}; //���ñ��Ͷȱ仯��Χ0-255
    const float *ranges[] = {hue_range, saturation_range};
    MatND hist;
    /*
     * MatND��ʾ��ά���飨���ڵ�����ά��
     * ������Mat����
    */
    int channels[] = {0, 1}; //��0�͵�1ͨ��ֱ��ͼ

    calcHist(&img, 1, channels, Mat(), hist, 2, hist_size, ranges, true, false);
    /*
     * ����һ�����߶�����е�ֱ��ͼ
     * ��һ���������������������鼯����ַ����Ҫ��ߴ�������ͬ��
     * �ڶ�����������������ĸ���������һ���������м���ͼ��
     * ��������������Ҫͳ�Ƶ�ͨ��������
     * ���ĸ���������ģ��8λͬ�ߴ磩
     * �����������������飬��һ����ά����
     * �����������Ǽ���ֱ��ͼ��ά�ȣ�����������
     * ���߸�������ÿ��ά���µ�ֱ��ͼ�ߴ�
     * �ڰ˸�������ÿһ��ά�ȵ�ȡֵ��Χ
     * �ھŸ�������ָʾֱ��ͼ�Ƿ���ȵ�flag
     * ��ʮ���������ۼƱ�ʶ���������ڶ�������м��㵥��ֱ��ͼ
    */

    double max_value = 0;
    minMaxLoc(hist, 0, &max_value, 0, 0);
    /*
     * ����������Сֵ
     * ��һ�������������ֱ��ͼ����
     * �ڶ��������Ƿ�����Сֵ��ָ�룬������������Ϊ0
     * �����������Ƿ������ֵ��ָ�룬������������Ϊ0
     * ���ĸ������Ƿ�����Сλ�õ�ָ��
     * ����������Ƿ������λ�õ�ָ��
     */
    int scale = 10;
    Mat hist_img = Mat::zeros(saturation_bin_num * scale, hue_bin_num * 10, CV_8UC3);

    for (int hue = 0; hue < hue_bin_num; hue++)
        for (int saturation = 0; saturation < saturation_bin_num; saturation++)
        {
            float bin_value = hist.at<float>(hue, saturation);
            int intensity = cvRound(bin_value * 255 / max_value);

            rectangle(hist_img, Point(hue * scale, saturation * scale), Point((hue + 1) * scale - 1, (saturation + 1) * scale - 1), Scalar::all(intensity), FILLED);
        }

    imshow("img", hist_img);
    waitKey(-1);
}

void calc_hist()
{
    Mat img = imread("lena.jpg", 0);
    MatND hist;
    int dims = 1;
    float hranges[] = {0, 255};
    const float *ranges[] = {hranges};
    int size = 256;
    int channels = 0;
    int scale = 1;

    calcHist(&img, 1, &channels, Mat(), hist, dims, &size, ranges);
    //����ֱ��ͼ

    Mat dst(size * scale, size, CV_8U, Scalar(0));

    double max_value = 0, min_value = 0;
    minMaxLoc(hist, &min_value, &max_value, 0, 0);

    int hpt = saturate_cast<int>(0.9 * size);
    for (int i = 0; i < 256; i++)
    {
        float bin_value = hist.at<float>(i);
        int real_value = saturate_cast<int>(bin_value * hpt / max_value);
        rectangle(dst, Point(i * scale, size - 1), Point((i + 1) * scale - 1, size - real_value), Scalar(255));
    }
    imshow("dst", dst);
    waitKey(-1);
}

void calc_hist_rgb()
{
    Mat img = imread("lena.jpg", IMREAD_COLOR);

    // for (int i = 0; i < img.rows; i++)
    //     for (int j = 0; j < img.cols; j++)
    //         (img.at<Vec3b>(i, j))[0] = 0;
    //���ϴ�����Բ��Ի����Ƿ���ȷ��ͨ����ĳͨ��ȫ����Ϊ0��

    int bins = 256;
    int hist_size[] = {bins};
    float range[] = {0, 256};
    const float *ranges[] = {range};
    MatND hist_r, hist_g, hist_b;

    //�ȼ����ɫֱ��ͼ
    int channels_r[] = {2};
    calcHist(&img, 1, channels_r, Mat(), hist_r, 1, hist_size, ranges, true, false);

    //������ɫֱ��ͼ
    int channels_g[] = {1};
    calcHist(&img, 1, channels_g, Mat(), hist_g, 1, hist_size, ranges, true, false);

    //������ɫֱ��ͼ
    int channels_b[] = {0};
    calcHist(&img, 1, channels_b, Mat(), hist_b, 1, hist_size, ranges, true, false);

    //*******����
    double max_r = 0, max_b = 0, max_g = 0;
    minMaxLoc(hist_r, 0, &max_r, 0, 0);
    minMaxLoc(hist_g, 0, &max_g, 0, 0);
    minMaxLoc(hist_b, 0, &max_b, 0, 0);
    int scale = 1;
    int hist_height = 256;
    Mat dst = Mat::zeros(hist_height, bins * 3, CV_8UC3);

    //��ʽ��ʼ����
    for (int i = 0; i < bins; i++)
    {
        float value_r = hist_r.at<float>(i);
        float value_g = hist_g.at<float>(i);
        float value_b = hist_b.at<float>(i);

        //�߶�
        int intensity_r = cvRound(value_r * hist_height / max_r);
        int intensity_g = cvRound(value_g * hist_height / max_g);
        int intensity_b = cvRound(value_b * hist_height / max_b);

        //���ƾ���
        rectangle(dst, Point(i * scale, hist_height - 1), Point((i + 1) * scale - 1, hist_height - intensity_r), Scalar(0, 0, 255));
        rectangle(dst, Point((i + bins) * scale, hist_height - 1), Point((i + 1 + bins) * scale - 1, hist_height - intensity_g), Scalar(0, 255, 0));
        rectangle(dst, Point((i + 2 * bins) * scale, hist_height - 1), Point((i + 1 + 2 * bins) * scale - 1, hist_height - intensity_b), Scalar(255, 0, 0));
    }

    imshow("dst", dst);
    waitKey(-1);
}