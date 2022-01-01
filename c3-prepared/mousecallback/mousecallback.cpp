/*
*���ļ�ѧϰʹ��������
*/

//���ص�Ҳ��ͨ�����ûص�����ʵ�ֵ�
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

//���ص�����
void mouse_callback(int event, int x, int y, int flags, void *params);
//���ƾ��ο���
void draw_rect(Mat &, Rect);
void show_text();

Rect rectangle_g;
/*
*Rect �Ǿ��ζ��󣬣�x,y,w,h����������
*��size��area��tl,br,width,height,contains(Point(x,y))
*�ֱ��ʾ�ߴ磬������������꣬�������꣬���ߣ��͵�İ���
*������&��|�Ծ����󽻺Ͳ�
*rect + Point(x,y)ƽ��
*rect + size(size)����
*/

bool draw_flag = false;
//���Ƶı��

RNG g_rng(123456);
//RNG����opencv��C++���������������
//next���Բ�����һ�������
//uniform ���Է���ָ����Χ�����
//gaussian���Է��ظ�˹�����
//fill����������

int main()
{
    rectangle_g = Rect(-1, -1, 0, 0);
    Mat src(600, 800, CV_8UC3), temp;
    src.copyTo(temp);
    src = Scalar::all(0);
    //scalar�������ͨ���ĳ�ʼֵ���൱��Ԫ��

    namedWindow("callback");
    setMouseCallback("callback", mouse_callback, (void *)&src);
    //���ô��ڻص�����������������ͬ�����û�����

    while (true)
    {
        src.copyTo(temp);
        if (draw_flag)
            //�˴���Ϊ��ʵʱ��ʾ�켣
            draw_rect(temp, rectangle_g);
        imshow("callback", temp);

        if (waitKey(10) == 27)
            break;
    }
    return 0;
}

void mouse_callback(int event, int x, int y, int flags, void *params)
{
    //���ص�����,flags�ƺ�����겻ͬ����ʱ���ز�ͬ��ֵ

    Mat &img = *(Mat *)params;

    switch (event)
    {
    case EVENT_MOUSEMOVE:
        //����ƶ�
        {
            if (draw_flag)
            {
                rectangle_g.width = x - rectangle_g.x;
                rectangle_g.height = y - rectangle_g.y;
            }
        }
        break;

    case EVENT_LBUTTONDOWN:
        //�������
        {
            draw_flag = true;
            rectangle_g = Rect(x, y, 0, 0);
            //��¼��ʼλ��
        }
        break;

    case EVENT_LBUTTONUP:
        //���̧��
        draw_flag = false;
        if (rectangle_g.width < 0)
        {
            //x�ᷴ�����ƶ�
            rectangle_g.x += rectangle_g.width;
            rectangle_g.width *= -1;
        }

        if (rectangle_g.height < 0)
        {
            //y�ᷴ�����ƶ�
            rectangle_g.y += rectangle_g.height;
            rectangle_g.height *= -1;
        }

        draw_rect(img, rectangle_g);

        break;
    }
}

void draw_rect(Mat &img, Rect box)
{
    rectangle(img, box.tl(), box.br(), Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)));
}