/*
 * ���ļ�����ѧϰ��̬ѧ�任
 * �����������㣬��̬ѧ�ݶȣ���ñ����ñ
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat img, dst, grad;
int element_shape = MORPH_RECT; //Ԫ�ؽṹ��״
int max_iteration = 10;
int open_close_shift = 0;
int erode_dilate_shift = 0;
int top_black_shift = 0;

//ȫ�ֺ���
static void open_close(int, void *);
static void erode_dilate(int, void *);
static void top_black_hat(int, void *);

int main()
{
    img = imread("lena.jpg", IMREAD_COLOR);

    namedWindow("raw", 1);
    namedWindow("open_close", 1);
    namedWindow("top_black", 1);
    namedWindow("erode_dilate", 1);
    namedWindow("gradient", 1);

    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    morphologyEx(img, grad, MORPH_GRADIENT, element);
    //��̬ѧ�ݶ�������ͼ��ȥ��ʴͼ��͹�Ա�Ե
    imshow("raw", img);
    imshow("gradient", grad);

    open_close_shift = 9;
    erode_dilate_shift = 9;
    top_black_shift = 2;

    createTrackbar("iteration", "open_close", &open_close_shift, max_iteration * 2 + 1, open_close);
    createTrackbar("iteration", "top_black", &top_black_shift, 2 * max_iteration + 1, top_black_hat);
    createTrackbar("iteration", "erode_dilate", &erode_dilate_shift, 2 * max_iteration + 1, erode_dilate);

    while (1)
    {
        //��ѯ�ķ�ʽ��ȡ����
        int c;
        open_close(open_close_shift, 0);
        erode_dilate(erode_dilate_shift, 0);
        top_black_hat(top_black_shift, 0);

        c = waitKey(0);
        if ((char)c == 'q')
            break;
        else if ((char)c == 49)
            element_shape = MORPH_ELLIPSE;
        else if ((char)c == 50)
            element_shape = MORPH_RECT;
        else if ((char)c == 51)
            element_shape = MORPH_CROSS;
    }
}

void open_close(int, void *)
{
    //������ͱ�����
    /*
     * ���������ȸ�ʴ������
     * ��������ϸС�����壬����ϸ���������
     * ����ƽ���ϴ�����ı߽��Ҳ��ı������
     * 
     * �������������ͺ�ʴ
     * �����ų�С�ͺڶ�
    */
    int offset = open_close_shift - max_iteration;
    int abs_offset = offset > 0 ? offset : -offset;

    Mat element = getStructuringElement(element_shape, Size(abs_offset * 2 + 1, abs_offset * 2 + 1), Point(abs_offset, abs_offset));

    if (offset < 0)
        morphologyEx(img, dst, MORPH_OPEN, element);
    /*
         * ��̬ѧ�仯����
         * ǰ�����������������
         * ����������������
         * ��MORPH_OPEN/CLOSE,MORPH_TOPHAT/BLACKHAT,MORPH_ERODE/DILATE,MORPH_GRADIENT
         * ���ĸ�����һ����element��ȡ�������ݣ���erode����
         * �����������ê��
         * �����������ǵ�������
         * ���ߡ��˸������Ǳ߽����ͣ����ù�
        */
    else
        morphologyEx(img, dst, MORPH_CLOSE, element);

    imshow("open_close", dst);
}

void erode_dilate(int, void *)
{
    //���ͺ͸�ʴ

    int offset = erode_dilate_shift - max_iteration;
    int abs_offset = offset > 0 ? offset : -offset;
    Mat element = getStructuringElement(element_shape, Size(abs_offset * 2 + 1, abs_offset * 2 + 1), Point(abs_offset, abs_offset));

    if (offset < 0)
        erode(img, dst, element);
    else
        dilate(img, dst, element);

    imshow("erode_dilate", dst);
}

void top_black_hat(int, void *)
{
    //��ñ��ñ
    /*
     * ��ñ��Դͼ���뿪����֮�������ٽ�����һЩ�İߵ�
     * ��ñ��Դͼ���������֮�������ٽ��㰵һЩ�İߵ�
    */

    int offset = top_black_shift - max_iteration;
    int abs_offset = offset > 0 ? offset : -offset;

    Mat element = getStructuringElement(element_shape, Size(abs_offset * 2 + 1, abs_offset * 2 + 1), Point(abs_offset, abs_offset));

    if (offset < 0)
        morphologyEx(img, dst, MORPH_TOPHAT, element);
    else
        morphologyEx(img, dst, MORPH_BLACKHAT, element);

    imshow("top_black", dst);
}