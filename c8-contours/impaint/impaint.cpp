/*
 * ͼ���޲�
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat img, mask;
Point previous_point(-1, -1);

static void on_mouse(int event, int x, int y, int flags, void *)
{
    if (event == EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON))
        //���̧��
        previous_point = Point(-1, -1);
    else if (event == EVENT_LBUTTONDOWN)
        //�������
        previous_point = Point(x, y);
    else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))
    //����ƶ�����
    {
        Point pt(x, y);
        if (previous_point.x < 0)
            previous_point = pt;

        //���ư�ɫ�ߣ���ģ��ͼ��ͬʱ���ƣ�
        //������ģ�Ĵ���ʽ������
        line(mask, previous_point, pt, Scalar::all(255), 5, LINE_AA);
        line(img, previous_point, pt, Scalar::all(255), 5, LINE_AA);
        previous_point = pt;
        imshow("img", img);
    }
}

int main()
{
    Mat src = imread("lena.jpg", IMREAD_COLOR);
    img = src.clone();
    mask = Mat::zeros(img.size(), CV_8U);

    imshow("img", img);

    setMouseCallback("img", on_mouse, 0);

    while (1)
    {
        char c = waitKey(0);

        if (c == 27)
            break;

        if (c == '2')
        {
            //�ָ�ԭͼ
            mask = Scalar::all(0);
            src.copyTo(img);
            imshow("img", img);
        }

        if (c == '1')
        //ͼ���޲�
        {
            Mat inpaint_img;
            inpaint(img, mask, inpaint_img, 3, INPAINT_TELEA);
            /*
             * �޸�����������Ч����̫��
             * ��һ��������ԭͼ��
             * �ڶ����������޸���ģ�����з�0����Ϊ�޸�����
             * ���������������
             * ���ĸ��������޸��ο��뾶
             * ������������޸��㷨
             * ��INPAINT_TELEA��INPAINT_NS����
            */
            imshow("inpaint", inpaint_img);
        }
    }
}