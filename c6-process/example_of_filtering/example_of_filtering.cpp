/*
* ���ļ���5���˲����ۺ�����
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//����һЩȫ�ֱ���
Mat g_src, g_dst1, g_dst2, g_dst3, g_dst4, g_dst5;
int g_box_filter_value = 6;       //�����˲������
int g_mean_blur_value = 10;       //��ֵ�˲������
int g_gaussain_blur_value = 6;    //��˹�˲������
int g_median_blur_value = 10;     //��ֵ�˲������
int g_bilatera_filter_value = 10; //˫���˲������

//����ȫ�ֻص�����
static void on_box_filter(int, void *);
static void on_mean_blur(int, void *);
static void on_gaussain_filter(int, void *);
static void on_median_blur(int, void *);
static void on_bilatera_filter(int, void *);

int main()
{
    system("color 5E");
    g_src = imread("lena.jpg", IMREAD_COLOR);

    //����ԭͼ��
    g_dst1 = g_src.clone();
    g_dst2 = g_src.clone();
    g_dst3 = g_src.clone();
    g_dst4 = g_src.clone();
    g_dst5 = g_src.clone();

    //��ʾԭͼ��
    imshow("raw", g_src);

    //�����˲�
    namedWindow("box_filter", 1);
    createTrackbar("boxfilter", "box_filter", &g_box_filter_value, 50, on_box_filter);
    on_box_filter(g_box_filter_value, 0);
    imshow("box_filter", g_dst1);

    //��ֵ�˲�
    namedWindow("mean_blur", 1);
    createTrackbar("meanfilter", "mean_blur", &g_mean_blur_value, 50, on_mean_blur);
    on_mean_blur(g_mean_blur_value, 0);
    imshow("mean_blur", g_dst2);

    //��˹�˲�
    namedWindow("gaussain", 1);
    createTrackbar("gaussainfilter", "gaussain", &g_gaussain_blur_value, 50, on_gaussain_filter);
    on_gaussain_filter(g_gaussain_blur_value, 0);
    imshow("gaussain", g_dst3);

    //��ֵ�˲�
    namedWindow("median_filter", 1);
    createTrackbar("medianfilter", "median_filter", &g_median_blur_value, 50, on_median_blur);
    on_median_blur(g_median_blur_value, 0);
    imshow("median_filter", g_dst4);

    //˫���˲�
    namedWindow("bilatera_filter", 1);
    createTrackbar("bilaterafilter", "bilatera_filter", &g_bilatera_filter_value, 50, on_bilatera_filter);
    on_bilatera_filter(g_bilatera_filter_value, 0);
    imshow("bilatera_filter", g_dst5);

    waitKey(-1);
}

static void on_box_filter(int, void *)
{
    //�����˲��Ļص�����
    boxFilter(g_src, g_dst1, -1, Size(g_box_filter_value + 1, g_box_filter_value + 1));
    imshow("box_filter", g_dst1);
}

static void on_mean_blur(int, void *)
{
    //��ֵ�˲��Ļص�����
    blur(g_src, g_dst2, Size(g_mean_blur_value + 1, g_mean_blur_value + 1), Point(-1, -1));
    imshow("mean_blur", g_dst2);
}

static void on_gaussain_filter(int, void *)
{
    GaussianBlur(g_src, g_dst3, Size(2 * g_gaussain_blur_value + 1, 2 * g_gaussain_blur_value + 1), 0, 0);
    imshow("gaussain", g_dst3);
}

static void on_median_blur(int, void *)
{
    medianBlur(g_src, g_dst4, g_median_blur_value * 2 + 1);
    imshow("median_filter", g_dst4);
}

static void on_bilatera_filter(int, void *)
{
    bilateralFilter(g_src, g_dst5, g_bilatera_filter_value, g_bilatera_filter_value * 2, g_bilatera_filter_value / 2);
    imshow("bilatera_filter", g_dst5);
}